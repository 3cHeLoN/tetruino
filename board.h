#pragma once

#include "matrix.h"
#include "tetromino.h"

class Board
{
    private:
        Matrix<int> m_matrix;
    public:
        Board(int rows, int cols);
        void check_block(Tetromino block, int row, int col);
        Matrix<int> get_slice(int row, int col, int width, int height);
        void set_block(int row, int col);
};