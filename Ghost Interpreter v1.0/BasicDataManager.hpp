#ifndef BASIC_DATA_MANAGER_HPP__
#define BASIC_DATA_MANAGER_HPP__

#include "ErrorHandler.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include <cctype>
#include <string>

struct BasicDataManager : virtual public ErrorHandler
{
public:
    // enum class to define variable type
    enum class varType { INT_VAR, FLOAT_VAR, STRING_VAR, LIST_VAR, NULL_VAR };

    // check value type of string command input
    varType getVarType(const std::string & cmd)
    {
        // LIST_VAR: start with '[' and ends with ']'
        if(cmd[0] == '[' && cmd.back() == ']')
        {
            return varType::LIST_VAR;
        }

        // STRING_VAR: start with '"', and ends with '"'
        else if(cmd[0] == '"' && cmd.back() == '"')
        {
            return varType::STRING_VAR;
        }

        size_t cnt = 0; // count the amount of dot(.)
        for(char c : cmd)
        {
            if(c == '.')
            {
                ++cnt;
                if(cnt > 1)
                {
                    return varType::NULL_VAR;
                }
            }
            else if(!isdigit(c))
            {
                return varType::NULL_VAR;
            }
        }
        return cnt == 0 ? varType::INT_VAR : varType::FLOAT_VAR;
    }
};

#endif