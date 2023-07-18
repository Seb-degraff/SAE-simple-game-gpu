#include <stdint.h> // for uint32_t
#include <stdio.h> // for printf
#include <stdlib.h> // for exit
#include <assert.h>

#include "draw.hpp"

float vertex_buffer[VERT_BUFFER_MAX_FLOATS];
//int   vertex_buffer_used = 0;

uint32_t index_buffer[INDEX_BUFFER_MAX_INT32];
//int      index_buffer_used = 0;

draw_data_t* draw_data;

void draw_frame_start(draw_data_t* _draw_data)
{
    draw_data = _draw_data;
    draw_data->index_buffer = index_buffer;
    draw_data->vertex_buffer = vertex_buffer;
    clear_draw_buffers();
}

void clear_draw_buffers()
{
    draw_data->vertex_buffer_used = 0;
    draw_data->index_buffer_used = 0;
}

void append_vertex(float x, float y, Color col)
{
    assert(draw_data && "Call draw frame start first!");
    assert(draw_data->window_w != 0 && draw_data->window_h != 0 && "Window width and height must be set in passed draw_data_t struct.");

    if ((draw_data->vertex_buffer_used + 7) * sizeof(*vertex_buffer) >= sizeof(vertex_buffer)) {
        printf("Error: vertex buffer full!\n");
        exit(-1);
    }

    vertex_buffer[draw_data->vertex_buffer_used++] = (x / draw_data->window_w) * 2 - 1;
    vertex_buffer[draw_data->vertex_buffer_used++] = (y / draw_data->window_h) * 2 - 1;
    vertex_buffer[draw_data->vertex_buffer_used++] = 0.5f;
    vertex_buffer[draw_data->vertex_buffer_used++] = col.r;
    vertex_buffer[draw_data->vertex_buffer_used++] = col.g;
    vertex_buffer[draw_data->vertex_buffer_used++] = col.b;
    vertex_buffer[draw_data->vertex_buffer_used++] = col.a;
}

void draw_rect(float x, float y, float sx, float sy, Color col)
{
    int start_index = draw_data->vertex_buffer_used / (3 + 4);
    append_vertex(x, y, col);
    append_vertex(x+sx, y, col);
    append_vertex(x+sx, y+sy, col);
    append_vertex(x, y+sy, col);

    if ((draw_data->index_buffer_used + 6) * sizeof(*index_buffer) >= sizeof(index_buffer)) {
        printf("Error: index buffer full!\n");
        exit(-1);
    }

    index_buffer[draw_data->index_buffer_used++] = start_index + 0;
    index_buffer[draw_data->index_buffer_used++] = start_index + 1;
    index_buffer[draw_data->index_buffer_used++] = start_index + 2;

    index_buffer[draw_data->index_buffer_used++] = start_index + 0;
    index_buffer[draw_data->index_buffer_used++] = start_index + 2;
    index_buffer[draw_data->index_buffer_used++] = start_index + 3;
}

void draw_circle(float center_x, float center_y, float radius, Color col)
{
    // to implement
}

void draw_line(float start_x, float start_y, float thickness, Color col)
{
    // to implement
}
