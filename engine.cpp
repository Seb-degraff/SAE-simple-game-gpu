
#define SOKOL_IMPL
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_log.h"
#include "sokol_glue.h"
#include "triangle-sapp.glsl.h"

#include "engine.hpp"
#include "draw.hpp"

extern "C" {
    __declspec(dllimport) void game_frame(draw_data_t* draw_data);
}


// "Engine" part of the codebase. This means it 
// NOTE: Some code based on the sokol sample "triangle-sapp.c"

// application state
static struct {
    sg_pipeline pip;
    sg_bindings bind;
    sg_pass_action pass_action;
} state;

static void init(void)
{    
    sg_desc desc = (sg_desc){
        .context = sapp_sgcontext(),
        .logger.func = slog_func,
    };
    sg_setup(desc);

    state.bind.vertex_buffers[0] = sg_make_buffer((sg_buffer_desc){
        .size = VERT_BUFFER_BYTE_SIZE,
        .usage = SG_USAGE_DYNAMIC,
        .label = "triangle-vertices",
    });
    
    state.bind.index_buffer = sg_make_buffer((sg_buffer_desc){
        .type = SG_BUFFERTYPE_INDEXBUFFER,
        .size = INDEX_BUFFER_BYTE_SIZE,
        .usage = SG_USAGE_DYNAMIC,
        .label = "triangle-indices",
    });

    // create shader from code-generated sg_shader_desc
    sg_shader shd = sg_make_shader(triangle_shader_desc(sg_query_backend()));

    // create a pipeline object (default render states are fine for triangle)
    sg_pipeline_desc pip_desc = {
        .index_type = SG_INDEXTYPE_UINT32,
        .shader = shd,
        // if the vertex layout doesn't have gaps, don't need to provide strides and offsets
        .layout = {
            .attrs = {
                [ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3,
                [ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4
            }
        },
        .label = "triangle-pipeline"
    };
    state.pip = sg_make_pipeline(pip_desc);

    // a pass action to clear framebuffer to black
    state.pass_action = (sg_pass_action) {
        .colors[0] = { .load_action=SG_LOADACTION_CLEAR, .clear_value={0.0f, 0.0f, 0.0f, 1.0f } }
    };
}

void frame(void)
{
    sg_begin_default_pass(&state.pass_action, sapp_width(), sapp_height());
    sg_apply_pipeline(state.pip);
    sg_apply_bindings(&state.bind);

    draw_data_t dd = {
        .window_w = sapp_width(),
        .window_h = sapp_height(),
    };

    game_frame(&dd);
    
    sg_update_buffer(state.bind.vertex_buffers[0], (sg_range) { .ptr = dd.vertex_buffer, .size = dd.vertex_buffer_used * sizeof(float) });
    sg_update_buffer(state.bind.index_buffer, (sg_range) { .ptr = dd.index_buffer, .size = dd.index_buffer_used * sizeof(uint32_t) });

    sg_draw(0, dd.index_buffer_used, 1);
    sg_end_pass();
    sg_commit();
}

void cleanup(void)
{
    sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[])
{
    (void)argc; (void)argv;
    return (sapp_desc){
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .width = 640,
        .height = 480,
        .window_title = "Triangle (sokol-app)",
        .icon.sokol_default = true,
        .logger.func = slog_func,
        .win32_console_attach = true,
    };
}

