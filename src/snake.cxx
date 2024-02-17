#include "snake.hxx"

bool Snake::move() {
    TileCoords new_pos { position + dir_to_coords(move_direction) };

    new_pos.x %= Grid::WIDTH;
    new_pos.y %= Grid::HEIGHT;

    if (new_pos.x < 0) {
        new_pos.x += Grid::WIDTH;
    }

    if (new_pos.y < 0) {
        new_pos.y += Grid::HEIGHT;
    }

    position = new_pos;

    return true;
}
