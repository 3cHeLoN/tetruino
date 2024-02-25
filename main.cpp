#include <iostream>
#include <vector>
#include <string>

#include "tetromino_factory.h"
#include "tetromino.h"


int main()
{
    auto factory = new TetrominoFactory();
    auto tetromino = factory->create("l");
    tetromino.m_matrix.print();
}