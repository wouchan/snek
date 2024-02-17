#pragma once

#include "grid.hxx"
#include "movement.hxx"

struct Snake {
    TileCoords position {};
    Direction move_direction {};

    // Returns true if move succeeded, false otherwise.
    bool move(Grid& grid);
};
