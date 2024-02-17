#include "snake.hxx"

#include "raylib.h"

bool Snake::move(Grid& grid, u32& score) {
    TileCoords new_pos { positions.front() + dir_to_coords(move_direction) };

    new_pos.x %= Grid::WIDTH;
    new_pos.y %= Grid::HEIGHT;

    if (new_pos.x < 0) {
        new_pos.x += Grid::WIDTH;
    }

    if (new_pos.y < 0) {
        new_pos.y += Grid::HEIGHT;
    }

    if (grid.is_tile_occupied(new_pos)) {
        return false;
    }

    grid.set_tile_occupation(new_pos, true);

    positions.emplace_front(new_pos);

    auto apple = grid.get_apple();
    if (apple.has_value()) {
        if (positions.front() == apple.value()) {
            score += 1;
            grid.consume_apple();
            TraceLog(LOG_INFO, "Apple collected! Current score: %d", score);
        } else {
            grid.set_tile_occupation(positions.back(), false);
            positions.pop_back();
        }
    }

    return true;
}
