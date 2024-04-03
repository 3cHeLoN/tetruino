#pragma once

#include <map>

#include "color.h"
#include "drawable.h"
#include "motions.h"
#include "matrix.h"
#include "screen_manager.h"

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
        Matrix<int>({{0, 1, 1}, {0, 1, 0}, {0, 1, 0}}),
        Matrix<int>({{0, 0, 0}, {1, 1, 1}, {0, 0, 1}}),
        Matrix<int>({{0, 1, 0}, {0, 1, 0}, {1, 1, 0}})  ,
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
        Matrix<int>({{1, 0, 0}, {1, 1, 0}, {0, 1, 0}}),
    }},
    {Z_block, {
        Matrix<int>({{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}),
        Matrix<int>({{0, 0, 1}, {0, 1, 1}, {0, 1, 0}}),
        Matrix<int>({{0, 0, 0}, {1, 1, 0}, {0, 1, 1}}),
        Matrix<int>({{0, 1, 0}, {1, 1, 0}, {1, 0, 0}}),
    }},
};


// const std::map<TetrominoType, Color> colormap
// {
//     {I_block, Color(251, 73, 52)},
//     {O_block, Color(184, 187, 38)},
//     {T_block, Color(250, 189, 47)},
//     {J_block, Color(131, 165, 152)},
//     {L_block, Color(211, 134, 155)},
//     {S_block, Color(142, 192, 124)},
//     {Z_block, Color(235, 219, 178)},
// };

const std::map<TetrominoType, Color> colormap
{
    {I_block, Color(0, 255, 255)},
    {O_block, Color(255, 255, 0)},
    {T_block, Color(128, 0, 128)},
    {J_block, Color(0, 255, 0)},
    {L_block, Color(255, 0, 0)},
    {S_block, Color(0, 0, 255)},
    {Z_block, Color(255, 127, 0)},
};

class Tetromino : public Drawable
{
    private:
        Color m_color;
        int m_row, m_col;
        int m_rotation;
        bool m_visible;
        std::vector<Matrix<int>> m_matrices;
        TetrominoType m_type;
    public:
        Tetromino();
        Tetromino(TetrominoType type);
        void toggle_visible();
        void set_visible(bool visible);
        int width() { return m_matrices[0].numCols(); };
        int height() { return m_matrices[0].numRows(); };
        TetrominoType get_type() { return m_type; };
        int get_row() { return m_row; };
        int get_col() { return m_col; };
        void move(Direction direction);
        Color get_color() { return m_color; };
        void set_color(Color color);
        void set_position(int row, int col);
        void rotate(RotationDirection direction);
        void print();
        int operator()(int row, int col) const;
        int& operator()(int row, int col);
        void draw(ScreenManager &manager) override;
};
