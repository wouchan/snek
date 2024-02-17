#pragma once

#include <memory>

#include <raylib-cpp.hpp>

#include "defs.hxx"
#include "grid.hxx"
#include "snake.hxx"

class App {
  private:
    static constexpr u32 SCREEN_WIDTH { (Grid::WIDTH + 2) * Grid::TILE_SIZE };
    static constexpr u32 SCREEN_HEIGHT { (Grid::HEIGHT + 4) * Grid::TILE_SIZE };

    std::unique_ptr<raylib::Window> m_window {};
    Grid m_grid {};
    Snake m_snake {};

  public:
    App();

    void run();

    void render();
};
