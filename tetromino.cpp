#include <iostream>
#include "tetrominos.h"
#include "tetromino.h"
#include "matrix.h"

Tetromino::Tetromino(const Matrix<int> &matrix)
{
    m_matrix = matrix;
    std::cout << "Creating a block" << "\n";
}
