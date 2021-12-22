#ifndef ESCAPE_TOOLS_LEVEL_EDITOR_WALLS_EDIT_H
#define ESCAPE_TOOLS_LEVEL_EDITOR_WALLS_EDIT_H

#include "base.h"

#include <cmath>

namespace esc::le {

/// Wall tile size (aka grid size).
static constexpr std::size_t TILE_SIZE = 16;

/// Draws walls preview on Level Editor screen.
void drawWalls(LevelEditorData& data);

/// Add/removes a tile if it can be done.
void tryAddATile(LevelEditorData& data, const Vector2Set& toEditWith);

/// Main wall edit mode function.
void wallEdit(LevelEditorData& data);

/// Draws wall edit specific toolbox ui.
void drawWallToolbox(LevelEditorData& data);

}

#endif//ESCAPE_TOOLS_LEVEL_EDITOR_WALLS_EDIT_H