#ifndef ESCAPE_RAY_RENDERER_HPP
#define ESCAPE_RAY_RENDERER_HPP

#include "error/error.hpp"

namespace esc::render {

struct ray {
    /// Initializes the renderer
    Error init();
    /// Deinitialize the renderer
    Error deinit();
    /// Start rendering into buffer
    Error startRendering();
    /// Stop rendering into buffer
    Error stopRendering();
};

}

#endif//ESCAPE_RAY_RENDERER_HPP