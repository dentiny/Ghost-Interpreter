#include "FileGhost.hpp"
#include "CommandGhost.hpp"
#include <string>
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
    else
    {
//        fileGhost(argc, argv);
    }

    return EXIT_SUCCESS; 
}