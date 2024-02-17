#include "grid.hxx"

TileCoords TileCoords::operator+(const TileCoords other) const {
    return TileCoords { this->x + other.x, this->y + other.y };
}

bool TileCoords::operator==(const TileCoords other) const {
    return (this->x == other.x && this->y == other.y);
}

bool Grid::is_tile_occupied(TileCoords coords) {
    coords.x %= Grid::WIDTH;
    coords.y %= Grid::HEIGHT;

    if (coords.x < 0) {
        coords.x += Grid::WIDTH;
    }

    if (coords.y < 0) {
        coords.y += Grid::HEIGHT;
    }

    return m_occupied_tiles[coords.x][coords.y];
}

void Grid::set_tile_occupation(TileCoords coords, bool occupied) {
    m_occupied_tiles[coords.x][coords.y] = occupied;
}

void Grid::clear_tile_occupation() {
    for (i32 x { 0 }; x < Grid::WIDTH; x += 1) {
        for (i32 y { 0 }; y < Grid::HEIGHT; y += 1) {
            m_occupied_tiles[x][y] = false;
        }
    }
}

void Grid::spawn_apple(std::mt19937& rng) {
    bool apple_placed { false };
    while (!apple_placed) {
        i32 x { die_width(rng) };
        i32 y { die_height(rng) };

        if (!is_tile_occupied({ x, y })) {
            m_apple = { x, y };
            apple_placed = true;
        }
    }
}

std::optional<TileCoords> Grid::get_apple() {
    return m_apple;
}

void Grid::consume_apple() {
    m_apple.reset();
}
