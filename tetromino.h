#pragma once

#include "matrix.h"

class Tetromino
{
    public:
        Matrix<int> m_matrix;
        Tetromino(const Matrix<int>& matrix);
};
