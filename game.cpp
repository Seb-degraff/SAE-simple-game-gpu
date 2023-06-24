#include "engine.hpp"
#include "draw.hpp"

static int frame_count = 0;

void game_frame()
{
    // Call draw functions here
    draw_rect(100, 100, 200, 200, Color(1,1,0,1));
    draw_rect(100 + frame_count, 0, 50, 100, Color(0,0.8,1,1));
    draw_rect(300, 400, 300, 240,  Color(1,0,1,1));
    
    frame_count++;
}
