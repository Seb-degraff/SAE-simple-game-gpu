#pragma once
#include "engine.hpp"

void clear_draw_buffers();
void draw_rect(float x, float y, float sx, float sy, Color col);
void draw_circle(float center_x, float center_y, float radius, Color col);
void draw_line(float start_x, float start_y, float thickness, Color col);
