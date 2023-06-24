#include <stdint.h> // for uint32_t
#include <stdio.h> // for printf
#include <stdlib.h> // for exit

#include "draw.hpp"

float vertex_buffer[1000];
int   vertex_buffer_used = 0;

uint32_t index_buffer[1000];
int      index_buffer_used = 0;

void clear_draw_buffers()
{
    vertex_buffer_used = 0;
    index_buffer_used = 0;
}

void append_vertex(float x, float y, Color col)
{
    if ((vertex_buffer_used + 7) * sizeof(*vertex_buffer) >= sizeof(vertex_buffer)) {
        printf("Error: vertex buffer full!\n");
        exit(-1);
    }


    int window_w = sapp_width();
    int window_h = sapp_height();

    vertex_buffer[vertex_buffer_used++] = (x / window_w) * 2 - 1;
    vertex_buffer[vertex_buffer_used++] = (y / window_h) * 2 - 1;
    vertex_buffer[vertex_buffer_used++] = 0.5f;
    vertex_buffer[vertex_buffer_used++] = col.r;
    vertex_buffer[vertex_buffer_used++] = col.g;
    vertex_buffer[vertex_buffer_used++] = col.b;
    vertex_buffer[vertex_buffer_used++] = col.a;
}

void draw_rect(float x, float y, float sx, float sy, Color col)
{
    int start_index = vertex_buffer_used / (3 + 4);
    append_vertex(x, y, col);
    append_vertex(x+sx, y, col);
    append_vertex(x+sx, y+sy, col);
    append_vertex(x, y+sy, col);

    if ((index_buffer_used + 6) * sizeof(*index_buffer) >= sizeof(index_buffer)) {
        printf("Error: index buffer full!\n");
        exit(-1);
    }

    index_buffer[index_buffer_used++] = start_index + 0;
    index_buffer[index_buffer_used++] = start_index + 1;
    index_buffer[index_buffer_used++] = start_index + 2;

    index_buffer[index_buffer_used++] = start_index + 0;
    index_buffer[index_buffer_used++] = start_index + 2;
    index_buffer[index_buffer_used++] = start_index + 3;
}

void draw_circle(float center_x, float center_y, float radius, Color col)
{
    // to implement
}

void draw_line(float start_x, float start_y, float thickness, Color col)
{
    // to implement
}
