#include "app.hxx"

#include <chrono>

App::App() {
    m_window = std::make_unique<raylib::Window>(App::SCREEN_WIDTH, App::SCREEN_HEIGHT, "Snek");
    m_window->SetTargetFPS(60);

    m_rng = std::mt19937 { static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count()) };
}

void App::init_game() {
    m_move_time = App::STARTING_MOVE_TIME;
    m_timer = 0;

    m_snake.positions.clear();
    m_grid.clear_tile_occupation();

    TileCoords center { Grid::WIDTH / 2, Grid::HEIGHT / 2 };

    m_snake.positions.emplace_front(center);
    m_grid.set_tile_occupation(center, true);
}

void App::run() {
    while (!m_window->ShouldClose()) {
        switch (m_state) {
            case GameState::PreGame: {
                m_score = 0;

                if (IsKeyPressed(KEY_SPACE)) {
                    init_game();
                    m_state = GameState::InGame;
                }
            } break;
            case GameState::InGame: {
                App::poll_input();

                if (!m_grid.get_apple().has_value()) {
                    m_grid.spawn_apple(m_rng);
                    m_move_time *= App::MOVE_TIME_DECREASE;
                    TraceLog(LOG_INFO, "Current move time: %f", m_move_time);
                }

                m_timer += m_window->GetFrameTime();
                if (m_timer >= m_move_time) {
                    m_timer -= m_move_time;

                    if (!m_snake.move(m_grid, m_score)) {
                        m_state = GameState::PostGame;
                    }
                }
            } break;
            case GameState::PostGame: {
                if (IsKeyPressed(KEY_SPACE)) {
                    m_state = GameState::PreGame;
                }
            } break;
        }

        App::render();
    }
}

void App::render() {
    m_window->BeginDrawing();
    m_window->ClearBackground(raylib::Color::RayWhite());

    // Score
    raylib::DrawText(
        std::to_string(m_score),
        App::SCREEN_WIDTH / 2 - Grid::TILE_SIZE,
        Grid::TILE_SIZE / 2,
        Grid::TILE_SIZE * 2,
        raylib::Color::DarkGray());

    switch (m_state) {
        case GameState::PreGame: {
            raylib::DrawText(
                "Press SPACE to begin",
                App::SCREEN_WIDTH / 2 - Grid::TILE_SIZE * 12,
                App::SCREEN_HEIGHT / 2 - Grid::TILE_SIZE / 2,
                Grid::TILE_SIZE * 2,
                raylib::Color::DarkGray());
        } break;
        case GameState::PostGame: {
            raylib::DrawText(
                "Game over!",
                App::SCREEN_WIDTH / 2 - Grid::TILE_SIZE * 15,
                App::SCREEN_HEIGHT / 2 - Grid::TILE_SIZE * 6,
                Grid::TILE_SIZE * 2,
                raylib::Color::DarkGray());

            raylib::DrawText(
                std::format("You scored {} points", m_score),
                App::SCREEN_WIDTH / 2 - Grid::TILE_SIZE * 15,
                App::SCREEN_HEIGHT / 2 - Grid::TILE_SIZE / 2,
                Grid::TILE_SIZE * 2,
                raylib::Color::DarkGray());

            raylib::DrawText(
                "Press SPACE to continue",
                App::SCREEN_WIDTH / 2 - Grid::TILE_SIZE * 15,
                App::SCREEN_HEIGHT / 2 + Grid::TILE_SIZE * 5,
                Grid::TILE_SIZE * 2,
                raylib::Color::DarkGray());
        } break;
        case GameState::InGame: {
            // Grid
            for (i32 x { 0 }; x < Grid::WIDTH; x += 1) {
                for (i32 y { 0 }; y < Grid::HEIGHT; y += 1) {
                    raylib::Rectangle rec {
                        static_cast<f32>((x + 1) * Grid::TILE_SIZE),
                        static_cast<f32>((y + 3) * Grid::TILE_SIZE),
                        static_cast<f32>(Grid::TILE_SIZE),
                        static_cast<f32>(Grid::TILE_SIZE),
                    };

                    rec.DrawLines(raylib::Color::LightGray());
                }
            }

            // Apple
            auto apple = m_grid.get_apple();
            if (apple.has_value()) {
                raylib::Rectangle apple_rec {
                    static_cast<f32>((apple.value().x + 1) * Grid::TILE_SIZE),
                    static_cast<f32>((apple.value().y + 3) * Grid::TILE_SIZE),
                    static_cast<f32>(Grid::TILE_SIZE),
                    static_cast<f32>(Grid::TILE_SIZE),
                };

                apple_rec.Draw(raylib::Color::Red());
                apple_rec.DrawLines(raylib::Color::DarkPurple(), 3);
            }

            // Snake
            for (const auto& pos : m_snake.positions) {
                raylib::Rectangle snake_rec {
                    static_cast<f32>((pos.x + 1) * Grid::TILE_SIZE),
                    static_cast<f32>((pos.y + 3) * Grid::TILE_SIZE),
                    static_cast<f32>(Grid::TILE_SIZE),
                    static_cast<f32>(Grid::TILE_SIZE),
                };

                snake_rec.Draw(raylib::Color::Green());
                snake_rec.DrawLines(raylib::Color::DarkGreen(), 3);
            }
        } break;
    }

    // Grid frame
    raylib::Rectangle grid_frame {
        static_cast<f32>(Grid::TILE_SIZE),
        static_cast<f32>(3 * Grid::TILE_SIZE),
        static_cast<f32>(Grid::WIDTH * Grid::TILE_SIZE),
        static_cast<f32>(Grid::HEIGHT * Grid::TILE_SIZE),
    };

    grid_frame.DrawLines(raylib::Color::DarkGray(), 3);

    m_window->EndDrawing();
}

void App::poll_input() {
    Direction new_dir { m_snake.move_direction };

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        if (m_snake.move_direction != Direction::Down) {
            new_dir = Direction::Up;
        }
    }

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        if (m_snake.move_direction != Direction::Left) {
            new_dir = Direction::Right;
        }
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        if (m_snake.move_direction != Direction::Up) {
            new_dir = Direction::Down;
        }
    }

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        if (m_snake.move_direction != Direction::Right) {
            new_dir = Direction::Left;
        }
    }

    m_snake.move_direction = new_dir;
}
