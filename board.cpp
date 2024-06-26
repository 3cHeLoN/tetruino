#include <bits/stdc++.h>

#include "board.h"
#include "screen_manager.h"

Board::Board() {
  m_visible = true;
  width = 10;
  height = 20;
  m_matrix = Matrix<int>(height, width);
}

Board::Board(int rows, int cols) {
  m_visible = true;
  width = cols;
  height = rows;
  m_matrix = Matrix<int>(rows, cols);
}

void Board::reset()
{
  m_visible = true;
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      m_matrix(row, col) = 0;
    }
  }
}

void Board::toggle_visible()
{
  m_visible = !m_visible;
}

void Board::clear_block(int row, int col) {
  m_matrix(row, col) = 0;
}

int Board::get_block(int row, int col) {
  return m_matrix(row, col);
}

bool Board::place(Tetromino &tetromino) {
  int row = tetromino.get_row();
  int col = tetromino.get_col();

  for (int row_index = row; row_index < row + tetromino.height(); row_index++) {
    for (int col_index = col; col_index < col + tetromino.width(); col_index++) {
      int row_local = row_index - row;
      int col_local = col_index - col;

      if (tetromino(row_local, col_local) == 0) {
        continue;
      }

      // Game over?
      if (row_index < 0) {
        return false;
      }

      // std::cout << "Writing to row/col " << row_index << "/" << col_index << '\n';
      m_matrix(row_index, col_index) = tetromino(row_local, col_local) * tetromino.get_type();
    }
  }

  return true;
}

Matrix<int> Board::get_slice(int row, int col, int width, int height) {
  auto matrix = Matrix<int>(height, width);
  for (int rowIndex = row; rowIndex < row + height; rowIndex++) {
    for (int colIndex = col; colIndex < col + width; colIndex++) {
      auto i = rowIndex - row;
      auto j = colIndex - col;
      matrix(i, j) = m_matrix(rowIndex, colIndex);
    }
  }

  return matrix;
}

bool Board::check_block(Tetromino &tetromino) {
  int row = tetromino.get_row();
  int col = tetromino.get_col();

  // Loop over tetromino entries
  for (int row_index = row; row_index < row + tetromino.height(); row_index++) {
    for (int col_index = col; col_index < col + tetromino.width(); col_index++) {
      int row_local = row_index - row;
      int col_local = col_index - col;

      if (tetromino(row_local, col_local) == 0) {
        continue;
      }

      // Out of bounds?
      if ((row_index >= height || col_index >= width || col_index < 0)) {
        return false;
      }

      if (row_index < 0) {
        continue;
      }

      // Overlap?
      if (m_matrix(row_index, col_index) > 0) {
        return false;
      }
    }
  }
  return true;
}

std::vector<int> Board::check_lines() {
  int line_count = 0;
  auto full_lines = std::vector<int>();

  int new_row_index = m_matrix.numRows() - 1;
  for (int row_index = m_matrix.numRows() - 1; row_index >= 0; row_index--) {
    bool row_is_full = true;
    for (int col_index = 0; col_index < m_matrix.numCols(); col_index++) {
      if (m_matrix(row_index, col_index) == 0) {
        row_is_full = false;
        break;
      }
    }

    if (row_is_full) {
      full_lines.push_back(row_index);
    }
  }

  return full_lines;
}


void Board::clear_lines() {
  int new_row_index = m_matrix.numRows() - 1;
  for (int row_index = m_matrix.numRows() - 1; row_index >= 0; row_index--) {
    bool row_is_full = true;
    for (int col_index = 0; col_index < m_matrix.numCols(); col_index++) {
      if (m_matrix(row_index, col_index) == 0) {
        row_is_full = false;
        break;
      }
    }

    if (!row_is_full) {
      // Copy row from above?
      if (new_row_index != row_index) {
        for (int col_index = 0; col_index < m_matrix.numCols(); col_index++) {
          m_matrix(new_row_index, col_index) = m_matrix(row_index, col_index);
        }
      }
      new_row_index--;
    }
  }
}


void Board::fill_line(int row) {
  for (int col = 0; col < width; col++) {
    m_matrix(row, col) = 1;
  }
}

void Board::draw(ScreenManager &manager) {
  if (!m_visible)
  {
    return;
  }

  manager.set_background(background_color);

  for (int row_index = 0; row_index < height; row_index++) {
    for (int col_index = 0; col_index < width; col_index++) {
      if (get_block(row_index, col_index) != 0) {
        auto tetromino_type = (TetrominoType)get_block(row_index, col_index);
        auto block_color = colormap.at(tetromino_type);
        manager.drawBox(row_index, col_index, block_color);
      }
    }
  }
}