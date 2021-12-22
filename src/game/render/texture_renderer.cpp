#include "texture_renderer.hpp"
#include <raylib.h>

namespace esc::render::test {

Texture::Texture(const std::size_t tex_width, const std::size_t tex_height): width(tex_width), height(tex_height) { }

Error Texture::init() {
    buffer = LoadRenderTexture(static_cast<int>(width), static_cast<int>(height));
    return {};
}

Error Texture::deinit() {
    UnloadRenderTexture(buffer);
    return {};
}

Error Texture::startRendering() {
    BeginTextureMode(buffer);
    return {};
}

Error Texture::stopRendering() {
    EndTextureMode();
    return {};
}

}