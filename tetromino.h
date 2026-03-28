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

// Accessors for tetromino data (defined in tetromino.cpp)
const std::map<TetrominoType, std::vector<Matrix<int>>> &tetrominos();
const std::map<TetrominoType, Color> &tetromino_colormap();

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
    int &operator()(int row, int col);
    void draw(ScreenManager &manager) override;
};
