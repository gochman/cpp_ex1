// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <iostream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;


// Insert Matrix class here...
/**
 * @brief Class representing a matrix object in the program
 */
class Matrix
{
public:
    /**
     * @brief Constructs Matrix rows × cols. Inits all elements to 0
     */
    Matrix(int rows, int cols);

    /**
     * @brief Constructs 1×1 Matrix Inits the single element to 0
     */
    Matrix();

    /**
     * @brief Constructs matrix from another Matrix m
     * @param m another matrix to construct from
     */
    Matrix(const Matrix &m);

    /**
     * @brief Destructor
     */
    ~Matrix();


    /**
     * @brief rows getter const version
     * @return content of _rows
     */
    int getRows() const;

    /**
     * @brief cols getter const version
     * @return content of _cols
     */
    int getCols() const;

    /**
     * @brief Transforms a matrix into a column vector. Supports function calling concatenation
     * @return a ref to a vectorized object
     */
    Matrix &vectorize();

    /**
     * @brief Prints matrix elements, no return value. prints space after each element (incl.
     * last element in the row) prints newline after each row (incl. last row)
     */
    void plainPrint();

    /**
     * @brief Implementation of the = operator (override)
     * @param other the other matrix
     * @return a ref to this matrix
     */
    Matrix &operator=(const Matrix &other);

    /**
     * @brief Implementation of the * operator (override). act as Matrix multiplication.
     * this * other
     * @param other the other matrix
     * @return a ref to result
     */
    Matrix operator*(const Matrix &other) const;


    /**
     * @brief Implementation of the * operator (override). act as scalar multiplication from the
     * right
     * this  * scalar
     * @param c a scalar
     * @return a ref to the result
     */
    Matrix operator*(float c) const;

    /**
     * @brief Implementation of the * operator. act as scalar multiplication from the left
     * @param left a const float (scalar)
     * @param right our matrix
     * @return a ref to the result
     */
    friend Matrix operator*(float left, const Matrix &right);


    /**
     * @brief Matrix + operator
     * @param other a matrix to add
     * @return a ref to the result
     */
    Matrix operator+(const Matrix &other) const;

    /**
     * @brief Matrix += operator
     * @param other a matrix to add
     * @return a ref to the result (this)
     */
    Matrix &operator+=(const Matrix &other);

    /**
     * @brief Matrix () operator
     * @param i rows
     * @param j cols
     * @return matrix[i][j]
     */
    float operator()(int i, int j) const;

    /**
    * @brief Matrix () operator
    * @param i rows
    * @param j cols
    * @return matrix[i][j]
    */
    float &operator()(int i, int j);


    /**
     * @brief Matrix [] operator const version
     * @param k
     * @return matrix[i][j] == matrix[i*cols + j];
     */
    float &operator[](int k) const;

    /**
     * @brief Matrix [] operator
     * @param k
     * @return matrix[i][j] == matrix[i*cols + j];
     */
    float &operator[](int k);


    /**
     * @brief read input from ifstream
     * @param is ifstream object
     */
    friend std::ifstream &operator>>(std::ifstream &is, Matrix &matrix);

    /**
     * @brief send to os stream the outputs
     * @param os a stream
     * @param matrix a matrix
     * @return a ref for an ostream
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

private:
    int _rows;
    int _cols;
    float *_mat;

};

#endif //MATRIX_H

