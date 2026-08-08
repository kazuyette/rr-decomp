# Build pipeline for rr-decomp.
#
# Status: no C reimplementation exists yet. This Makefile currently produces
# "target" objects only -- i.e. it reassembles the disassembly that splat
# extracted from the original PSX.EXE, using GNU binutils (+ maspsx to
# emulate PSY-Q's ASPSX.EXE assembler quirks). These objects are the ground
# truth that future C reimplementations will be diffed against via objdiff.
#
# As functions get rewritten in C (see objdiff.json), this Makefile will
# grow rules to also build "base" objects from src/*.c, and the target/base
# split will separate accordingly. For now target == the only thing built.

BUILD_DIR := build
ASM_DIR   := asm
INC_DIR   := include

AS        := mipsel-linux-gnu-as
OBJCOPY   := mipsel-linux-gnu-objcopy
PYTHON    := python3
MASPSX    := $(PYTHON) tools/maspsx/maspsx.py

AS_FLAGS  := -EL -march=r3000 -mtune=r3000 -mabi=32 -I$(INC_DIR)

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

.PHONY: all dirs report clean
all: $(TARGET_OBJS)

dirs:
	@mkdir -p $(BUILD_DIR)/asm/data

$(BUILD_DIR)/asm/header.o: $(ASM_DIR)/header.s | dirs
	$(AS) $(AS_FLAGS) -G0 -o $@ $<

$(BUILD_DIR)/asm/data/800.rodata.o: $(ASM_DIR)/data/800.rodata.s | dirs
	$(AS) $(AS_FLAGS) -G0 -o $@ $<

$(BUILD_DIR)/asm/data/49A30.data.o: $(ASM_DIR)/data/49A30.data.s | dirs
	$(AS) $(AS_FLAGS) -G0 -o $@ $<

$(BUILD_DIR)/asm/29E8.o: $(ASM_DIR)/29E8.s | dirs
	$(MASPSX) --run-assembler --gnu-as-path $(AS) -o $@ $(AS_FLAGS) $<

report: all
	objdiff-cli report generate -o $(BUILD_DIR)/report.json

clean:
	rm -rf $(BUILD_DIR)
