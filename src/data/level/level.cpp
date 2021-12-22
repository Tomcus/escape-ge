#include "level.hpp"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <istream>

using namespace esc::data;

Level::Level(std::size_t levelWidth, std::size_t levelHeight): width(levelWidth), height(levelHeight), tiles(width*height, Tile::AIR) { }

esc::Error esc::data::save(const Level& level, const std::filesystem::path& levelFile) {
    if (levelFile == ".lvl") {
        return {-1, "LevelSave: Wrong file name. Can't save."};
    }
    if (level.tiles.size() == 0) {
        return {-1, "LevelSave: Can't save empty level"};
    }
    if (level.width == 1 || level.height == 1) {
        return {-1, "LevelSave: Level has to be minimal 2x2."};
    }
    std::ofstream ofs(levelFile);
    if (!ofs.good()) {
        return {-1, "LevelSave: Can't open file for writing."};
    }
    ofs << "1\n";
    ofs << level.width << '\n';
    ofs << level.height << '\n';
    for (std::size_t y = 0; y < level.height; ++y) {
        for (std::size_t x = 0; x < level.width; ++x) {
            switch (level.tiles[x + y * level.width]) {
            case esc::data::Tile::AIR:
                ofs << '_';
            break;
            case esc::data::Tile::WALL:
                ofs << '*';
            break;
            }
        }
        ofs << '\n';
    }
    if (!ofs.good()) {
        return {-1, "LevelSave: While writing level data something went wrong."};
    }
    return {};
}

template <size_t version>
esc::ErrorOr<Level> load(std::istream&) {
    return {-1, "LevelLoad: Unsuported version."};
}

template<>
esc::ErrorOr<Level> load<1>(std::istream& input) {
    std::size_t width, height;
    input >> width;
    input >> height;
    if (!input.good()) {
        return {-1, "LoadLevel: Bad level format (unable to load level's width and height)"};
    }
    Level lvl(width, height);
    char c;
    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            input >> c;
            switch (c) {
                case '*':
                    lvl.tiles[x + y * width] = Tile::WALL;
                break;
                case '_':
                    lvl.tiles[x + y * width] = Tile::AIR;
                break;
                default:
                    return {-1, "LoadLevel: Bad level format (can't parse character)"};
            }
        }
    }
    if (!input.good()) {
        return {-1, "LoadLevel: Bad level format (something wrong with the file)"};
    }
    return lvl;
}

esc::ErrorOr<Level> esc::data::loadLevel(const std::filesystem::path& levelFile) {
    if (!std::filesystem::exists(levelFile)) {
        return {-1, "LoadLevel: No such file."};
    }

    std::size_t version;
    std::ifstream ifs(levelFile);
    ifs >> version;
    switch(version) {
        case 1:
            return load<1>(ifs);
    }

    return {-1, "LoadLevel: Bad level format (can't determine valid version)."};
}