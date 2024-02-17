#include "grid.hxx"

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
