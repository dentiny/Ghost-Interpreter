// Exit Handler to handle exit() instructions and those possible to require exit()

#ifndef EXIT_HANDLER_HPP__
#define EXIT_HANDLER_HPP__

#include "ErrorHandler.hpp"
#include <string>
#include <unordered_set>

class ExitHandler : virtual public ErrorHandler
{
private:
    // exit_cmd store instructions legal to exit()
    // exit_sim_cmd are those possible to require exit()
    std::unordered_set<std::string> exit_cmd { "exit()", "quit()" };
    std::unordered_set<std::string> exit_sim_cmd { "exit", "quit" };

public:
    // exit-related variables
    enum class exitStatus { Exit_stat, Sim_exit_stat, Other };
    
    // Parse command first step:
    // decide whether exit() the Ghost Shell
    // true to exit, false to stay
    exitStatus tryExit(std::string & cmd)
    {
        // command to exit
        if(exit_cmd.find(cmd) != exit_cmd.end())
        {
            err_no = EXIT_CONFIRM;
            return exitStatus::Exit_stat;
        }

        // command suspected to exit
        else if(exit_sim_cmd.find(cmd) != exit_sim_cmd.end())
        {
            err_no = SIM_EXIT;
            return exitStatus::Sim_exit_stat;
        }
        return exitStatus::Other;
    }
};

#endif