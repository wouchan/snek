#pragma once

#include <array>

#include "defs.hxx"

struct TileCoords {
    isize x {};
    isize y {};
};

class Grid {
  public:
    static constexpr isize WIDTH { 36 };
    static constexpr isize HEIGHT { 32 };
    static constexpr isize TILE_SIZE { 20 };

  private:
    std::array<std::array<bool, HEIGHT>, WIDTH> m_occupied_tiles {};

  public:
    bool is_tile_occupied(TileCoords coords);
};
