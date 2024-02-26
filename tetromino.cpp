#include <iostream>
#include "tetromino.h"
#include "matrix.h"

Tetromino::Tetromino(const std::vector<Matrix<int>> &matrices)
{
    m_rotation = 0;
    // Create correctly sized rotation matrices.
    m_matrices = matrices;
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