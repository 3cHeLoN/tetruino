#pragma once

#include "color.h"
#include "matrix.h"
#include "tetromino.h"
#include "screen_manager.h"
#include "drawable.h"

class Tetromino;

class Board : public Drawable
{
    private:
        Matrix<int> m_matrix;
    public:
        Color background_color = Color(40, 40, 40);
        int width, height;
        Board();
        Board(int rows, int cols);
        void draw(ScreenManager &manager) override;
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