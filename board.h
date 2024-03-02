#pragma once

#include "matrix.h"
#include "tetromino.h"

class Board
{
    private:
        Matrix<int> m_matrix;
    public:
        int width, height;
        Board();
        Board(int rows, int cols);
        bool check_block(Tetromino &tetromino);
        Matrix<int> get_slice(int row, int col, int width, int height);
        void clear_block(int row, int col);
        int get_block(int row, int col);
        void clear_lines();
        bool place(Tetromino &tetromino);
        void show();
        std::vector<int> check_lines();
        void fill_line(int row);
};