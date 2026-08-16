build/psx.exe.elf: \
    build/asm/header.o \
    build/asm/data/800.rodata.o \
    build/src/29E8.o \
    build/src/psyq.o \
    build/asm/data/49A30.data.o
build/asm/header.o:
build/asm/data/800.rodata.o:
build/src/29E8.o:
build/src/psyq.o:
build/asm/data/49A30.data.o:
-include build/asm/header.d build/asm/data/800.rodata.d build/src/29E8.d build/src/psyq.d build/asm/data/49A30.data.d
