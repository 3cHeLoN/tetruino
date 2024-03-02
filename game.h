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
        bool m_updated = true;
        TetrominoFactory factory;
        std::vector<int> line_rates = {1000, 793, 617, 472, 355, 262, 189, 134, 93, 64, 42, 28, 18, 11, 7};
    public:
        Game();
        bool has_update() { return m_updated; };
        void unset_update() { m_updated = false; };
        bool update();
        void draw(ScreenManager manager);
        int level;
        Board board;
        Tetromino tetromino;
        bool move(Direction direction);
        bool rotate(RotationDirection direction);
};