// this file is the code for scipt mode for Ghost

#ifndef SHELL_GHOST_HPP__
#define SHELL_GHOST_HPP__

#include "ExitHandler.hpp"
#include "ErrorHandler.hpp"
#include "Uncommenter.hpp"
#include "Tokenizer.hpp" 
#include "DataManager.hpp"
#include "Parser.hpp"
#include <vector>
#include <string>
#include <iostream>

class CommandGhost : public ExitHandler, public Uncommenter, public Tokenizer, public Parser
{
public:
    // main function of Command Ghost
    void execute()
    {
        // create a scope when entering main scope
        createScopeManager();
        std::string cmd;
        while(true)
        {
            std::cout << "Ghost > " << std::flush;
            std::getline(std::cin, cmd);

            // first step: decide whether to exit() 
            exitStatus exit = tryExit(cmd);
            if(exit == exitStatus::Exit_stat) 
            {
                std::cout << errMsg[err_no] << std::endl;
                break;
            }
            else if(exit == exitStatus::Sim_exit_stat)
            {
                std::cout << errMsg[err_no] << std::endl;
                continue;
            }

            // second step: uncomment
            uncomment(cmd);

            // third step: tokenize the command
            std::vector<std::string> cmd_vec = tokenize(cmd);

            // third step: parse the tokens
            bool ifValid = parse(cmd_vec);
            if(!ifValid)
            {
                std::cout << ErrorHandler::errMsg[err_no] << std::endl;
                continue;
            }

            // final step: parse the command line and calculate
//            std::cout << calculate(cmd) << std::endl;
        }

        // delete default ScopeManager when exiting main scope
        deleteScopeManager();
    }
};

#endif