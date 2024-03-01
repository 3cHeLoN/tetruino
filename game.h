#pragma once

#include <chrono>

#include "board.h"
#include "screen_manager.h"
#include "tetromino_factory.h"

enum GameState
{
    SpawningState,
    CollidedState,
    MovingState,
};

class Game
{
    private:
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = std::chrono::time_point<Clock>;
        TimePoint last_move;
        GameState current_state;
        TetrominoFactory factory;
        std::vector<int> line_rates = {600, 800, 500, 300, 100, 80, 50, 20};
    public:
        Game();
        bool update();
        void draw(ScreenManager manager);
        int level;
        Board board;
        Tetromino tetromino;
        void move_left();
        void move_right();
        void move_down();
        void rotate(bool direction);
};