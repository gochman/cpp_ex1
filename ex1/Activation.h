//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};

/**
 * @brief Class representing an Activation function in the model
 */
class Activation
{
public:

    /**
     * @brief Constructor for Activation Object
     * @param actType (Relu or Softmax)
     */
    explicit Activation(ActivationType actType);

    /**
     * @brief Getter for the ActivationType struct
     * @return Activation Type (Relu or Softmax)
     */
    ActivationType getActivationType();

    /**
     * @brief () Operator overload for the activation
     * @param input an input matrix
     * @return a ref to a vector representing the result of Activation(input);
     */
    Matrix operator()(const Matrix &input);


private:
    ActivationType _myActivationType;

    /**
     * @brief Helper function that calcs Relu:Real Numbers -> Real numbers
     * @param input a float
     * @return Relu(float)
     */
    static float _reluHelperRealNumbers(float input);

    /**
     * @brief Helper function that calculates Relu: Rn-cols -> Rn-cols
     * @param input a vector
     * @return Relu on the vector
     */
    static Matrix _reluFunc(const Matrix &input);

    /**
     * @brief Helper function that calculates Softmax: Rn-cols -> Rn-cols
     * @param input a vector
     * @return Softmax on the vector
     */
    static Matrix _softMaxFunc(const Matrix &input);

};


#endif //ACTIVATION_H
