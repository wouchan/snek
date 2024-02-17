#include "app.hxx"

App::App() {
    m_window = std::make_unique<raylib::Window>(App::SCREEN_WIDTH, App::SCREEN_HEIGHT, "Snek");
    m_window->SetTargetFPS(60);
}

void App::run() {
    while (!m_window->ShouldClose()) {
        App::render();
    }
}

void App::render() {
    m_window->BeginDrawing();

    m_window->ClearBackground(raylib::Color::RayWhite());

    for (i32 x {}; x < Grid::WIDTH; x += 1) {
        for (i32 y {}; y < Grid::HEIGHT; y += 1) {
            raylib::Rectangle rec {
                static_cast<f32>((x + 1) * Grid::TILE_SIZE),
                static_cast<f32>((y + 3) * Grid::TILE_SIZE),
                static_cast<f32>(Grid::TILE_SIZE),
                static_cast<f32>(Grid::TILE_SIZE),
            };

            rec.DrawLines(raylib::Color::LightGray());
        }
    }

    raylib::Rectangle grid_frame {
        static_cast<f32>(Grid::TILE_SIZE),
        static_cast<f32>(3 * Grid::TILE_SIZE),
        static_cast<f32>(Grid::WIDTH * Grid::TILE_SIZE),
        static_cast<f32>(Grid::HEIGHT * Grid::TILE_SIZE),
    };

    grid_frame.DrawLines(raylib::Color::DarkGray(), 3);

    m_window->EndDrawing();
}
