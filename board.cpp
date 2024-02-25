#include "board.h"

Board::Board(int rows, int cols)
{
    m_matrix = Matrix<int>(rows, cols);
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

void Board::check_block(Tetromino block, int row, int col)
{

}