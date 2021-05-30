//
// Created by user on 21/12/2019.
//

#include "Matrix.h"

#include <fstream>
#include <iostream>


#define MULTIPLY_ERROR "Please validate your matrices size"
#define ADD_ERROR "Please validate your matrices size - must be same size"
#define SMALL_INPUT_ERROR "The entered Data is smaller than the size of the matrix."
#define BIG_INPUT_ERROR "The entered Data is bigger than the size of the matrix."
#define ACCESS_ERROR "Cannot access matrix in this index."

/**
 * @brief Constructs Matrix rows × cols. Inits all elements to 0
 */
Matrix::Matrix(int rows, int cols) : _rows(rows), _cols(cols)
{

    auto *matrix = new float[_rows * _cols];
    for (int i = 0; i < _rows * _cols; i++)
    {
        matrix[i] = 0.0f;
    }

    _mat = matrix;
}

/**
 * @brief Constructs 1×1 Matrix Inits the single element to 0
 */
Matrix::Matrix() : _rows(1), _cols(1)
{
    auto *matrix = new float[1];
    matrix[0] = 0;

    _mat = matrix;
}

/**
 * @brief Constructs matrix from another Matrix m
 * @param m another matrix to construct from
 */
Matrix::Matrix(const Matrix &m) : _rows(m.getRows()), _cols(m.getCols())
{

    _mat = new float[m.getCols() * m.getRows()];
    for (int i = 0; i < m.getRows() * m.getCols(); i++)
    {
        (*this)[i] = m[i];
    }


}

/**
 * @brief Destructor
 */
Matrix::~Matrix()
{
    delete[] _mat;
}

/**
 * @brief rows getter const version
 * @return content of _rows
 */
int Matrix::getRows() const
{
    return _rows;
}

/**
 * @brief cols getter const version
 * @return content of _cols
 */
int Matrix::getCols() const
{
    return _cols;
}

/**
 * @brief Transforms a matrix into a column vector. Supports function calling concatenation
 * @return a ref to a vectorized object
 */
Matrix &Matrix::vectorize()
{
    _rows = getRows() * getCols();
    _cols = 1;
    return *this;

}

/**
 * @brief Prints matrix elements, no return value. prints space after each element (incl.
 * last element in the row) prints newline after each row (incl. last row)
 */
void Matrix::plainPrint()
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            std::cout << (*this)(i, j) << " ";
        }

        std::cout << std::endl;
    }

}

/**
 * @brief Implementation of the = operator (override)
 * @param other the other matrix
 * @return a ref to this matrix
 */
Matrix &Matrix::operator=(const Matrix &other)
{
    // prevent self-assignment
    if (this == &other)
    {
        return *this;
    }

    // delete mat
    delete[] _mat;

    _rows = other.getRows();
    _cols = other.getCols();


    //re-create mat
    _mat = new float[_rows * _cols];
    for (int i = 0; i < _rows * _cols; i++)
    {
        _mat[i] = other[i];
    }


    return *this;       //TODO NOT SURE ABOUT THIS

}

/**
 * @brief Implementation of the * operator (override). act as Matrix multiplication.
 * this * other
 * @param other the other matrix
 * @return a ref to result
 */
