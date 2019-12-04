#include "FileGhost.hpp"
#include "CommandGhost.hpp"
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>

int main(int argc, char ** argv)
{
    // decide command line mode or file mode
    // command line mode
    if(argc == 1)
    {
       CommandGhost cght;
       cght.execute();
    }

    // file mode
    else if(argc == 2)
    {
        // check file format
        // (1) length of the filename should exceed 6(.ghost)
        // (2) filename should end with "/ghost"
        std::stringstream ss(argv[1]);
        std::string filename = ss.str();
        if(filename.length() <= 6 || filename.substr(filename.length() - 6) != ".ghost")
        {
            std::cerr << "File error" << std::endl;
            return EXIT_FAILURE;
        }

        FileGhost fght;
        fght.execute(filename);
    }

    else
    {
        std::cerr << "Argument Error" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; 
}