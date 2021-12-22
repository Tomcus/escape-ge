#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "ray.hpp"
#include "game.hpp"
#include "render/ray_renderer.hpp"
#include "input/ray_input_handler.hpp"

int main() {
#if DEBUG
    SetTraceLogLevel(LOG_TRACE);
#else
    SetTraceLogLevel(LOG_ERROR);
#endif
    esc::Game theGame{esc::input::ray{}, esc::render::ray{}};
    MUST(theGame.run());   
    return 0;
} 