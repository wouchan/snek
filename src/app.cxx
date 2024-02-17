#include "app.hxx"

App::App() {
    m_window = std::make_unique<raylib::Window>(App::SCREEN_WIDTH, App::SCREEN_HEIGHT, "Snek");
    m_window->SetTargetFPS(60);
}

void App::run() {
    while (!m_window->ShouldClose()) {
        m_window->BeginDrawing();

        m_window->ClearBackground(raylib::Color::RayWhite());

        m_window->EndDrawing();
    }
}
