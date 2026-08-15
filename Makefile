# Build pipeline for rr-decomp.
#
# Two kinds of objects:
# - "target" objects (asm/*.s -> build/asm/*.o): splat's disassembly of the
#   original PSX.EXE, reassembled as-is. Ground truth, nothing to match
#   against them, they ARE the original bytes.
# - "base" objects (src/*.c -> build/src/*.o, merged into build/matched.o):
#   real C reimplementations, compiled with the project's PSX cross-GCC and
#   diffed against the target via objdiff.json. Grows over time as more
#   functions get decompiled -- see BUILD_NOTES.md for what's covered so far.
#
# The C compiler (old GCC 2.7.2, PSX target) is not vendored in this repo --
# it comes from the toolchain image built by docker/toolchain.Dockerfile
# (published to ghcr.io by .github/workflows/docker.yaml). Locally, point
# PSX_GCC_DIR at wherever you extracted/built it (must contain gcc+cc1).

BUILD_DIR   := build
ASM_DIR     := asm
SRC_DIR     := src
INC_DIR     := include
# Docker Desktop on Windows exposes 64-bit inode numbers over its bind mount,
# and the 32-bit cpp from GCC 2.7.2 gets EOVERFLOW ("Value too large for
# defined data type") when it stats a header found through -I. Staging the
# headers onto the container's own filesystem sidesteps it. On Linux this is
# just a copy of four small files, and -I affects header lookup only, never
# codegen.
INC_STAGE   := /tmp/rr-include

AS          := mipsel-linux-gnu-as
LD          := mipsel-linux-gnu-ld
OBJCOPY     := mipsel-linux-gnu-objcopy
PYTHON      := python3
MASPSX      := $(PYTHON) tools/maspsx/maspsx.py

PSX_GCC_DIR ?= /opt/psx-gcc
GCC         := $(PSX_GCC_DIR)/gcc -B$(PSX_GCC_DIR)/
# Round 69: second compiler for the GCC 2.5.7-era unit (src/c_257.c);
# built alongside 2.7.2 in docker/toolchain.Dockerfile.
PSX_GCC257_DIR ?= /opt/psx-gcc257
GCC257      := $(PSX_GCC257_DIR)/gcc -B$(PSX_GCC257_DIR)/
GCC_FLAGS   := -O2 -mrnames -fno-builtin -fsigned-char -gcoff

AS_FLAGS    := -EL -march=r3000 -mtune=r3000 -mabi=32 -I$(INC_DIR)

# --- target objects (disassembly, reassembled as-is) ---

# Plain data segments (header, rodata, data): no gcc/ASPSX quirks to emulate,
# assemble directly with GNU as.
DATA_OBJS := \
    $(BUILD_DIR)/asm/header.o \
    $(BUILD_DIR)/asm/data/800.rodata.o \
    $(BUILD_DIR)/asm/data/49A30.data.o

# The main code blob: disassembled machine code, routed through maspsx so
# that -G0/$at/li-expansion behaviour matches what PSY-Q's ASPSX.EXE would
# have produced (needed for a byte-exact reassembly).
CODE_OBJS := $(BUILD_DIR)/asm/29E8.o

TARGET_OBJS := $(DATA_OBJS) $(CODE_OBJS)

# --- base objects (real C, see src/) ---

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
BASE_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/src/%.o,$(SRC_FILES))

.PHONY: all dirs report clean setup

# Regenerate asm/ from your own PSX.EXE. Required once after cloning, and
# again after any change to psx.exe.yaml or symbol_addrs.txt. splat never
# overwrites a file that exists, so renaming a symbol means deleting the
# listings that mention it before re-running this.
setup:
	$(PYTHON) tools/setup.py
all: $(TARGET_OBJS) $(BUILD_DIR)/matched.o

dirs:
	@mkdir -p $(BUILD_DIR)/asm/data $(BUILD_DIR)/src

$(BUILD_DIR)/asm/header.o: $(ASM_DIR)/header.s | dirs
	$(AS) $(AS_FLAGS) -G0 -o $@ $<

$(BUILD_DIR)/asm/data/800.rodata.o: $(ASM_DIR)/data/800.rodata.s | dirs
	$(AS) $(AS_FLAGS) -G0 -o $@ $<

$(BUILD_DIR)/asm/data/49A30.data.o: $(ASM_DIR)/data/49A30.data.s | dirs
	$(AS) $(AS_FLAGS) -G0 -o $@ $<

$(BUILD_DIR)/asm/29E8.o: $(ASM_DIR)/29E8.s | dirs
	$(MASPSX) --run-assembler --gnu-as-path $(AS) -o $@ $(AS_FLAGS) $<

