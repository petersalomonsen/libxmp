#!/bin/bash
emconfigure ./configure --enable-static
emmake make
emcc -I./include lib/libxmp.a ./wasm-mod-player.c -O3 -o wasm-mod-player.wasm