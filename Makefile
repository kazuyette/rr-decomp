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

AS          := mipsel-linux-gnu-as
LD          := mipsel-linux-gnu-ld
OBJCOPY     := mipsel-linux-gnu-objcopy
PYTHON      := python3
MASPSX      := $(PYTHON) tools/maspsx/maspsx.py

PSX_GCC_DIR ?= /opt/psx-gcc
GCC         := $(PSX_GCC_DIR)/gcc -B$(PSX_GCC_DIR)/
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

.PHONY: all dirs report clean
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
	$(GCC) $(GCC_FLAGS) -S $< -o $@

# Round 67: c_o1.c holds real-C conversions that byte-match under the
# ORIGINAL compiler settings (-O1 -mmips-as: assembler macro forms +
# no scheduling, expanded ASPSX-style by maspsx). Only this file uses
# them; everything already matched keeps the historical flags above.
$(BUILD_DIR)/src/c_o1.s: GCC_FLAGS := -O1 -mrnames -mmips-as -fno-builtin -fsigned-char -gcoff

# ...and assembled in ASPSX-2.2x emulation, whose $at macro expansion
# (lui/addiu %lo/addu/op 0($at)) is the retail addressing shape.
$(BUILD_DIR)/src/c_o1.o: $(BUILD_DIR)/src/c_o1.s
	$(MASPSX) --aspsx-version 2.21 --run-assembler --gnu-as-path $(AS) -o $@ $(AS_FLAGS) $<

$(BUILD_DIR)/src/%.o: $(BUILD_DIR)/src/%.s
	$(MASPSX) --run-assembler --gnu-as-path $(AS) -o $@ $(AS_FLAGS) $<

# All currently-decompiled functions merged into one relocatable object, so
# objdiff.json's units can diff against it regardless of which .c file each
# function lives in.
$(BUILD_DIR)/matched.o: $(BASE_OBJS)
	$(LD) -r -o $@ $(BASE_OBJS)

report: all
	objdiff-cli report generate -o $(BUILD_DIR)/report.json

clean:
	rm -rf $(BUILD_DIR)
