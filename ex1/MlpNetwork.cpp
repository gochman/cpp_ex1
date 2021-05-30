//
// Created by user on 23/12/2019.
//

#include "MlpNetwork.h"
#include "Dense.h"

/**
 * @brief Constructor
 * @param weightsArr an array of Matrices representing weights
 * @param biasArr an array of Matrices representing biases
 */
MlpNetwork::MlpNetwork(Matrix weightsArr[], Matrix biasArr[])
{
    for (int i = 0; i < MLP_SIZE; i++)
    {
        _weightsArr[i] = weightsArr[i];
        _biasArr[i] = biasArr[i];
    }


}

/**
 * @brief operator overriding the () operator. gets an image (matrix) and returns digit
 * representing the result of the network process
 * @param img a matrix representing the image
 * @return a Digit object
 */
Digit MlpNetwork::operator()(Matrix &img)
{
    Dense dense0(_weightsArr[0], _biasArr[0], Relu);
    Dense dense1(_weightsArr[1], _biasArr[1], Relu);
    Dense dense2(_weightsArr[2], _biasArr[2], Relu);
    Dense dense3(_weightsArr[3], _biasArr[3], Softmax);

    Matrix &r1 = dense0(img);
    Matrix &r2 = dense1(r1);
    Matrix &r3 = dense2(r2);
    Matrix &r4 = dense3(r3);

    unsigned int maxIndex = _maxCoordinateIndex(r4);
    float probability = r4((int) maxIndex, 0);
    Digit result{maxIndex, probability};

    return result;

}
/**
 * @brief Helper function to calculate the index of the Maximum coordinate in the given vector
 * @param vec a Matrix representing a vector
 * @return integer: the index of the maximum coordinate value
 */
unsigned int MlpNetwork::_maxCoordinateIndex(const Matrix &vec)
{
    float max = 0;
    unsigned int maxIndex = 0;
    for (int i = 0; i < vec.getRows(); i++)
    {
        if (vec(i, 0) > max)
        {
            max = vec(i, 0);
            maxIndex = i;
        }
    }

    return maxIndex;
}


