#ifndef ESCAPE_RAY_INPUT_HANDLER_HPP
#define ESCAPE_RAY_INPUT_HANDLER_HPP

#include "error/error.hpp"
#include "input/event.hpp"
#include "ray.hpp"
#include <raylib.h>

namespace esc::input {

struct ray {
    /// Reads for event in current frame
    Error readForEvents() noexcept;
};

}

#endif//ESCAPE_RAY_INPUT_HANDLER_HPP