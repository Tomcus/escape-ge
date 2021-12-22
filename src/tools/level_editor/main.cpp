#define RAYGUI_IMPLEMENTATION

#include "ray.hpp"

#include "base.h"
#include "level/level.hpp"
#include "wallsEdit.h"

#include <cstddef>
#include <cstring>
#include <cmath>

namespace esc::le {

/**
 * \page pageLevelEditor Level Editor
 * \tableofcontents
 * This page contains main documentation about Escape's Level Editor.
 * This program shouldn't be part of the main game distribution.
 * It's sole pourpose is to edit games levels data.
 * If user want to edit the game files, that they can download it from tool bundle.
 * \subsection levelEditorModes Editing modes
 * The editing process of every level can be split into 3 categories:
 * 
 * * The main layout (wall placement)
 * * Enemy placement
 * * Decorating (in 3 separate levels)
 *
 * There are 5 edit modes that corespond to these categories: Wall Edit Mode => Level Layout,
 * Entity placement mode => Enemy placement, Floor Decoration + Interactables + Ceiling Decoration => Decorating
 * \subsection levelEditorModesWall Wall editing mode
 * Editing level's layout is done by placing wall pieces into a 2D grid.
 */

/// Draws Level Editor's toolbox in top of the window
void drawToolbox(LevelEditorData& data) {
    static std::string errorText = "";
    GuiPanel({0, 0, 1280, LevelEditorData::LINE_HEIGHT * LevelEditorData::TOOLBOX_LINES});

    for (std::size_t i = 0; i < MODES_CNT; ++i) {
        bool toggled = GuiToggle({static_cast<float>(i*80 + 4), 4, 78, 24}, EDIT_MODES_NAME[i], data.editMode == static_cast<EDIT_MODE>(i));
        if (toggled) {
            data.editMode = static_cast<EDIT_MODE>(i);
        }
    }

    static constexpr Rectangle textBoxSize{404, 4, 200, 24};
    static char levelName[LevelEditorData::LEVEL_NAME_MAX_SIZE] = "";
    GuiTextBox(textBoxSize, levelName, LevelEditorData::LEVEL_NAME_MAX_SIZE - 1,
               CheckCollisionPointRec(GetMousePosition(), textBoxSize));
    data.levelName = levelName;

    if (GuiButton({606, 4, 78, 24}, "New")) {
        data.tiles.clear();
        data.levelName.clear();
    }
    if (GuiButton({686, 4, 78, 24}, "Save")) {
        auto res = data::save(data.toLevel(), data.levelName + ".lvl");
        if (res.isError()) {
            data.errorText = res.getErrorMessage();
        }
    }
    if (GuiButton({766, 4, 78, 24}, "Load")) {
        auto res = data::loadLevel(data.levelName + ".lvl");
        if (res.isError()) {
            data.errorText = res.getErrorMessage();
        } else {
            data.fromLevel(res.getValue());
        }
    }

    switch(data.editMode) {
        case WALLS:
            drawWallToolbox(data);
        break;
    }
}

/// Draw Error message if error text is not empty
void drawErrorMessage(LevelEditorData& data) {
    static constexpr Rectangle messageBoxPosition{490, 300, 300, 150};
    if (data.errorText.size() > 0) {
        if(GuiMessageBox(messageBoxPosition, "Error", data.errorText.c_str(), "OK") == 1) {
            data.errorText = "";
        }
    }
}

}

int main() {
    using namespace esc::le;
    LevelEditorData tbd;
    InitWindow(1280, 800, "Level Editor");

    SetTargetFPS(60);

    GuiLoadStyleDefault();
    while(!WindowShouldClose()) {
        moveEditor(tbd);

        BeginDrawing();
        ClearBackground({255, 255, 255, 255});

        GuiGrid({0, 0, 1280, 800}, 16, 1);

        drawWalls(tbd);

        if (tbd.errorText.empty()) {
            switch(tbd.editMode) {
                case WALLS:
                    wallEdit(tbd);
                break;
            }
        }

        drawToolbox(tbd);

        drawErrorMessage(tbd);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}