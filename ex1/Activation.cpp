//
// Created by user on 23/12/2019.
//

#include "Activation.h"
#include <math.h>

/**
 * @brief Constructor for Activation Object
 * @param actType (Relu or Softmax)
 */
Activation::Activation(ActivationType actType)
{
    _myActivationType = actType;
}

/**
 * @brief Getter for the ActivationType struct
 * @return Activation Type (Relu or Softmax)
 */
ActivationType Activation::getActivationType()
{
    return _myActivationType;
}

/**
 * @brief () Operator overload for the activation
 * @param input an input matrix
 * @return a ref to a vector representing the result of Activation(input);
 */
Matrix Activation::operator()(const Matrix &input)
{
    if (_myActivationType == Relu)
    {
        Matrix result = _reluFunc(input);
        return result;

    }

    // else: if (_myActivationType == Softmax)
    Matrix result = _softMaxFunc(input);
    return result;

}

/**
 * @brief Helper function that calcs Relu:Real Numbers -> Real numbers
 * @param input a float
 * @return Relu(float)
 */
float Activation::_reluHelperRealNumbers(float input)
{
    if (input >= 0)
    {
        return input;
    }

    return 0;
}

/**
 * @brief Helper function that calculates Relu: Rn-cols -> Rn-cols
 * @param input a vector
 * @return Relu on the vector
 */
Matrix Activation::_reluFunc(const Matrix &input)
{
    Matrix result = Matrix(input.getRows(), input.getCols());

    for (int i = 0; i < result.getRows(); i++)
    {
        result(i, 0) = _reluHelperRealNumbers(input(i, 0));
    }

    return result;
}

/**
 * @brief Helper function that calculates Softmax: Rn-cols -> Rn-cols
 * @param input a vector
 * @return Softmax on the vector
 */
Matrix Activation::_softMaxFunc(const Matrix &input)
{
    float sum = 0;
    Matrix vec(input.getRows(), input.getCols());
    for (int i = 0; i < input.getRows(); i++)
    {
        sum += std::exp(input(i, 0));
        vec(i, 0) = exp(input(i, 0));
    }

    float scalar = 1 / sum;
    // Matrix &result = *new Matrix(input.getRows(), input.getCols());

    Matrix result = vec * scalar;

    return result;
}

