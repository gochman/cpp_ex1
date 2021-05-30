//
// Created by user on 23/12/2019.
//

#ifndef EX1_DENSE_H
#define EX1_DENSE_H

#include "Matrix.h"
#include "Activation.h"

/**
 * @brief This class represents a Dense in the model
 */
class Dense
{
public:
    /**
     * @brief Constructor
     * @param weights matrix representing the weights of this layer
     * @param bias the biad vector of this layer
     * @param actType activationType (Relu or Softmax)
     */
    Dense(Matrix &weights, Matrix &bias, ActivationType actType);

    /**
     * @brief Getter function for weights
     * @return ref for the weights matrix
     */
    const Matrix &getWeights() const;

    /**
     * @brief Getter function for bias
     * @return ref for the bias vector
     */
    const Matrix &getBias() const;

    /**
     * @brief Getter function for weights
     * @return ref for the Activation object
     */
    const Activation &getActivation() const;

    /**
     * @brief Operator() overload
     * @param input a vector (represented by a matrix)
     * @return ref to the vector that is the calculation of: Activation(Weights * input + bias)
     * means layer(input) = Activation(weights * input + bias)
     */
    Matrix &operator()(Matrix &input) const;

private:

    Matrix &_weights;
    Matrix &_bias;
    Activation &_layerActivation;


};


#endif //EX1_DENSE_H
