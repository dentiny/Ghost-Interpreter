// this file is for file mode for Ghost

#ifndef FILE_GHOST_HPP__
#define FILE_GHOST_HPP__

#include "FileUncommenter.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class FileGhost : public FileUncommenter, public Tokenizer, public Parser
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

        // uncomment the code
        std::string line;
        std::vector<std::string> rawCode;
        while(std::getline(f, line))
        {
            rawCode.push_back(line);
        }
        std::vector<std::string> uncommentedCode = uncomment(rawCode);

        // create a scope when entering main scope
        createScopeManager();
        for(std::string cmd : uncommentedCode)
        {
            std::vector<std::string> cmd_vec = tokenize(cmd);
            bool ifValid = parse(cmd_vec);
            if(!ifValid)
            {
                std::cout << errMsg[err_no] << std::endl;
            }
        }

        // delete default ScopeManager when exiting main scope
        deleteScopeManager();

        // close the filestream
        f.close();
    }
};

#endif