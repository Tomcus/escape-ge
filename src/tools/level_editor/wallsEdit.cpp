#include "wallsEdit.h"
#include "base.h"

namespace esc::le {

float sqDistance(const Vector2& a, const Vector2& b) {
    float deltaX = a.x - b.x;
    float deltaY = a.y - b.y;
    return deltaX * deltaX + deltaY * deltaY;
}

void tryEmplace(const Vector2 v, Vector2Set& toPlaceIn, const Vector2Set& toCheckIn) {
    if (!toCheckIn.contains(v)) {
        toPlaceIn.emplace(v);
    }
}

void wallEdit(LevelEditorData& data) {
    static Color canPlaceTileMainColor{255, 150, 150, 255};
    // static Color canPlaceTileHighlight{255, 50, 50, 255};

    if (static_cast<std::size_t>(GetMouseY()) > LevelEditorData::LINE_HEIGHT * LevelEditorData::TOOLBOX_LINES) {
        auto paintSizeSq = data.wallEditSize * data.wallEditSize;
        Vector2Set toPlace(10);
        Vector2Set toCheck(10);

        Vector2 tileVector = GetMousePosition();
        tileVector.x = floor(tileVector.x / TILE_SIZE);
        tileVector.y -= LevelEditorData::LINE_HEIGHT * LevelEditorData::TOOLBOX_LINES;
        tileVector.y = floor(tileVector.y / TILE_SIZE);

        toCheck.emplace(tileVector);
        do {
            Vector2Set newToCheck(10);
            for (auto& point:toCheck) {
                if (sqDistance(point, tileVector) < paintSizeSq) {
                    toPlace.emplace(point);
                    tryEmplace({point.x + 1, point.y}, newToCheck, toPlace);
                    tryEmplace({point.x - 1, point.y}, newToCheck, toPlace);
                    tryEmplace({point.x, point.y + 1}, newToCheck, toPlace);
                    tryEmplace({point.x, point.y - 1}, newToCheck, toPlace);
                }
            }
            toCheck = newToCheck;
        } while(!toCheck.empty());

        for (auto& point:toPlace) {
            DrawRectangle(point.x * TILE_SIZE, point.y * TILE_SIZE + LevelEditorData::TOOLBOX_HEIGHT, TILE_SIZE, TILE_SIZE, canPlaceTileMainColor);
        }

        tryAddATile(data, toPlace);
    }
}

void drawWalls(LevelEditorData& data) {
    static Color wallColor{150, 255, 150, 255};

    for (auto tv:data.tiles) {
        tv.x -= data.offset.x;
        tv.y -= data.offset.y;
        if (tv.x >= 0 && tv.y >= 0) {
            int x = tv.x * TILE_SIZE;
            int y = LevelEditorData::LINE_HEIGHT * LevelEditorData::TOOLBOX_LINES + tv.y * TILE_SIZE;
            DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, wallColor);
        }
    }
}

void tryAddATile(LevelEditorData& data, const Vector2Set& toEditWith) {

    if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)) {
        for (auto point: toEditWith) {
            point.x += data.offset.x;
            point.y += data.offset.y;
            data.tiles.emplace(point);
        }
    } else if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT) && data.tiles.size() > 0) {
        for (auto point: toEditWith) {
            point.x += data.offset.x;
            point.y += data.offset.y;
            data.tiles.erase(point);
        }
    }
}

void drawWallToolbox(LevelEditorData& data) {
    GuiSpinner({4, 36, 98, 24}, "test", &data.wallEditSize, 1, 5, false);
}

}