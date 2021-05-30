//
// Created by Yoav Gochman on 02/01/2020.
//

#include "Fractal.h"
#include <iostream>
#include <regex>
#include <string>
#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>
#include <math.h>
#include <fstream>

#define INVALID_INPUT_MSG "Invalid input"
#define LEGAL_INPUT_REGEX "^([1-3]),([1-6])$"
#define SIERPINSKI_CARPET_MULTIPLIER 3
#define SIERPINSKI_TRIANGLE_MULTIPLIER 2
#define VICSEK_MULTIPLIER 3
#define SIERPINSKI_CARPET_SERIAL_NUM 1
#define SIERPINSKI_TRIANGLE_SERIAL_NUM 2
#define VICSEK_SERIAL_NUM 3


using namespace std;


/*
 *   ******** Parser ******** 
 */


Parser::Parser(string &path) :
        _path(path)
{
    fileValidate();
    fileParse();
}

void Parser::fileValidate()
{

    ifstream file(_path);

    if (file.fail())
    {
        cerr << INVALID_INPUT_MSG << endl;
        exit(EXIT_FAILURE);
    }


    if (is_empty(file))
    {
        exit(EXIT_SUCCESS);
    }


    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            // strip line from new lines
            boost::replace_all(line, "\r", "");
            boost::replace_all(line, "\n", "");


            regex re(LEGAL_INPUT_REGEX);
            if (!regex_match(line, re))
            {
                cerr << INVALID_INPUT_MSG << endl;
                exit(EXIT_FAILURE);
            }

        }
    }

    file.close();

}

bool Parser::is_empty(std::ifstream &pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();

}

vector<vector<int>> Parser::fileParse()
{
    vector<vector<int>> result;
    std::ifstream file(_path);

    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            boost::replace_all(line, "\r", "");
            boost::replace_all(line, "\n", "");

            regex re(LEGAL_INPUT_REGEX);
            smatch match;

            if (regex_search(line, match, re))
            {
                int fractalType, dim;
                fractalType = boost::lexical_cast<int>(match.str(1));
                dim = boost::lexical_cast<int>(match.str(2));

                result.push_back({fractalType, dim});
            }

        }
    }

    file.close();
    return result;

}


/*
 *   ******** Fractal ******** 
 */

Fractal::Fractal(int dimension, int edge, vector<vector<bool>> *representation) : _dimension(
        dimension),
                                                                                  _edge(edge),
                                                                                  _representation(
                                                                                          representation)
{
}

void Fractal::printFractal()
{
    vector<vector<bool>> *rep = getRep();
    for (int i = 0; i < _edge; i++)
    {
        for (int j = 0; j < _edge; j++)
        {
            if ((*rep)[i][j] == true)
            {
                cout << "#";
            }
            else
            {
                cout << " ";
            }

        }

        cout << endl;
    }

    cout << endl;

}

vector<vector<bool>> *Fractal::getRep()
{
    return _representation;
}


Fractal::~Fractal()
{
    delete _representation;

}

/*
 *   ******** SierTriangle ******** 
 */

vector<vector<bool>> *SierTriangle::copyMachine(vector<vector<bool>> &small)
{
    int smallEdge = small.size();
    int newEdge = smallEdge * SIERPINSKI_TRIANGLE_MULTIPLIER;


    auto result = new vector<vector<bool>>(newEdge, vector<bool>(newEdge,
                                                                 false));

    for (int cubeRows = 0; cubeRows < SIERPINSKI_TRIANGLE_MULTIPLIER; cubeRows++)
    {

        for (int cubeCols = 0; cubeCols < SIERPINSKI_TRIANGLE_MULTIPLIER; cubeCols++)
        {


            if ((cubeRows + cubeCols) != 2)
            {
                for (int i = 0; i < smallEdge; i++)
                {
                    for (int j = 0; j < smallEdge; j++)
                    {
                        (*result)[i + (cubeRows * smallEdge)][j +
                                                              (cubeCols * smallEdge)] = small[i][j];
                    }
                }
            }


        }

    }


    delete &small;
    return result;

}


vector<vector<bool>> *SierTriangle::createGrid(int dim)
{
    if (dim == 1)
    {
        auto grid = new vector<vector<bool>>{{true, true},
                                             {true, false}};
        return grid;
    }
    else
    {
        return copyMachine(*createGrid(dim - 1));
    }
}

