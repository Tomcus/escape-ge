#include "ray_input_handler.hpp"

namespace esc::input {

Error ray::readForEvents() noexcept {
    static Vector2 v2z{0.0f, 0.0f};
    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
        pushEvent(ExitButtonPressedEvent{});
    }
    if (GetMouseDelta() == v2z) {
        pushEvent(MouseMovedEvent{GetMousePosition(), GetMouseDelta()});
    }
    return {};
}

}