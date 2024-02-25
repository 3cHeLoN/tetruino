#pragma once

#include "color.h"
#include "matrix.h"

enum TetrominoType
{
    I_block,
    O_block,
    T_block,
    J_block,
    L_block,
    S_block,
    Z_block,
};

class Tetromino
{
    private:
        Color color;
        int row, col;
    public:
        Matrix<int> m_matrix;
        Tetromino(const Matrix<int>& matrix);
        int get_row() { return row; };
        int get_col() { return col; };
};
