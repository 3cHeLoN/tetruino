#include "board.h"

Board::Board()
{
    width = 10;
    height = 20;
    m_matrix = Matrix<int>(height, width);
}

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

bool Board::place(Tetromino &tetromino)
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
            
            // Game over?
            if (row_index < 0)
            {
                return false;
            }

            std::cout << "Writing to row/col " << row_index << "/" << col_index << '\n';
            m_matrix(row_index, col_index) = tetromino(row_local, col_local) * tetromino.get_type();
        }
    }

    return true;
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

    // Loop over tetromino entries
    for (int row_index = row; row_index < row + tetromino.height(); row_index++)
    {
        for (int col_index = col; col_index < col + tetromino.width(); col_index++)
        {
            int row_local = row_index - row;
            int col_local = col_index - col;

            if (row_index < 0)
            {
                continue;
            }

            if (tetromino(row_local, col_local) == 0)
            {
                continue;
            }

            // Out of bounds?
            if ((row_index >= height || col_index >= width || col_index < 0))
            {
                return false;
            }

            // Overlap?
            if (m_matrix(row_index, col_index) > 0)
            {
                return false;
            }
        }
    }
    return true;
}

void Board::check_lines()
{
    int new_row_index = m_matrix.numRows() - 1;
    for (int row_index = m_matrix.numRows() - 1; row_index >= 0; row_index--)
    {
        bool row_is_full = true;
        for (int col_index = 0; col_index < m_matrix.numCols(); col_index++)
        {
            if (m_matrix(row_index, col_index) == 0)
            {
                row_is_full = false;
                break;
            }
        }

        if (!row_is_full)
        {
            // Copy row from above?
            if (new_row_index != row_index)
            {
                for (int col_index = 0; col_index < m_matrix.numCols(); col_index++)
                {
                    m_matrix(new_row_index, col_index) = m_matrix(row_index, col_index);
                }
            }
            new_row_index--;
        }
    }
}