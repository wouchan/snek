#pragma once

#include "grid.hxx"

enum class Direction {
    Up,
    Right,
    Down,
    Left,
};

TileCoords dir_to_coords(const Direction dir);
