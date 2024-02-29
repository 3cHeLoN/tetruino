#include "board.h"

Board::Board(int rows, int cols)
{
    width = cols;
    height = rows;
    m_matrix = Matrix<int>(rows, cols);
}

int Board::get_block(int row, int col)
{
    return m_matrix(row, col);
}

void Board::place(Tetromino &tetromino)
{
    int row = tetromino.get_row();
    int col = tetromino.get_col();

    for (int row_index = row; row_index < row + tetromino.height(); row_index++)
    {
        for (int col_index = col; col_index < col + tetromino.width(); col_index++)
        {
            int row_local = row_index - row;
            int col_local = col_index - col;

            if (tetromino(row_local, col_local) == 0)
            {
                continue;
            }
            
            m_matrix(row_index, col_index) = tetromino(row_local, col_local) * tetromino.get_type();
        }
    }
}

Matrix<int> Board::get_slice(int row, int col, int width, int height)
{
    auto matrix = Matrix<int>(height, width);
    for (int rowIndex = row; rowIndex < row + height; rowIndex++)
    {
        for (int colIndex = col; colIndex < col + width; colIndex++)
        {
            auto i = rowIndex - row;
            auto j = colIndex - col;
            matrix(i, j) = m_matrix(rowIndex, colIndex);
        }
    }
    
    return matrix;
}

bool Board::check_block(Tetromino &tetromino)
{
    int row = tetromino.get_row();
    int col = tetromino.get_col();

    for (int row_index = row; row_index < row + tetromino.height(); row_index++)
    {
        for (int col_index = col; col_index < col + tetromino.width(); col_index++)
        {
            if (row_index >= height || col_index >= width)
            {
                return false;
            }

            if (tetromino(row_index - row, col_index - col) & m_matrix(row_index, col_index))
            {
                // overlap
                return false;
            }
        }
    }
    return true;
}