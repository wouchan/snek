#pragma once

#include <memory>

#include <raylib-cpp.hpp>

#include "defs.hxx"

class App {
  private:
    static constexpr u32 SCREEN_WIDTH { 600 };
    static constexpr u32 SCREEN_HEIGHT { 800 };

    std::unique_ptr<raylib::Window> m_window {};

  public:
    App();

    void run();
};
