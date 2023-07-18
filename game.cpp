#include "engine.hpp"
#include "draw.cpp"

static int frame_count = 0;

extern "C" {

EXPORT void game_frame(draw_data_t* draw_data)
{
    draw_frame_start(draw_data);

    // Call draw functions here
    draw_rect(100, 100, 200, 200, Color(1,1,0,1));
    draw_rect(100 + frame_count, 0, 50, 100, Color(0,0.8,1,1));
    draw_rect(300, 400, 300, 240,  Color(1,0,1,1));
    
    frame_count++;
}

}
