#include "base.h"
#include <cmath>
#include <cstddef>
#include <limits>

namespace esc::le {

void moveEditor(LevelEditorData& data) {
    if (IsKeyPressed(KeyboardKey::KEY_W)) {
        data.offset.y += 1.0f;
    } else if (IsKeyPressed(KeyboardKey::KEY_S)) {
        data.offset.y -= 1.0f;
    }

    if (IsKeyPressed(KeyboardKey::KEY_A)) {
        data.offset.x += 1.0f;
    } else if (IsKeyPressed(KeyboardKey::KEY_D)) {
        data.offset.x -= 1.0f;
    }
}

LevelEditorData::LevelEditorData(): tiles(100) {
    levelName.reserve(LEVEL_NAME_MAX_SIZE);
}

data::Level LevelEditorData::toLevel() const {
    float minWidth, maxWidth, minHeight, maxHeight;
    minWidth = minHeight = std::numeric_limits<float>::infinity();
    maxWidth = maxHeight = -std::numeric_limits<float>::infinity();
    
    for (const auto& vec:tiles) {
        if (vec.x < minWidth) {
            minWidth = vec.x;
        }
        if (vec.x > maxWidth) {
            maxWidth = vec.x;
        }
        if (vec.y < minHeight) {
            minHeight = vec.y;
        }
        if (vec.y > maxHeight) {
            maxHeight = vec.y;
        }
    }

    std::size_t width, height;
    width = static_cast<std::size_t>(maxWidth - minWidth) + 1;
    height = static_cast<std::size_t>(maxHeight - minHeight) + 1;
    data::Level res(width, height);
    
    for (const auto& tile: tiles) {
        std::size_t x = tile.x - minWidth;
        std::size_t y = tile.y - minHeight;
        res.tiles[x + y * width] = data::Tile::WALL;
    }

    return res;
}

void LevelEditorData::fromLevel(const data::Level& lvl) {
    tiles.clear();
    for (std::size_t y = 0; y < lvl.height; ++y) {
        for (std::size_t x = 0; x < lvl.width; ++x) {
            if (lvl.tiles[x + y * lvl.width] == data::Tile::WALL) {
                tiles.emplace(x, y);
            }
        }
    }
}

}