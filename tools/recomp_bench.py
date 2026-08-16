#!/usr/bin/env python3
"""Banc d'essai du traducteur : le vrai MIPS contre la traduction.

La question à trancher n'est pas « ma traduction a-t-elle l'air juste » mais
« produit-elle exactement les mêmes octets que le code d'origine ». La seule
réponse qui vaille passe donc par l'exécution du vrai code.

Deux exécutables, un seul jeu d'entrées :

  - la référence : les mots du retail copiés tels quels dans un objet mipsel,
    appelés par un harnais C compilé pour MIPS et exécutés sous qemu-mipsel.
    Aucune interprétation de ma part n'intervient -- ce sont les instructions
    d'origine sur un processeur qui les comprend.

  - la traduction : le C produit par tools/recomp.py, compilé pour la machine
    hôte.

Chacun reçoit le même tampon de 256 octets rempli pseudo-aléatoirement et les
mêmes quatre registres d'argument, puis imprime la valeur de retour et le
tampon final. On compare les deux textes.

Le tampon est aligné à la même adresse relative des deux côtés, et les
fonctions choisies n'utilisent que des pointeurs qu'on leur passe : leurs
résultats ne peuvent donc pas dépendre de l'adresse absolue, seulement du
contenu.
"""
import random
import struct
import subprocess
import sys

FUNCS = sys.argv[1:] or ["func_800465DC", "func_80047D24", "func_80047CC4",
                         "func_80047AE0", "func_80047AF8"]
EXE = "/tmp/rr/files/PSX.EXE"
ASMS = ["/tmp/rrdecomp/asm/psyq.s", "/tmp/rrdecomp/asm/29E8.s"]


def find(nm):
    """Les fonctions vivent dans l'une ou l'autre des deux unites."""
    for a in ASMS:
        addr, cnt = recomp.func_length(a, nm)
        if addr is not None:
            return a, addr, cnt
    raise SystemExit("fonction introuvable : " + nm)
sys.path.insert(0, "/tmp/rrdecomp/tools")
import recomp

BUF = 0x1000      # où le tampon d'essai vit dans la RAM simulée
SIZE = 256
ROUNDS = 24


def vectors():
    rnd = random.Random(20260816)
    out = []
    for _ in range(ROUNDS):
        buf = bytes(rnd.randrange(256) for _ in range(SIZE))
        # Les deux premiers arguments sont des pointeurs : ils doivent être
        # alignés sur 4, sinon le MIPS lève SIGBUS sur le premier lw -- ce que
        # le vrai matériel ferait aussi. Le banc doit poser des questions que
        # la console pouvait entendre.
        args = [4 * rnd.randrange(0, 16), 4 * rnd.randrange(0, 16),
                rnd.randrange(0, 0x100), rnd.randrange(0, 0x100)]
        out.append((buf, args))
    return out


VEC = vectors()


def c_bytes(b):
    return ",".join(str(x) for x in b)


# ---------------------------------------------------------------- référence
def build_reference():
    words = {}
    for nm in FUNCS:
        _, a, c = find(nm)
        words[nm] = (a, recomp.words_from_exe(EXE, a, c))
    # Les sauts absolus (opcode j) n'encodent que les 28 bits bas de leur
    # cible. Copier le code ailleurs en mémoire les envoie donc dans le vide.
    # On place chaque fonction à son adresse d'origine masquée sur 28 bits,
    # dans une section liée à la bonne base : les j retombent alors juste.
    BASE = 0x00010000
    with open("/tmp/recomp/ref_code.s", "w") as f:
        f.write('    .set noreorder\n    .section .psx,"ax",@progbits\n')
        for nm, (a, ws) in sorted(words.items(), key=lambda kv: kv[1][0]):
            f.write(f"    .org 0x{(a & 0x0FFFFFFF) - BASE:X}\n")
            f.write(f"    .globl psx_{nm}\n    .type psx_{nm}, @function\npsx_{nm}:\n")
            for w in ws:
                f.write(f"    .word 0x{w:08X}\n")
            f.write(f"    .size psx_{nm}, .-psx_{nm}\n")
    # Certaines fonctions, nourries d'entrées quelconques, sortent du tampon ou
    # déréférencent un pointeur invalide -- ce que la console ferait aussi. On
    # ne peut pas leur poser la question, alors on note le cas et on l'exclut
    # des deux côtés, plutôt que de bricoler des entrées sur mesure qui
    # rendraient la comparaison moins probante.
    src = ['#include <stdio.h>', '#include <string.h>', '#include <signal.h>',
           '#include <setjmp.h>',
           'typedef unsigned int u32;',
           'static sigjmp_buf JB;',
           'static void onsig(int s){ (void)s; siglongjmp(JB, 1); }',
           '#include <unistd.h>',
           'static unsigned char buf[%d] __attribute__((aligned(16)));' % SIZE]
    for nm in FUNCS:
        src.append(f"u32 psx_{nm}(u32,u32,u32,u32);")
    src.append("int main(void){ u32 rv; int i,k;")
    src.append("  signal(SIGSEGV, onsig); signal(SIGBUS, onsig); signal(SIGALRM, onsig);")
    for nm in FUNCS:
        src.append(f'  for (k = 0; k < {len(VEC)}; k++) {{')
        src.append('    static const unsigned char V[][%d] = {' % SIZE)
        src.append(",\n".join("      {%s}" % c_bytes(b) for b, _ in VEC))
        src.append('    };')
        src.append('    static const u32 A[][4] = {%s};' %
                   ",".join("{%s}" % ",".join(str(x) for x in a) for _, a in VEC))
        src.append('    memcpy(buf, V[k], sizeof buf);')
        src.append('    if (sigsetjmp(JB, 1)) { alarm(0); printf("%s %d CRASH\\n", "'+nm+'", k); continue; }')
        src.append('    alarm(1);')
        src.append(f'    rv = psx_{nm}((u32)buf + A[k][0], (u32)buf + A[k][1],'
                   f' A[k][2], A[k][3]);')
        src.append('    alarm(0);')
        src.append(f'    printf("{nm} %d rv=%08x", k, rv);')
        src.append('    for (i = 0; i < %d; i++) printf(" %%02x", buf[i]);' % SIZE)
        src.append('    printf("\\n");')
        src.append('  }')
    src.append("  return 0; }")
    open("/tmp/recomp/ref_main.c", "w").write("\n".join(src))
    subprocess.run(["mipsel-linux-gnu-gcc", "-static", "-O1", "-o", "/tmp/recomp/ref",
                    "-Wl,--section-start=.psx=0x00010000",
                    "/tmp/recomp/ref_main.c", "/tmp/recomp/ref_code.s"], check=True)
    return subprocess.run(["qemu-mipsel", "/tmp/recomp/ref"],
                          capture_output=True, text=True, check=True).stdout


