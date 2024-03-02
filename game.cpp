#include "game.h"
#include "motions.h"

std::map<Direction, Direction> reverse_direction =
{
    {DirectionLeft, DirectionRight},
    {DirectionRight, DirectionLeft},
    {DirectionUp, DirectionDown},
    {DirectionDown, DirectionUp},
};

std::map<RotationDirection, RotationDirection> reverse_rotation =
{
    {ClockWise, CounterClockWise},
    {CounterClockWise, ClockWise},
};

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
    bool can_move;
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
                can_move = move(DirectionDown);

                if (!can_move)
                {
                    current_state = CollidedState;
                }

                last_move = Clock::now();
            }
            break;
        case CollidedState:
            success = board.place(tetromino);
            board.check_lines();
            current_state = SpawningState;
            break;
    }

    return success;
}

bool Game::move(Direction direction)
{
    bool success = true;
    tetromino.move(direction);
    if (!board.check_block(tetromino))
    {
        success = false;
        tetromino.move(reverse_direction.at(direction));
    }

    return success;
}

bool Game::rotate(RotationDirection direction)
{
    bool success = true;
    tetromino.rotate(direction);
    if (!board.check_block(tetromino))
    {
        success = false;
        tetromino.rotate(reverse_rotation.at(direction));
    }

    return success;
}