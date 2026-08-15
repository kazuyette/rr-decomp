build/psx.exe.elf: \
    build/assets/header.o \
    build/asm/data/800.rodata.o \
    build/src/29E8.o \
    build/asm/data/49A30.data.o
build/assets/header.o:
build/asm/data/800.rodata.o:
build/src/29E8.o:
build/asm/data/49A30.data.o:
-include build/assets/header.d build/asm/data/800.rodata.d build/src/29E8.d build/asm/data/49A30.data.d