Matrix Matrix::operator*(const Matrix &other) const
{
    // must assure when multiplying matrices
    if (_cols != other.getRows())
    {
        std::cerr << MULTIPLY_ERROR << std::endl;
        std::exit(1);
    }

    // if A size is nxm and B is mxp then result is nxp
    Matrix result = Matrix(_rows, other.getCols());

    for (int i = 0; i < _rows; ++i)
    {
        for (int j = 0; j < other.getCols(); ++j)
        {
            for (int k = 0; k < _cols; ++k)
            {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }

    return result;


}

/**
 * @brief Implementation of the * operator (override). act as scalar multiplication from the
 * right
 * this  * scalar
 * @param c a scalar
 * @return a ref to the result
 */
Matrix Matrix::operator*(const float c) const
{
    Matrix result{_rows, _cols}; // if A size is nxm and B is mxp then result is nxp

    for (int i = 0; i < _rows; ++i)
    {
        for (int j = 0; j < _cols; ++j)
        {
            result(i, j) = c * (*this)(i, j);
        }
    }

    return result;
}

/**
 * @brief Implementation of the * operator. act as scalar multiplication from the left
 * @param left a const float (scalar)
 * @param right our matrix
 * @return a ref to the result
 */
Matrix operator*(const float left, const Matrix &right)
{

    Matrix result = Matrix(right.getRows(), right.getCols());
    // if A's size is nxm and B is mxp then result is nxp

    for (int i = 0; i < right.getRows(); ++i)
    {
        for (int j = 0; j < right.getCols(); ++j)
        {
            result(i, j) = left * right(i, j);
        }
    }

    return result;

}

/**
 * @brief Matrix + operator
 * @param other a matrix to add
 * @return a ref to the result
 */
Matrix Matrix::operator+(const Matrix &other) const
{

    // must assure when adding matrices
    if (_cols != other.getCols() || _rows != other.getRows())
    {
        std::cerr << ADD_ERROR << std::endl;
        std::exit(1);
    }

    Matrix result(_rows, _cols);
    // if A size is nxm and B is mxp then result is nxp

    for (int i = 0; i < _rows; ++i)
    {
        for (int j = 0; j < _cols; ++j)
        {
            (result)(i, j) = (*this)(i, j) + (other)(i, j);
        }
    }

    return result;

}

/**
 * @brief Matrix += operator
 * @param other a matrix to add
 * @return a ref to the result (this)
 */
Matrix &Matrix::operator+=(const Matrix &other)
{
    *this = *this + other;
    return *this;
}

/**
 * @brief Matrix () operator
 * @param i rows
 * @param j cols
 * @return matrix[i][j]
 */
float Matrix::operator()(const int i, const int j) const
{

    if (i >= _rows || j >= _cols || i < 0 || j < 0)
    {
        std::cerr << ACCESS_ERROR << std::endl;
        std::exit(1);
    }
    return _mat[i * _cols + j];

}

/**
 * @brief Matrix () operator
 * @param i rows
 * @param j cols
 * @return matrix[i][j]
 */
float &Matrix::operator()(const int i, const int j)
{
    if (i >= _rows || j >= _cols || i < 0 || j < 0)
    {
        std::cerr << ACCESS_ERROR << std::endl;
        std::exit(1);
    }
    return _mat[(i * _cols) + j];

}

/**
 * @brief Matrix [] operator const version
 * @param k
 * @return matrix[i][j] == matrix[i*cols + j];
 */
float &Matrix::operator[](const int k)
{
    if (k >= _rows * _cols || k < 0)
    {
        std::cerr << ACCESS_ERROR << std::endl;
        std::exit(1);
    }
    return _mat[k];

}

/**
 * @brief Matrix [] operator const version
 * @param k
 * @return matrix[i][j] == matrix[i*cols + j];
 */
float &Matrix::operator[](const int k) const
{
    if (k >= _rows * _cols || k < 0)
    {
        std::cerr << ACCESS_ERROR << std::endl;
        std::exit(1);
    }
    return _mat[k];

}

/**
 * @brief read input from ifstream
 * @param is ifstream object
 */
std::ifstream &operator>>(std::ifstream &is, Matrix &matrix)
{
    is.seekg(0, std::ios::end);
    if (is.tellg() / sizeof(float) != (unsigned long) matrix.getRows() * matrix.getCols())
    {
        std::cerr << "error" << std::endl;
        exit(EXIT_FAILURE);
    }
    is.seekg(0, std::ios::beg);

    float f = 0;
    for (int k = 0; k < (matrix.getRows() * matrix.getCols()); k++)
    {
        is.read((char *) (&f), sizeof(float));
        matrix[k] = f;
    }

    return is;


}

/**
 * @brief send to os stream the outputs
 * @param os a stream
 * @param matrix a matrix
 * @return a ref for an ostream
 */
std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    for (int i = 0; i < matrix.getRows(); i++)
    {
        for (int j = 0; j < matrix.getCols(); j++)
        {
            if (matrix(i, j) <= 0.1)
            {
                os << "  ";
            }
            else
            {
                os << "**";
            }

        }

        os << std::endl;
    }


    return os;

}
