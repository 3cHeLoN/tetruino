#include <iostream>
#include "tetromino.h"
#include "matrix.h"

Tetromino::Tetromino()
{
    m_type = I_block;
    m_rotation = 0;
    // Create correctly sized rotation matrices.
    m_matrices = Tetrominos.at(I_block);
    set_position(0, 0);
    m_color = Color(255, 0, 0);
}

Tetromino::Tetromino(TetrominoType type)
{
    m_type = type;
    m_rotation = 0;
    // Create correctly sized rotation matrices.
    m_matrices = Tetrominos.at(type);
    set_position(0, 0);
    m_color = Color(255, 0, 0);
}

void Tetromino::set_color(Color color)
{
    m_color = color;
}

void Tetromino::set_position(int row, int col)
{
    m_row = row;
    m_col = col;
}

void Tetromino::rotate(RotationDirection direction)
{
    switch(direction)
    {
        case ClockWise:
            m_rotation = (m_rotation + 1) % 4;
            break;
        case CounterClockWise:
            m_rotation = (4 + m_rotation - 1) % 4;
    }
}

void Tetromino::print()
{
    m_matrices[m_rotation].print();
}

int Tetromino::operator()(int row, int col) const {
    return m_matrices[m_rotation](row, col);
}

int& Tetromino::operator()(int row, int col) {
    return m_matrices[m_rotation](row, col);
}

void Tetromino::move(Direction direction)
{
    switch(direction)
    {
        case DirectionLeft:
            m_col--;
            break;
        case DirectionRight:
            m_col++;
            break;
        case DirectionDown:
            m_row++;
            break;
        case DirectionUp:
            m_row--;
            break;
    }
}


void Tetromino::draw(ScreenManager &manager)
{
    for (int row = m_row; row < m_row + height(); row++)
    {
        for (int col = m_col; col < m_col + width(); col++)
        {
            int row_local = row - m_row;
            int col_local = col - m_col;

            if ((*this)(row_local, col_local) > 0)
            {
                manager.drawBox(row, col, get_color());
            }
        }
    }
}