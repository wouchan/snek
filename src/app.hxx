#pragma once

#include <memory>
#include <random>

#include <raylib-cpp.hpp>

#include "defs.hxx"
#include "grid.hxx"
#include "snake.hxx"

enum class GameState {
    PreGame,
    InGame,
    PostGame,
};

class App {
  private:
    static constexpr u32 SCREEN_WIDTH { (Grid::WIDTH + 2) * Grid::TILE_SIZE };
    static constexpr u32 SCREEN_HEIGHT { (Grid::HEIGHT + 4) * Grid::TILE_SIZE };
    static constexpr f64 STARTING_MOVE_TIME { 0.2 };
    static constexpr f64 MOVE_TIME_DECREASE { 0.98 };

    std::unique_ptr<raylib::Window> m_window {};
    std::mt19937 m_rng {};
    GameState m_state { GameState::PreGame };
    Snake m_snake {};
    Grid m_grid {};
    u32 m_score {};
    f64 m_move_time {};
    f64 m_timer {};

  public:
    App();

    void run();

    void init_game();

    void render();

    void poll_input();
};
