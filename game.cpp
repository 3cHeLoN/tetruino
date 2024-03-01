#include "game.h"

Game::Game()
{
    level = 0;
    board = Board(20, 10);
    factory = TetrominoFactory();
    current_state = SpawningState;
    last_move = Clock::now();
}

bool Game::update()
{
    bool success = true;
    std::chrono::milliseconds duration;

    switch (current_state)
    {
        case SpawningState:
            tetromino = factory.create_random();
            // Set initial position.
            tetromino.set_position(-2, (int)(board.width / 2) - 1);
            current_state = MovingState;
            break;
        case MovingState:
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - last_move);
            if (duration.count() > line_rates[level])
            {
                tetromino.increase_row(true);

                // Can it move?
                if (!board.check_block(tetromino))
                {
                    // No? Then collided.
                    tetromino.increase_row(false);
                    current_state = CollidedState;
                }
                std::cout << "Moved down" << '\n';
                last_move = Clock::now();
            }
            break;
        case CollidedState:
            std::cout << "Collided!" << '\n';
            success = board.place(tetromino);
            board.check_lines();
            current_state = SpawningState;
            break;
    }

    return success;
}

void Game::move_left()
{
    tetromino.increase_col(false);
    if (!board.check_block(tetromino))
    {
        // undo
        tetromino.increase_col(true);
    }
}


void Game::move_right()
{
    tetromino.increase_col(true);
    if (!board.check_block(tetromino))
    {
        // undo
        tetromino.increase_col(false);
    }
}

void Game::move_down()
{
    tetromino.increase_row(true);
    if (!board.check_block(tetromino))
    {
        // undo
        tetromino.increase_row(false);
    }
}


void Game::rotate(bool direction)
{
    if (direction)
    {
        tetromino.rotate_clockwise();
    }
    else
    {
        tetromino.rotate_counter_clockwise();
    }
    if (!board.check_block(tetromino))
    {
        direction ? tetromino.rotate_counter_clockwise() : tetromino.rotate_clockwise();
    }
}