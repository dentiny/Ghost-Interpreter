// this file is for file mode for Ghost

#ifndef FILE_GHOST_HPP__
#define FILE_GHOST_HPP__

#include "Uncommenter.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

class FileGhost : public Uncommenter, public Tokenizer, public Parser
{
public:
    void execute(const std::string & filename)
    {
        // open file
        std::ifstream f(filename);
        if(!f)
        {
            std::cerr << "Open File Stream Failure." << std::endl;
            return;
        }

        // create a scope when entering main scope
        createScopeManager();
        std::string cmd;
        while(std::getline(f, cmd))
        {
            uncomment(cmd);
            std::vector<std::string> cmd_vec = tokenize(cmd);
            bool ifValid = parse(cmd_vec);
            if(!ifValid)
            {
                std::cout << errMsg[err_no] << std::endl;
            }
        }

        // delete default ScopeManager when exiting main scope
        deleteScopeManager();
    }
};

#endif 