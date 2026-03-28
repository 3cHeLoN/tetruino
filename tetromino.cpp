#include <iostream>
#include "tetromino.h"
#include "matrix.h"

namespace
{
  const std::map<TetrominoType, std::vector<Matrix<int>>> g_Tetrominos = {
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
                    Matrix<int>({{0, 1, 0}, {0, 1, 0}, {1, 1, 0}}),
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

  const std::map<TetrominoType, Color> g_colormap{
      {I_block, Color(0, 255, 255)},
      {O_block, Color(255, 255, 0)},
      {T_block, Color(128, 0, 128)},
      {J_block, Color(0, 255, 0)},
      {L_block, Color(255, 0, 0)},
      {S_block, Color(0, 0, 255)},
      {Z_block, Color(255, 127, 0)},
  };

  const std::map<TetrominoType, std::vector<Matrix<int>>> &tetrominos()
  {
    return g_Tetrominos;
  }

  const std::map<TetrominoType, Color> &tetromino_colormap()
  {
    return g_colormap;
  }

  Tetromino::Tetromino()
  {
    m_type = I_block;
    m_visible = true;
    m_rotation = 0;
    // Create correctly sized rotation matrices.
    m_matrices = Tetrominos.at(I_block);
    set_position(0, 0);
    m_color = Color(255, 0, 0);
  }

  Tetromino::Tetromino(TetrominoType type)
  {
    m_type = type;
    m_visible = true;
    m_rotation = 0;
    // Create correctly sized rotation matrices.
    m_matrices = Tetrominos.at(type);
    set_position(0, 0);
    m_color = Color(255, 0, 0);
  }

  // void Tetromino::set_visible(bool visible) {
  //   m_visible = visible;
  // }

  // void Tetromino::toggle_visible() {
  //   m_visible = !m_visible;
  // }

  void Tetromino::set_color(Color color)
  {
    m_color = color;
  }

  void Tetromino::set_position(int row, int col)
  {
    m_row = row;
    m_col = col;
  }

  void Tetromino::rotate(RotationDirection direction)
  {
    switch (direction)
    {
    case ClockWise:
      m_rotation = (m_rotation + 1) % 4;
      break;
    case CounterClockWise:
      m_rotation = (4 + m_rotation - 1) % 4;
    }
  }

  void Tetromino::print()
  {
    m_matrices[m_rotation].print();
  }

  int Tetromino::operator()(int row, int col) const
  {
    return m_matrices[m_rotation](row, col);
  }

  int &Tetromino::operator()(int row, int col)
  {
    return m_matrices[m_rotation](row, col);
  }

  void Tetromino::move(Direction direction)
  {
    switch (direction)
    {
    case DirectionLeft:
      m_col--;
      break;
    case DirectionRight:
      m_col++;
      break;
    case DirectionDown:
      m_row++;
      break;
    case DirectionUp:
      m_row--;
      break;
    }
  }

  void Tetromino::draw(ScreenManager &manager)
  {
    if (!isVisible())
    {
      return;
    }
    for (int row = m_row; row < m_row + height(); row++)
    {
      for (int col = m_col; col < m_col + width(); col++)
      {
        int row_local = row - m_row;
        int col_local = col - m_col;

        if ((*this)(row_local, col_local) > 0)
        {
          manager.drawBox(row, col, get_color(), false);
        }
      }
    }
  }