#include "movement.hxx"

TileCoords dir_to_coords(const Direction dir) {
    switch (dir) {
        case Direction::Up: {
            return TileCoords { 0, -1 };
        }
        case Direction::Right: {
            return TileCoords { 1, 0 };
        }
        case Direction::Down: {
            return TileCoords { 0, 1 };
        }
        case Direction::Left: {
            return TileCoords { -1, 0 };
        }
    }
}
