#ifndef ESCAPE_DATA_LEVEL_HPP
#define ESCAPE_DATA_LEVEL_HPP

#include "ray.hpp"
#include "error/error.hpp"

#include <cstddef>
#include <vector>
#include <filesystem>
#include <cstdint>

namespace esc::data {

enum class Tile : std::uint8_t {
    AIR = 0,
    WALL = 1
};

struct [[nodiscard]] Level {
    Level(std::size_t levelWidth, std::size_t levelHeight);
    const std::size_t width;
    const std::size_t height;
    std::vector<Tile> tiles;
};

Error save(const Level& level, const std::filesystem::path& levelFile);
ErrorOr<Level> loadLevel(const std::filesystem::path& levelFile);

};

#endif//ESCAPE_DATA_LEVEL_HPP