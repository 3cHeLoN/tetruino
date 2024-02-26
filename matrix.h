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
    Matrix<T> get_slice(int row_start, int col_start, int width, int height);
    
    // Print
    void print() const;

    // Matrix operations
    Matrix<T> operator*(const Matrix<T>& other) const;
    Matrix<T> operator+(T value);
    Matrix<T> operator-(T value);
    Matrix<T> operator+(std::vector<T> vec);
    Matrix<T> operator-(std::vector<T> vec);
};
