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
        int m_rotation;
        
    public:
        std::vector<Matrix<int>> m_matrices;
        Tetromino(const std::vector<Matrix<int>>& matrices);
        int get_row() { return row; };
        int get_col() { return col; };
        void rotate_clockwise();
        void rotate_counter_clockwise();
        void print();
};
