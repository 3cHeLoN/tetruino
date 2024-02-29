#include <iostream>
#include "tetromino.h"
#include "matrix.h"

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

void Tetromino::rotate_clockwise()
{
    m_rotation = (m_rotation + 1) % 4;
}

void Tetromino::rotate_counter_clockwise()
{
    m_rotation = (4 + m_rotation - 1) % 4;
}

void Tetromino::print()
{
    std::cout << "Showing rotation " << m_rotation << '\n';
    m_matrices[m_rotation].print();
}

int Tetromino::operator()(int row, int col) const {
    return m_matrices[m_rotation](row, col);
}

int& Tetromino::operator()(int row, int col) {
    return m_matrices[m_rotation](row, col);
}