#include "game.h"
#include "motions.h"

#define GAME_OVER_REPEAT 700

std::map<Direction, Direction> reverse_direction = {
    {DirectionLeft, DirectionRight},
    {DirectionRight, DirectionLeft},
    {DirectionUp, DirectionDown},
    {DirectionDown, DirectionUp},
};

std::map<RotationDirection, RotationDirection> reverse_rotation = {
    {ClockWise, CounterClockWise},
    {CounterClockWise, ClockWise},
};

void Game::setLevel(int level)
{
    m_level = level;
    m_line_count = (level - 1) * 10;
}

int Game::getLevel()
{
    return m_level;
}

void Game::reset()
{
    if (current_state != GameOverState)
    {
        return;
    }

    m_level = 0;
    m_line_count = 0;
    board.reset();
    current_state = SpawningState;
}

Game::Game()
{
    setLevel(0);
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
        tetromino = factory.get_block();
        next_tetromino = factory.the_next_block();
        next_tetromino.set_position(0, 12);
        // Set initial position.
        tetromino.set_position(-2, (int)(board.width / 2) - 2);
        current_state = MovingState;
        unset_update();
        break;
    case PausedState:
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - last_move);
        if (duration.count() > line_rates[getLevel()])
        {
            tetromino.toggle_visible();
            last_move = Clock::now();
            m_updated = true;
            // TODO: reset timer at stopping pause.
        }
        break;
    case GameOverState:
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - last_move);
        if (duration.count() > GAME_OVER_REPEAT)
        {
            board.toggle_visible();
            last_move = Clock::now();
            m_updated = true;
            // TODO: reset timer at stopping pause.
        }
        break;
    case MovingState:
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - last_move);
        if (duration.count() > line_rates[getLevel()])
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
        if (m_line_count > (m_level * 10))
        {
            m_level++;
            std::cout << "Advancing to level " << m_level << "!" << '\n';
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
        // TODO: Could this be more elegant?
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

void Game::game_over()
{
    current_state = GameOverState;
}

void Game::toggle_pause()
{
    if (current_state != PausedState)
    {
        std::cout << "Pausing the game!" << '\n';
        m_old_state = current_state;
        current_state = PausedState;
    }
    else
    {
        std::cout << "Resuming game!" << '\n';
        current_state = m_old_state;
        tetromino.set_visible(true);
    }
}

bool Game::move(Direction direction)
{
    if (current_state == PausedState)
    {
        return true;
    }
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
    if (current_state == PausedState)
    {
        return true;
    }
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
    if (current_state == PausedState)
    {
        //return true;
    }
    while (move(DirectionDown))
    {
    }
    m_updated = true;
    current_state = CollidedState;
}

void Game::draw(ScreenManager manager)
{
    manager.set_background(board.background_color);
    manager.clear_screen();
    board.draw(manager);
    tetromino.draw(manager);
    next_tetromino.draw(manager);
    unset_update();
}