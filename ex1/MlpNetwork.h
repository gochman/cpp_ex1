//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Digit.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784},
                                  {64,  128},
                                  {20,  64},
                                  {10,  20}};
const MatrixDims biasDims[] = {{128, 1},
                               {64,  1},
                               {20,  1},
                               {10,  1}};

// Insert MlpNetwork class here...


/**
 * @brief This class represents a full Network in the model
 */
class MlpNetwork
{
public:

    /**
     * @brief Constructor
     * @param weightsArr an array of Matrices representing weights
     * @param biasArr an array of Matrices representing biases
     */
    MlpNetwork(Matrix weightsArr[], Matrix biasArr[]);

    /**
     * @brief operator overriding the () operator. gets an image (matrix) and returns digit
     * representing the result of the network process
     * @param img a matrix representing the image
     * @return a Digit object
     */
    Digit operator()(Matrix &img);


private:

    Matrix _weightsArr[MLP_SIZE];
    Matrix _biasArr[MLP_SIZE];

    /**
     * @brief Helper function to calculate the index of the Maximum coordinate in the given vector
     * @param vec a Matrix representing a vector
     * @return integer: the index of the maximum coordinate value
     */
    static unsigned int _maxCoordinateIndex(const Matrix &vec);


};


#endif // MLPNETWORK_H
