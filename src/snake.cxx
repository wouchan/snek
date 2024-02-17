#include "snake.hxx"

bool Snake::move(Grid& grid, u32& score) {
    TileCoords new_pos { position + dir_to_coords(move_direction) };

    new_pos.x %= Grid::WIDTH;
    new_pos.y %= Grid::HEIGHT;

    if (new_pos.x < 0) {
        new_pos.x += Grid::WIDTH;
    }

    if (new_pos.y < 0) {
        new_pos.y += Grid::HEIGHT;
    }

    grid.set_tile_occupation(position, false);
    grid.set_tile_occupation(new_pos, true);

    position = new_pos;

    auto apple = grid.get_apple();
    if (apple.has_value()) {
        if (position == apple.value()) {
            score += 1;
            grid.consume_apple();
        }
    }

    return true;
}
