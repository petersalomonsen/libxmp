#include <xmp.h>
#include "emscripten.h"
#include <stdlib.h>

xmp_context c;
struct xmp_frame_info frame_info;
struct xmp_module_info module_info;

EMSCRIPTEN_KEEPALIVE
void * allocMemoryForModule(long size) {
    return malloc(size);
} 

EMSCRIPTEN_KEEPALIVE
void loadModule(void *mem, long size) {
    /* Create the player context */
    c = xmp_create_context();

    /* Load our module */
    xmp_load_module_from_memory(c, mem, size);
    xmp_start_player(c, 44100, 0);
}

/**
 * 
 */
EMSCRIPTEN_KEEPALIVE
void * playFrame()
{
    xmp_play_frame(c);
    xmp_get_frame_info(c, &frame_info);
    return &frame_info;
}