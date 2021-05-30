
#include "Fractal.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <regex>


int main(int argc, char *argv[])
{
    // First Validate num of arguments
    if (argc - 1 != 1){
        cerr << "Usage: FractalDrawer <file path>" << endl;
        exit(EXIT_FAILURE);
    }


    string myPath = argv[1];
    Parser myParser(myPath);
    FractalFactory myFactory(myParser.fileParse());
    vector<Fractal*>& myFractalList = myFactory.generateFractalList();
    int size = (int) myFractalList.size();

    // iterate backwards
    for (int i = size - 1; i >= 0; --i)
    {
        myFractalList[i]->printFractal();
        delete myFractalList[i];
    }


}