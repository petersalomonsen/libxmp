#!/bin/bash
#emconfigure ./configure --enable-static --disable-shared --disable-it CFLAGS=-O3
#emmake make
#emcc -I./include lib/libxmp.a ./wasmlib/wasm-mod-player.c -O3 -o wasmlib/wasm-mod-player.wasm

emcc -Oz -DLIBXMP_CORE_DISABLE_IT -I./include -I ./src ./wasmlib/wasm-mod-player.c src/player.c src/extras.c \
         src/smix.c src/scan.c src/hmn_extras.c src/lfo.c src/med_extras.c src/load_helpers.c \
         src/virtual.c src/mixer.c src/period.c src/control.c src/load.c src/format.c src/hio.c \
         src/memio.c src/md5.c src/dataio.c src/mix_paula.c src/read_event.c src/effects.c \
         src/mix_all.c \
         src/loaders/common.c src/loaders/mod_load.c src/loaders/sample.c  \
         -o wasmlib/wasm-mod-player.wasm