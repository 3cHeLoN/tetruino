#pragma once

#include <chrono>

#include "board.h"
#include "screen_manager.h"
#include "tetromino_factory.h"

#define CLEAR_MS 58

enum GameState
{
    SpawningState,
    CollidedState,
    MovingState,
    ClearingLinesState,
    ShrinkingBoardState,
    PausedState,
    GameOverState,
};

class Game
{
    private:
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = std::chrono::time_point<Clock>;
        TimePoint last_move;
        TimePoint last_clear;
        int clear_column;
        GameState current_state;
        GameState m_old_state;
        bool m_updated = true;
        int m_line_count = 0;
        std::vector<int> full_lines;
        TetrominoFactory factory;
        std::vector<int> line_rates = {800, 716, 633, 550, 466, 383, 300, 216, 133, 100, 83, 66, 50, 33, 16};
        Tetromino next_tetromino;
        int m_level;
    public:
        Game();
        void reset();
        void game_over();
        void setLevel(int level);
        int getLevel();
        void toggle_pause();
        bool has_update() { return m_updated; };
        void unset_update() { m_updated = false; };
        bool update();
        void draw(ScreenManager manager);
        Board board;
        Tetromino tetromino;
        bool move(Direction direction);
        void harddrop();
        bool rotate(RotationDirection direction);
};