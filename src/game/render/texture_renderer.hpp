#ifndef ESCAPE_TEXTURE_RENDERER_HPP
#define ESCAPE_TEXTURE_RENDERER_HPP

#include <cstdint>

#include "ray.hpp"
#include "error/error.hpp"

namespace esc::render::test {
/**
 * @brief Buffer renderer that is used in tests
 * 
 * Renders the game graphics into predefined buffer, that can be accessed, like normal screen would.
 * Can be used in tests since it allows headless testing.
 */
struct Texture {

    /// Main constructor (creates buffer with defined values)
    Texture(const std::size_t tex_width, const std::size_t tex_height);
    /// Initializes the renderer
    Error init();
    /// Deinitialize the renderer
    Error deinit();
    /// Start rendering into buffer
    Error startRendering();
    /// Stop rendering into buffer
    Error stopRendering();
protected:
    /// Inner buffer dimensions
    std::size_t width, height;
    /// Inner buffer raylib reference
    RenderTexture2D buffer;
};
}

#endif//ESCAPE_TEXTURE_RENDERER_HPP