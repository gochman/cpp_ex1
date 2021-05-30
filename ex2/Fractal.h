//
// Created by user on 02/01/2020.
//

#include <string>
#include <vector>

using namespace std;


#ifndef FRACTALDRAWER_FRACTAL_H
#define FRACTALDRAWER_FRACTAL_H


/**
 * @brief This class represents a parser. the Parser role is to get a path, and return a list of
 * Fractals, if the file is in the right format specified in the exercise.
 */
class Parser
{
public:


    /**
     * @brief Constructor
     * @param path
     */
    explicit Parser(string &path);

    /**
     * @brief return a vector of vector of ints representing the fractals data.
     */
    vector<vector<int>> fileParse();

private:

    string _path;

    /**
     * @brief Validate that file is legal: file exits, file not empty, values are legal, has only
     * 2 cols
     */
    void fileValidate();


    /**
     * @brief Helper function to determine if a file is empty
     * @param pFile a file input stream
     * @return true if file is empty. false otherwise.
     */
    static bool is_empty(std::ifstream &pFile);
};


/**
 * @brief  this class represents a Fractal.
 */
class Fractal
{
public:
    /**
     * @brief Constructor for Fractal
     * @param dimension dimension of fractal
     * @param edge edge size
     * @param representation array of bools representing the frac
     */
    explicit Fractal(int dimension, int edge, vector<vector<bool>> *representation);

    /**
     * @brief free the resources of the fractal (specifically the representation)
     */
    ~Fractal();

    /**
     * @brief prints a fractal in the obvious way: "#" for true, " " for false;
     */
    void printFractal();


private:
    int _dimension;
    int _edge;
    vector<vector<bool>> *_representation;


    /**
     * @brief ger the representation of the frac
     * @return
     */
    vector<vector<bool>> *getRep();


};


/**
 * @brief Derived class of Fractal. this class represents a Sierpinski Triangle.
 */
class SierTriangle : public Fractal
{
public:
    /**
     * @brief Constructor
     * @param dimension dim of the Sierpinski Triangle
     */
    explicit SierTriangle(int dimension);


private:
    /**
     * @brief This copyMachine gets a ref to a bool 2d array and returns sierpinski version of
     * it, one dimension bigger.
     * NOTE: the memory frees the memory of the smaller array in the end.
     * @param small the ref for the small array
     * @return the bigger array ref
     */
    static vector<vector<bool>> *copyMachine(vector<vector<bool>> &small);

    /**
     * @brief Recursive function that creates a Sierpinski Triangle Grid(Representation) of a
     * certain dimension
     * @param dim the given dimension
     * @return a ref for the final grid with dimension dim.
     */
    static vector<vector<bool>> *createGrid(int dim);


};


/**
 * @brief Derived class of Fractal. this class represents a Sierpinski Carpet.
 */
class SierCarpet : public Fractal
{
public:
    /**
     * @brief Constructor
     * @param dimension dim of the Sierpinski Carpet
     */
    explicit SierCarpet(int dimension);


private:
    /**
     * @brief This copyMachine gets a ref to a bool 2d array and returns sierpinski carpet
     * version of it, one dimension bigger.
     * NOTE: the memory frees the memory of the smaller array in the end.
     * @param small the ref for the small array
     * @return the bigger array ref
     */
    static vector<vector<bool>> *copyMachine(vector<vector<bool>> &small);

    /**
     * @brief Recursive function that creates a Sierpinski Carpet Grid(Representation) of a
     * certain dimension
     * @param dim the given dimension
     * @return a ref for the final grid with dimension dim.
     */
    static vector<vector<bool>> *createGrid(int dim);


};


/**
 * @brief Derived class of Fractal. this class represents a Vicsek Fractal.
 */
class Vicsek : public Fractal
{
public:
    /**
     * @brief Constructor
     * @param dimension dim of the Sierpinski Carpet
     */
    explicit Vicsek(int dimension);


private:
    /**
     * @brief This copyMachine gets a ref to a bool 2d array and returns Vicsek Fractal
     * version of it, one dimension bigger.
     * NOTE: the memory frees the memory of the smaller array in the end.
     * @param small the ref for the small array
     * @return the bigger array ref
     */
    static vector<vector<bool>> *copyMachine(vector<vector<bool>> &small);

    /**
     * @brief Recursive function that creates a Vicsek Grid(Representation) of a
     * certain dimension
     * @param dim the given dimension
     * @return a ref for the final grid with dimension dim.
     */
    static vector<vector<bool>> *createGrid(int dim);


};

/**
 * @brief This class gets data list, and creates objects of Fractals
 */
class FractalFactory
{

public:
    /**
     * @brief Constructor for the factory
     * @param dataList pairs of (FractalType, dimension) in a list.
     */
    explicit FractalFactory(vector<vector<int>> dataList);


    /**
     * @brief Fractal List Generator
     * @return a list of pointers for fractals. (has to be pointers so that they can be freed)
     */
    vector<Fractal *> &generateFractalList();

private:

    vector<vector<int>> _dataList;
};


#endif //FRACTALDRAWER_FRACTAL_H
