
#define SOKOL_IMPL
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_log.h"
#include "sokol_glue.h"
#include "triangle-sapp.glsl.h"

#include "engine.hpp"
#include "draw.cpp"


void game_frame();

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
        .size = sizeof(vertex_buffer),
        .usage = SG_USAGE_DYNAMIC,
        .label = "triangle-vertices",
    });
    
    state.bind.index_buffer = sg_make_buffer((sg_buffer_desc){
        .type = SG_BUFFERTYPE_INDEXBUFFER,
        .size = sizeof(index_buffer),
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
    // clear draw.cpp buffers
    clear_draw_buffers();

    game_frame();

    // update vertex and index buffer on the GPU
    sg_update_buffer(state.bind.vertex_buffers[0], (sg_range) { .ptr = vertex_buffer, .size = vertex_buffer_used * sizeof(*vertex_buffer) });
    sg_update_buffer(state.bind.index_buffer, (sg_range) { .ptr = index_buffer, .size = index_buffer_used * sizeof(*index_buffer) });

    // render
    sg_begin_default_pass(&state.pass_action, sapp_width(), sapp_height());
    sg_apply_pipeline(state.pip);
    sg_apply_bindings(&state.bind);
    sg_draw(0, index_buffer_used, 1);
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
    };
}

