#pragma once

#include <map>

#include "color.h"
#include "matrix.h"

enum TetrominoType
{
    I_block = 1,
    O_block = 2,
    T_block = 3,
    J_block = 4,
    L_block = 5,
    S_block = 6,
    Z_block = 7,
};

const std::map<TetrominoType, std::vector<Matrix<int>>> Tetrominos = {
    {I_block, {
        Matrix<int>({{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}),
        Matrix<int>({{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}}),
        Matrix<int>({{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}}),
        Matrix<int>({{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}),
    }},
    {O_block, {
        Matrix<int>({{1, 1}, {1, 1}}),
        Matrix<int>({{1, 1}, {1, 1}}),
        Matrix<int>({{1, 1}, {1, 1}}),
        Matrix<int>({{1, 1}, {1, 1}}),
    }},
    {T_block, {
        Matrix<int>({{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}),
        Matrix<int>({{0, 1, 0}, {0, 1, 1}, {0, 1, 0}}),
        Matrix<int>({{0, 0, 0}, {1, 1, 1}, {0, 1, 0}}),
        Matrix<int>({{0, 1, 0}, {1, 1, 0}, {0, 1, 0}}),
    }},
    {J_block, {
        Matrix<int>({{1, 0, 0}, {1, 1, 1}, {0, 0, 0}}),
        Matrix<int>({{0, 1, 0}, {0, 1, 0}, {0, 1, 1}}),
        Matrix<int>({{0, 0, 0}, {1, 1, 1}, {1, 0, 0}}),
        Matrix<int>({{1, 1, 0}, {0, 1, 0}, {1, 1, 0}}),
    }},
    {L_block, {
        Matrix<int>({{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}),
        Matrix<int>({{0, 1, 0}, {0, 1, 0}, {0, 1, 1}}),
        Matrix<int>({{0, 0, 0}, {1, 1, 1}, {1, 0, 0}}),
        Matrix<int>({{1, 1, 0}, {0, 1, 0}, {0, 1, 0}}),
    }},
    {S_block, {
        Matrix<int>({{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}),
        Matrix<int>({{0, 1, 0}, {0, 1, 1}, {0, 0, 1}}),
        Matrix<int>({{0, 0, 0}, {0, 1, 1}, {1, 1, 0}}),
        Matrix<int>({{1, 0, 0}, {1, 1, 0}, {1, 0, 0}}),
    }},
    {Z_block, {
        Matrix<int>({{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}),
        Matrix<int>({{0, 0, 1}, {0, 1, 1}, {0, 1, 0}}),
        Matrix<int>({{0, 0, 0}, {1, 1, 0}, {0, 1, 1}}),
        Matrix<int>({{0, 1, 0}, {1, 1, 0}, {1, 0, 0}}),
    }},
};

const std::map<TetrominoType, Color> colormap
{
    {I_block, Color(253, 63, 89)},
    {O_block, Color(255, 200, 46)},
    {T_block, Color(254, 251, 52)},
    {J_block, Color(83, 218, 63)},
    {L_block, Color(1, 237, 250)},
    {S_block, Color(234, 20, 28)},
    {Z_block, Color(254, 72, 128)},
};


class Tetromino
{
    private:
        Color m_color;
        int m_row, m_col;
        int m_rotation;
        std::vector<Matrix<int>> m_matrices;
        TetrominoType m_type;
    public:
        Tetromino();
        Tetromino(TetrominoType type);
        int width() { return m_matrices[0].numCols(); };
        int height() { return m_matrices[0].numRows(); };
        TetrominoType get_type() { return m_type; };
        int get_row() { return m_row; };
        int get_col() { return m_col; };
        void increase_row(bool direction);
        void increase_col(bool direction);
        Color get_color() { return m_color; };
        void set_color(Color color);
        void set_position(int row, int col);
        void rotate_clockwise();
        void rotate_counter_clockwise();
        void print();
        int operator()(int row, int col) const;
        int& operator()(int row, int col);
};