SierTriangle::SierTriangle(int dimension) : Fractal(dimension,
                                                    pow(SIERPINSKI_TRIANGLE_MULTIPLIER, dimension),
                                                    createGrid
                                                            (dimension))
{
}

/*
 *   ******** SierCarpet ********
 */
vector<vector<bool>> *SierCarpet::copyMachine(vector<vector<bool>> &small)
{
    int smallEdge = small.size();
    int newEdge = smallEdge * SIERPINSKI_CARPET_MULTIPLIER;


    auto result = new vector<vector<bool>>(newEdge, vector<bool>(newEdge,
                                                                 false));

    for (int cubeRows = 0; cubeRows < SIERPINSKI_CARPET_MULTIPLIER; cubeRows++)
    {

        for (int cubeCols = 0; cubeCols < SIERPINSKI_CARPET_MULTIPLIER; cubeCols++)
        {


            if (cubeRows != 1 || cubeCols != 1)
            {
                for (int i = 0; i < smallEdge; i++)
                {
                    for (int j = 0; j < smallEdge; j++)
                    {
                        (*result)[i + (cubeRows * smallEdge)][j +
                                                              (cubeCols * smallEdge)] = small[i][j];
                    }
                }
            }


        }

    }


    delete &small;
    return result;

}


vector<vector<bool>> *SierCarpet::createGrid(int dim)
{
    if (dim == 1)
    {
        auto grid = new vector<vector<bool>>{{true, true,  true},
                                             {true, false, true},
                                             {true, true,  true}};
        return grid;
    }
    else
    {
        return copyMachine(*createGrid(dim - 1));
    }
}

SierCarpet::SierCarpet(int dimension) : Fractal(dimension,
                                                pow(SIERPINSKI_CARPET_MULTIPLIER, dimension),
                                                createGrid
                                                        (dimension))
{
}


/*
 *   ******** Vicsek ********
 */
vector<vector<bool>> *Vicsek::copyMachine(vector<vector<bool>> &small)
{
    int smallEdge = small.size();
    int newEdge = smallEdge * VICSEK_MULTIPLIER;

    auto *bool_ptr = new vector<vector<bool>>(newEdge, vector<bool>(newEdge,
                                                                    false));

    vector<vector<bool>> *result = bool_ptr;

    for (int cubeRows = 0; cubeRows < VICSEK_MULTIPLIER; cubeRows++)
    {

        for (int cubeCols = 0; cubeCols < VICSEK_MULTIPLIER; cubeCols++)
        {


            if ((cubeRows + cubeCols) % 2 == 0)
            {
                for (int i = 0; i < smallEdge; i++)
                {
                    for (int j = 0; j < smallEdge; j++)
                    {
                        (*result)[i + (cubeRows * smallEdge)][j +
                                                              (cubeCols * smallEdge)] = small[i][j];
                    }
                }
            }


        }

    }


    delete &small;
    return result;

}


vector<vector<bool>> *Vicsek::createGrid(int dim)
{
    if (dim == 1)
    {
        auto grid = new vector<vector<bool>>{{true,  false, true},
                                             {false, true,  false},
                                             {true,  false, true}};
        return grid;
    }
    else
    {
        return copyMachine(*createGrid(dim - 1));
    }
}

Vicsek::Vicsek(int dimension) : Fractal(dimension, pow(VICSEK_MULTIPLIER, dimension), createGrid
        (dimension))
{
}


/*
 *   ******** FractalFactory ********
 */


FractalFactory::FractalFactory(vector<vector<int>> dataList) : _dataList(dataList)
{

}

vector<Fractal *> &FractalFactory::generateFractalList()
{
    vector<Fractal *> &result = *new vector<Fractal *>;
    for (int i = 0; i < (int) _dataList.size(); i++)
    {
        int frac = _dataList[i][0];
        int dim = _dataList[i][1];

        if (frac == SIERPINSKI_CARPET_SERIAL_NUM)
        {
            result.push_back(new SierCarpet(dim));
        }
        else if (frac == SIERPINSKI_TRIANGLE_SERIAL_NUM)
        {
            result.push_back(new SierTriangle(dim));
        }
        else if (frac == VICSEK_SERIAL_NUM)
        {
            result.push_back(new Vicsek(dim));
        }
    }


    return result;
}

