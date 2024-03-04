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
    last_clear = Clock::now();
    clear_column = 4;
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
            unset_update();
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
            full_lines = board.check_lines();
            m_line_count += full_lines.size();

            if (m_line_count > level * 10)
            {
                level++;
                std::cout << "Advancing to level " << level << "!" << '\n';
            }

            current_state = full_lines.size() > 0 ? ClearingLinesState : SpawningState;
            break;
        case ClearingLinesState:
            // move tetromino out of sight
            // TODO: fix, ugly
            tetromino.set_position(-1000, (int)(board.width / 2) - 1);
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - last_clear);

            if (duration.count() > CLEAR_MS)
            {
                for (int line : full_lines)
                {
                    board.clear_block(line, clear_column);
                    board.clear_block(line, board.width - clear_column - 1);
                }

                last_clear = Clock::now();
                clear_column--;
                if (clear_column < 0)
                {
                    clear_column = board.width / 2 - 1;
                    current_state = ShrinkingBoardState;
                }
                m_updated = true;
            }
            break;
        case ShrinkingBoardState:
            // refill empty lines
            for (int line : full_lines)
            {
                board.fill_line(line);
            }
            board.clear_lines();
            current_state = SpawningState;
            m_updated = true;
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

    m_updated = success;
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

    m_updated = success;
    return success;
}

void Game::harddrop()
{
    while (move(DirectionDown))
    {}
    m_updated = true;
    current_state = CollidedState;
}