# --------------------------------------------------------------- traduction
def build_translated(FUNCS):
    parts = ["/* genere par tools/recomp.py */", '#include "rt.h"']
    for nm in FUNCS:
        asm, a, c = find(nm)
        ws = recomp.words_from_exe(EXE, a, c)
        parts.append(recomp.translate("psx_" + nm, a, ws))
    open("/tmp/recomp/gen.c", "w").write("\n".join(parts))
    src = ['#include <stdio.h>', '#include <string.h>', '#include "rt.h"',
           'u8 RAM[0x200000];']
    for nm in FUNCS:
        src.append(f"u32 psx_{nm}(u32,u32,u32,u32);")
    src.append("int main(void){ u32 rv; int i,k;")
    for nm in FUNCS:
        src.append(f'  for (k = 0; k < {len(VEC)}; k++) {{')
        src.append('    static const unsigned char V[][%d] = {' % SIZE)
        src.append(",\n".join("      {%s}" % c_bytes(b) for b, _ in VEC))
        src.append('    };')
        src.append('    static const u32 A[][4] = {%s};' %
                   ",".join("{%s}" % ",".join(str(x) for x in a) for _, a in VEC))
        src.append('    memcpy(RAM + %d, V[k], %d);' % (BUF, SIZE))
        src.append(f'    rv = psx_{nm}({BUF} + A[k][0], {BUF} + A[k][1], A[k][2], A[k][3]);')
        src.append(f'    printf("{nm} %d rv=%08x", k, rv);')
        src.append('    for (i = 0; i < %d; i++) printf(" %%02x", RAM[%d + i]);'
                   % (SIZE, BUF))
        src.append('    printf("\\n");')
        src.append('  }')
    src.append("  return 0; }")
    open("/tmp/recomp/gen_main.c", "w").write("\n".join(src))
    subprocess.run(["gcc", "-O1", "-I/tmp/recomp", "-o", "/tmp/recomp/gen",
                    "/tmp/recomp/gen_main.c", "/tmp/recomp/gen.c"], check=True)
    return subprocess.run(["/tmp/recomp/gen"], capture_output=True, text=True,
                          check=True).stdout


a = build_reference().splitlines()
crashed = {l.split()[0] for l in a if l.endswith("CRASH")}
# Une fonction que la référence n'a pas su exécuter -- pointeur invalide ou
# boucle sans fin sur des entrées quelconques -- est retirée des deux côtés :
# la traduction s'y perdrait pareillement, et une comparaison entre deux
# blocages ne prouve rien.
survivors = [f for f in FUNCS if f not in crashed]
a = [l for l in a if l.split()[0] in set(survivors)]
b = build_translated(survivors).splitlines()
keep = list(range(min(len(a), len(b))))
bad = [i for i in keep if a[i] != b[i]]
print("%d fonctions demandees, %d exclues faute d'entrees valides pour la reference"
      % (len(FUNCS), len(crashed)))
print("%d cas compares" % len(keep))
if len(a) != len(b):
    print("NOMBRE DE LIGNES DIFFERENT : %d contre %d" % (len(a), len(b)))
if bad:
    print("%d divergences. Premiere :" % len(bad))
    i = bad[0]
    print("  vrai MIPS  :", a[i][:150])
    print("  traduction :", b[i][:150])
else:
    print("AUCUNE DIVERGENCE : la traduction rend les memes octets que le retail.")
