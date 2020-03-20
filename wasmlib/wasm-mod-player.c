#include <xmp.h>
#include "emscripten.h"
#include <stdlib.h>

xmp_context ctx;
struct xmp_frame_info frame_info;
struct xmp_module_info module_info;

EMSCRIPTEN_KEEPALIVE
void * allocMemoryForModule(long size) {
    return malloc(size);
} 

EMSCRIPTEN_KEEPALIVE
void loadModule(void *mem, long size, int samplerate) {
    /* Create the player context */
    ctx = xmp_create_context();

    /* Load our module */
    xmp_load_module_from_memory(ctx, mem, size);
    xmp_start_player(ctx, samplerate, 0);
}

EMSCRIPTEN_KEEPALIVE
void setPlayerParameter(int parameter, int value) {
    xmp_set_player(ctx, parameter, value);
}

/**
 * 
 */
EMSCRIPTEN_KEEPALIVE
void * playFrame()
{
    xmp_play_frame(ctx);
    xmp_get_frame_info(ctx, &frame_info);
    return &frame_info;
}