#include "matrix.h"

template<typename T>
Matrix<T>::Matrix()
{
    rows = 1;
    cols = 1;
    data.resize(1, std::vector<T>(1));
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<T>(cols));
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& initialData)
    : data(initialData), rows(initialData.size()), cols(initialData[0].size()) {}

template<typename T>
T Matrix<T>::operator()(size_t row, size_t col) const {
    return data[row][col];
}

template<typename T>
T& Matrix<T>::operator()(size_t row, size_t col) {
    return data[row][col];
}

template<typename T>
size_t Matrix<T>::numRows() const {
    return rows;
}

template<typename T>
size_t Matrix<T>::numCols() const {
    return cols;
}

template<typename T>
void Matrix<T>::print() const {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (cols != other.rows) {
        std::cerr << "Matrix dimensions do not match for multiplication." << std::endl;
        return Matrix<T>(0, 0);
    }

    Matrix<T> result(rows, other.cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            result(i, j) = 0;
            for (size_t k = 0; k < cols; ++k) {
                result(i, j) = result(i, j) + data[i][k] * other(k, j);
            }
        }
    }

    return result;
}

template class Matrix<int>;