# PS1 matching-decomp toolchain image for rr-decomp.
#
# Bundles: old GCC 2.7.2 targeting mips-sony-psx (built from
# https://github.com/decompals/old-gcc, same source every other PSX
# decomp project uses), plus GNU binutils for mipsel and Python for splat.
#
# Built and pushed to ghcr.io by .github/workflows/docker.yaml whenever this
# file changes -- the main build workflow (build.yaml) just pulls the
# published image, it never rebuilds GCC from source itself.

# --- Stage 1: build GCC 2.7.2 (PSX target) ---
# Deliberately ubuntu:focal here, matching decompals/old-gcc's own Dockerfile
# exactly (not the newer ubuntu:22.04 used below for the runtime stage):
# the static -m32 link of xgcc (`collect2: error: ld returned 1 exit status`)
# fails on 22.04's multilib setup but works on focal, which is why upstream
# pins it.
FROM ubuntu:focal AS gcc-build
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y build-essential gcc gcc-multilib wget git

ENV VERSION=2.7.2
ENV GNUPATH=old-gnu

WORKDIR /toolchain-src
RUN git clone --depth 1 https://github.com/decompals/old-gcc.git

WORKDIR /toolchain-src/build
RUN wget https://ftp.gnu.org/${GNUPATH}/gcc/gcc-${VERSION}.tar.gz \
    && tar xzf gcc-${VERSION}.tar.gz

WORKDIR /toolchain-src/build/gcc-${VERSION}
RUN sed -i -- 's/include <varargs.h>/include <stdarg.h>/g' *.c \
    && patch -u -p1 obstack.h -i ../../old-gcc/patches/obstack-2.7.2.h.patch \
    && patch -u -p1 configure -i ../../old-gcc/patches/configure.patch \
    && patch -u -p1 config.sub -i ../../old-gcc/patches/config.sub.patch \
    && patch -u -p1 config/mips/mips.h -i ../../old-gcc/patches/mipsel-2.7.patch \
    && patch -su -p1 < ../../old-gcc/patches/psx-2.5.7.patch

RUN ./configure \
        --target=mips-sony-psx \
        --prefix=/opt/cross \
        --with-endian-little \
        --with-gnu-as \
        --disable-gprof \
        --disable-gdb \
        --disable-werror \
        --host=i386-pc-linux \
        --build=i386-pc-linux \
    && make --jobs "$(nproc)" cpp cc1 xgcc cc1plus g++ CFLAGS="-std=gnu89 -m32 -static" \
    && mkdir -p /opt/psx-gcc \
    && mv xgcc /opt/psx-gcc/gcc \
    && cp cpp cc1 cc1plus g++ /opt/psx-gcc/

# --- Stage 1b: build GCC 2.5.7 (PSX target) ---
# Round 69: parts of the retail EXE (a libgpu-style unit) only
# byte-match GCC 2.5.7's -O2 scheduler, so the toolchain now carries
# both compilers. Same recipe as decompals/old-gcc's
# gcc-2.5.7-psx.Dockerfile (funet mirror is plain http, which is also
# why it survives this build environment's TLS quirks).
FROM ubuntu:focal AS gcc257-build
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y build-essential gcc gcc-multilib wget git

WORKDIR /work
RUN git clone --depth 1 https://github.com/decompals/old-gcc.git patches-src
RUN wget http://www.nic.funet.fi/index/gnu/funet/historical-funet-gnu-area-from-early-1990s/gcc-2.5.7.tar.gz \
    && tar xzf gcc-2.5.7.tar.gz

WORKDIR /work/gcc-2.5.7
RUN sed -i -- 's/include <varargs.h>/include <stdarg.h>/g' *.c \
    && patch -u -p1 obstack.h -i ../patches-src/patches/obstack-2.5.7.h.patch \
    && patch -u -p1 sdbout.c -i ../patches-src/patches/sdbout-2.6.0.c.patch \
    && patch -u -p1 gvarargs.h -i ../patches-src/patches/gvarargs-2.5.7.h.patch \
    && patch -u -p1 cccp.c -i ../patches-src/patches/cccp-2.5.7.c.patch \
    && patch -u -p1 gcc.c -i ../patches-src/patches/gcc-2.5.7.c.patch \
    && patch -u -p1 g++.c -i ../patches-src/patches/g++-2.5.7.c.patch \
    && patch -u -p1 config/mips/mips.h -i ../patches-src/patches/mips-2.5.7.h.patch \
    && patch -su -p1 < ../patches-src/patches/psx-2.5.7.patch \
    && touch insn-config.h

RUN ./configure \
        --target=mips-sony-psx \
        --prefix=/opt/cross \
        --with-endian-little \
        --with-gnu-as \
        --host=i386-pc-linux \
        --build=i386-pc-linux \
    && make --jobs "$(nproc)" cpp cc1 xgcc cc1plus g++ CFLAGS="-std=gnu89 -m32 -static -Dbsd4_4 -Dmips -march=i686 -DHAVE_STRERROR"
RUN mkdir -p /opt/psx-gcc257 \
    && mv xgcc /opt/psx-gcc257/gcc \
    && cp cpp cc1 /opt/psx-gcc257/ \
    && (cp cc1plus g++ /opt/psx-gcc257/ || true)

# --- Stage 2: runtime image used by the main build workflow ---
FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        binutils-mipsel-linux-gnu python3 python3-pip make ca-certificates curl \
    && rm -rf /var/lib/apt/lists/*

COPY --from=gcc-build /opt/psx-gcc /opt/psx-gcc
COPY --from=gcc257-build /opt/psx-gcc257 /opt/psx-gcc257
ENV PATH="/opt/psx-gcc:${PATH}"
WORKDIR /work
