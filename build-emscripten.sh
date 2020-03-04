#!/bin/bash
emconfigure ./configure --enable-static
emmake make
emcc -I./include lib/libxmp.a ./wasmlib/wasm-mod-player.c -O3 -o wasmlib/wasm-mod-player.wasm