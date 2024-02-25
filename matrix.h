#pragma once

#include <iostream>
#include <vector>

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    // Constructors
    Matrix();
    Matrix(size_t rows, size_t cols);
    Matrix(const std::vector<std::vector<T>>& initialData);

    // Accessor
    T operator()(size_t row, size_t col) const;
    T& operator()(size_t row, size_t col);

    // Getters
    size_t numRows() const;
    size_t numCols() const;

    // Print
    void print() const;

    // Matrix multiplication
    Matrix<T> operator*(const Matrix<T>& other) const;
};
