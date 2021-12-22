#ifndef ESCAPE_TOOLS_LEVEL_EDITOR_BASE_H
#define ESCAPE_TOOLS_LEVEL_EDITOR_BASE_H

#include "ray.hpp"

#include "level/level.hpp"

#include <cstddef>
#include <cstdint>

#include <unordered_set>
#include <array>
#include <functional>
#include <string>

namespace esc::le {

/// Number of editing modes
static constexpr std::size_t MODES_CNT = 5;

/// Enum of all edit modes, that user can use
enum EDIT_MODE: int {
    /// User can place walls, where it is needed
    WALLS,
    /// Place other entities on the map
    ENEMIES,
    /// Place floor hight decoration - these don't interact with player.
    DEC_LVL_0,
    /// Place player hight decorations - these INTERACT with player - ie. doors, level changers, spell scrolls, ...
    DEC_LVL_1,
    /// Place ceiling decoration - these decoration don't interact with player AND are rendered above the everything else (except UI)
    DEC_LVL_2
};

/// Array of string representation of EDIT_MODE
static constexpr std::array<const char*, MODES_CNT> EDIT_MODES_NAME = {
    "Walls",
    "Enemies",
    "Ground Dec",
    "Interactables",
    "Ceiling Dec"
};

/**
 * @brief THE object that stores all the Level Editor data.
 * 
 * Stores current state of every Level Editor instance.
 * Is [[nodiscard]] to prevent not using it.
 */
struct [[nodiscard]] LevelEditorData {
    /// Line pixel height
    static constexpr std::size_t LINE_HEIGHT = 32;
    /// Number of lines in editor's toolbox
    static constexpr std::size_t TOOLBOX_LINES = 2;
    /// Total toolbox height
    static constexpr std::size_t TOOLBOX_HEIGHT = LINE_HEIGHT * TOOLBOX_LINES;
    /// Max level file's name size
    static constexpr std::size_t LEVEL_NAME_MAX_SIZE = 512;

    /**
     * @brief Construct a new Level Editor Data object.
     * 
     * 
     */
    LevelEditorData();
    /// Deleted copy constructor to prevent accidental copying
    LevelEditorData(const LevelEditorData&) = delete;
    /// Deleted assign operator= to prevent accidental copying
    void operator=(const LevelEditorData&) = delete;

    /// Current edit mode. Defaults to EDIT_MODE::WALLS
    EDIT_MODE editMode{EDIT_MODE::WALLS};
    /// Level editor grid offset.
    Vector2 offset{0.0f, 0.0f};
    /// All placed wall tiles
    Vector2Set tiles;
    /// Currently edited level's name
    std::string levelName{};
    /// Size of the wall placing brush (values from 1 to 5)
    int wallEditSize = 1;
    /// Error text variable. If not empty, then MessageBox shows with given text.
    std::string errorText = "";

    /// Converts current data to data::Level object.
    data::Level toLevel() const;
    /// Loads data from data::Level object.
    void fromLevel(const data::Level& lvl);
};

/// Function that handles Level Editor's offset
void moveEditor(LevelEditorData& data);

}

#endif//ESCAPE_TOOLS_LEVEL_EDITOR_BASE_H