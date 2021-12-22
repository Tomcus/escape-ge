#include "ray_renderer.hpp"
#include "ray.hpp"
#include <raylib.h>

namespace esc::render {

Error ray::init() {
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Escape");
    ToggleFullscreen();
    return {};
}

Error ray::deinit() {
    CloseWindow();
    return {};
}

Error ray::startRendering() {
    BeginDrawing();
    return {};
}

Error ray::stopRendering() {
    EndDrawing();
    return {};
}

}