#pragma once

#include "grid.hxx"
#include "movement.hxx"
#include <list>

struct Snake {
    std::list<TileCoords> positions {};
    Direction move_direction {};

    // Returns true if move succeeded, false otherwise.
    bool move(Grid& grid, u32& score);
};
