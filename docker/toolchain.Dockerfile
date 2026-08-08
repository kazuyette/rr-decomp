# PS1 matching-decomp toolchain image for rr-decomp.
#
# Bundles: old GCC 2.7.2 targeting mips-sony-psx (built from
# https://github.com/decompals/old-gcc, same source every other PSX
# decomp project uses), plus GNU binutils for mipsel and Python for splat.
#
# Built and pushed to ghcr.io by .github/workflows/docker.yaml whenever this
# file changes -- the main build workflow (build.yaml) just pulls the
# published image, it never rebuilds GCC from source itself.
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential gcc gcc-multilib wget git ca-certificates \
        binutils-mipsel-linux-gnu python3 python3-pip \
    && rm -rf /var/lib/apt/lists/*

# --- Build old GCC 2.7.2 (PSX target) from decompals/old-gcc ---
WORKDIR /toolchain-src
RUN git clone --depth 1 https://github.com/decompals/old-gcc.git

ENV VERSION=2.7.2
ENV GNUPATH=old-gnu

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
    && cp cpp cc1 cc1plus g++ /opt/psx-gcc/ \
    && cd / && rm -rf /toolchain-src

ENV PATH="/opt/psx-gcc:${PATH}"
WORKDIR /work
