#pragma once

#include <array>
#include <optional>
#include <random>

#include "defs.hxx"

struct TileCoords {
    isize x {};
    isize y {};

    TileCoords operator+(const TileCoords other) const;
    bool operator==(const TileCoords other) const;
};

class Grid {
  public:
    static constexpr isize WIDTH { 36 };
    static constexpr isize HEIGHT { 32 };
    static constexpr isize TILE_SIZE { 20 };

  private:
    std::array<std::array<bool, HEIGHT>, WIDTH> m_occupied_tiles {};
    std::uniform_int_distribution<> die_width { 0, Grid::WIDTH - 1 };
    std::uniform_int_distribution<> die_height { 0, Grid::HEIGHT - 1 };
    std::optional<TileCoords> m_apple {};

  public:
    bool is_tile_occupied(TileCoords coords);

    void set_tile_occupation(TileCoords coords, bool occupied);

    void spawn_apple(std::mt19937& rng);

    std::optional<TileCoords> get_apple();

    void consume_apple();
};
