#pragma once
#include <stdint.h>
#include "engine.hpp"

struct draw_data_t {
    int window_w;
    int window_h;
    float* vertex_buffer;
    int vertex_buffer_used;
    uint32_t* index_buffer;
    int index_buffer_used;
};

#define VERT_BUFFER_MAX_FLOATS 4000
#define VERT_BUFFER_BYTE_SIZE (VERT_BUFFER_MAX_FLOATS * 4)

#define INDEX_BUFFER_MAX_INT32 1000
#define INDEX_BUFFER_BYTE_SIZE (INDEX_BUFFER_MAX_INT32 * 4)

void clear_draw_buffers();
void draw_rect(float x, float y, float sx, float sy, Color col);
void draw_circle(float center_x, float center_y, float radius, Color col);
void draw_line(float start_x, float start_y, float thickness, Color col);