$(BUILD_DIR)/src/%.s: $(SRC_DIR)/%.c | dirs
	@mkdir -p $(INC_STAGE) && cp -f $(INC_DIR)/* $(INC_STAGE)/
	$(GCC) $(GCC_FLAGS) -I$(INC_STAGE) -S $< -o $@

# Rounds 67-68: the c_o1/c_o1_ndb/c_o2 files hold real-C conversions
# that byte-match under the ORIGINAL per-unit compiler settings
# (-O1 / -O1 -fno-delayed-branch / -O2, all with -mmips-as so cc1
# emits assembler macro forms), assembled in ASPSX-2.2x emulation
# (addiu-$at macro expansion) with the epilogue delay-slot swap the
# real ASPSX reorderer performed (tools/aspsx_epilogue_swap.py).
# Everything already matched keeps the historical flags above.
$(BUILD_DIR)/src/c_o1.s: GCC_FLAGS := -O1 -mrnames -mmips-as -fno-builtin -fsigned-char -gcoff
$(BUILD_DIR)/src/c_o1_ndb.s: GCC_FLAGS := -O1 -mrnames -mmips-as -fno-delayed-branch -fno-builtin -fsigned-char -gcoff
$(BUILD_DIR)/src/c_o2.s: GCC_FLAGS := -O2 -mrnames -mmips-as -fno-builtin -fsigned-char -gcoff

# c_257.c compiles with GCC 2.5.7 (no -mrnames: 2.5.7 would emit
# symbolic register names that modern gas rejects).
$(BUILD_DIR)/src/c_257.s: $(SRC_DIR)/c_257.c | dirs
	@mkdir -p $(INC_STAGE) && cp -f $(INC_DIR)/* $(INC_STAGE)/
	$(GCC257) -O2 -mmips-as -fno-builtin -fsigned-char -gcoff -I$(INC_STAGE) -S $< -o $@

$(BUILD_DIR)/src/c_o1.o $(BUILD_DIR)/src/c_o1_ndb.o $(BUILD_DIR)/src/c_o2.o $(BUILD_DIR)/src/c_257.o: \
$(BUILD_DIR)/src/%.o: $(BUILD_DIR)/src/%.s
	$(PYTHON) tools/aspsx_epilogue_swap.py $< $<.swap
	$(MASPSX) --aspsx-version 2.21 --run-assembler --gnu-as-path $(AS) -o $@ $(AS_FLAGS) $<.swap

$(BUILD_DIR)/src/%.o: $(BUILD_DIR)/src/%.s
	$(MASPSX) --run-assembler --gnu-as-path $(AS) -o $@ $(AS_FLAGS) $<

# --- pipeline-specific units (tools/flag_sweep.py + tools/apply_sweep.py) ---
# src/x_<tag>_NN.c holds functions measured to reproduce the retail bytes
# under one specific pipeline. No tag is a prefix of another, because make
# resolves competing pattern rules by shortest stem and "x_o1_%" would
# otherwise capture x_o1d_00 as well.
#   o2p = -O2, plain            o2m = -O2 -mmips-as
#   o1m = -O1 -mmips-as         o1d = -O1 -mmips-as -fno-delayed-branch
#   c257 = GCC 2.5.7 -O2 -mmips-as
$(BUILD_DIR)/src/x_o2p_%.s: GCC_FLAGS := -O2 -mrnames -fno-builtin -fsigned-char -gcoff
$(BUILD_DIR)/src/x_o2m_%.s: GCC_FLAGS := -O2 -mrnames -mmips-as -fno-builtin -fsigned-char -gcoff
$(BUILD_DIR)/src/x_o1m_%.s: GCC_FLAGS := -O1 -mrnames -mmips-as -fno-builtin -fsigned-char -gcoff
$(BUILD_DIR)/src/x_o1d_%.s: GCC_FLAGS := -O1 -mrnames -mmips-as -fno-delayed-branch -fno-builtin -fsigned-char -gcoff

$(BUILD_DIR)/src/x_c257_%.s: $(SRC_DIR)/x_c257_%.c | dirs
	@mkdir -p $(INC_STAGE) && cp -f $(INC_DIR)/* $(INC_STAGE)/
	$(GCC257) -O2 -mmips-as -fno-builtin -fsigned-char -gcoff -I$(INC_STAGE) -S $< -o $@

# Everything but o2p goes through ASPSX 2.21 emulation and the epilogue
# delay-slot swap, exactly like c_o1/c_o1_ndb/c_o2/c_257.

$(BUILD_DIR)/src/x_o2m_%.o: $(BUILD_DIR)/src/x_o2m_%.s
	$(PYTHON) tools/aspsx_epilogue_swap.py $< $<.swap
	$(MASPSX) --aspsx-version 2.21 --run-assembler --gnu-as-path $(AS) -o $@ $(AS_FLAGS) $<.swap

$(BUILD_DIR)/src/x_o1m_%.o: $(BUILD_DIR)/src/x_o1m_%.s
	$(PYTHON) tools/aspsx_epilogue_swap.py $< $<.swap
	$(MASPSX) --aspsx-version 2.21 --run-assembler --gnu-as-path $(AS) -o $@ $(AS_FLAGS) $<.swap

$(BUILD_DIR)/src/x_o1d_%.o: $(BUILD_DIR)/src/x_o1d_%.s
	$(PYTHON) tools/aspsx_epilogue_swap.py $< $<.swap
	$(MASPSX) --aspsx-version 2.21 --run-assembler --gnu-as-path $(AS) -o $@ $(AS_FLAGS) $<.swap

$(BUILD_DIR)/src/x_c257_%.o: $(BUILD_DIR)/src/x_c257_%.s
	$(PYTHON) tools/aspsx_epilogue_swap.py $< $<.swap
	$(MASPSX) --aspsx-version 2.21 --run-assembler --gnu-as-path $(AS) -o $@ $(AS_FLAGS) $<.swap

# All currently-decompiled functions merged into one relocatable object, so
# objdiff.json's units can diff against it regardless of which .c file each
# function lives in.
$(BUILD_DIR)/matched.o: $(BASE_OBJS)
	$(LD) -r -o $@ $(BASE_OBJS)

report: all
	objdiff-cli report generate -o $(BUILD_DIR)/report.json

clean:
	rm -rf $(BUILD_DIR)
