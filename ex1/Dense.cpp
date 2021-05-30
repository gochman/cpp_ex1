//
// Created by user on 23/12/2019.
//

#include "Dense.h"

/**
 * @brief Constructor
 * @param weights matrix representing the weights of this layer
 * @param bias the biad vector of this layer
 * @param actType activationType (Relu or Softmax)
 */
Dense::Dense(Matrix &weights, Matrix &bias, ActivationType actType) :
        _weights(weights), _bias(bias), _layerActivation(*new Activation(actType))
{

}

/**
 * @brief Getter function for weights
 * @return ref for the weights matrix
 */
const Matrix &Dense::getWeights() const
{
    return _weights;
}

/**
 * @brief Getter function for bias
 * @return ref for the bias vector
 */
const Matrix &Dense::getBias() const
{
    return _bias;
}

/**
 * @brief Getter function for weights
 * @return ref for the Activation object
 */
const Activation &Dense::getActivation() const
{
    return _layerActivation;
}

/**
 * @brief Operator() overload
 * @param input a vector (represented by a matrix)
 * @return ref to the vector that is the calculation of: Activation(Weights * input + bias)
 * means layer(input) = Activation(weights * input + bias)
 */
Matrix &Dense::operator()(Matrix &input) const
{
    Matrix &result = *new Matrix(input.getRows(), input.getCols());
    result = _layerActivation((_weights * input) + _bias);

    return result;
}

