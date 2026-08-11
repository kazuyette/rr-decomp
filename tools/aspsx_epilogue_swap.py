#!/usr/bin/env python3
"""ASPSX epilogue delay-slot swap: in reorder-mode cc1 output, the
framed-function epilogue is emitted as `addu $sp,$sp,N` then `j $ra`,
counting on ASPSX to swap the stack restore into the jump delay slot
(the retail binaries show exactly that). maspsx only inserts nops, so
this tiny preprocessor performs the one swap ASPSX did, emitting an
explicit noreorder pair."""
import re, sys
lines = open(sys.argv[1]).read().split('\n')
out = []
i = 0
while i < len(lines):
    l = lines[i]
    m = re.match(r'\s*(addu|addiu)\t\$sp,\$sp,(\d+)\s*$', l)
    if m:
        # find next significant line
        j = i + 1
        while j < len(lines) and (not lines[j].strip() or lines[j].strip().startswith(('.loc', 'LM', '#'))):
            j += 1
        if j < len(lines) and re.match(r'\s*j\t\$(ra|31)\s*$', lines[j]):
            out.append('\t.set\tnoreorder')
            out.append(lines[j])
            out.append(l)
            out.append('\t.set\treorder')
            i = j + 1
            continue
    out.append(l)
    i += 1
open(sys.argv[2], 'w').write('\n'.join(out))
