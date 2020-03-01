#!/bin/bash
emconfigure ./configure --enable-static
emmake make
emcc -I./include lib/libxmp.a ./test.c -o test.wasm