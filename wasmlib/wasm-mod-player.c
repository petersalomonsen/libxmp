#include <xmp.h>
#include "../src/common.h"
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

EMSCRIPTEN_KEEPALIVE
int getPosition() {
    return frame_info.pos;
}

EMSCRIPTEN_KEEPALIVE
void setPosition(int position) {
    xmp_set_position(ctx, position);
}

EMSCRIPTEN_KEEPALIVE
int getRow() {
    return frame_info.row;
}

EMSCRIPTEN_KEEPALIVE
void setRow(int row) {
    xmp_set_row(ctx, row);
}

EMSCRIPTEN_KEEPALIVE
int getTime() {
    return frame_info.time;
}

EMSCRIPTEN_KEEPALIVE
void seekTime(int time) {
    xmp_seek_time(ctx, time);
}

EMSCRIPTEN_KEEPALIVE
int getBPM() {
    return frame_info.bpm;
}

EMSCRIPTEN_KEEPALIVE
void setBPM(int bpm) {
    struct context_data *ctxdata = (struct context_data *)ctx;
    ctxdata->p.bpm = bpm;
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