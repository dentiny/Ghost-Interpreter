#ifndef BASIC_DATA_MANAGER_HPP__
#define BASIC_DATA_MANAGER_HPP__

#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include <cctype>
#include <string>
#include <unordered_set>
#include <unordered_map>

struct BasicDataManager
{
public:
    // unordered_set to store keywords, which cannot be used as variable name
    const std::unordered_set<std::string> keywords
    {
        "var", // declaration of variable
        "def" // declaration of function
    };

    // enum class to define variable type
    enum class varType { INT_VAR, FLOAT_VAR, STRING_VAR, LIST_VAR, NULL_VAR };

    // symbol table to store local variable
    std::unordered_map<std::string, varType> localVarTbl;
    std::unordered_map<std::string, Ghost_intObj> localIntTbl;
    std::unordered_map<std::string, Ghost_floatObj> localFloatTbl;
    std::unordered_map<std::string, Ghost_stringObj> localStringTbl;

    // symbol table to store variable and its corresponding object
    std::unordered_map<std::string, varType> varTbl;
    std::unordered_map<std::string, Ghost_intObj> intTbl;
    std::unordered_map<std::string, Ghost_floatObj> floatTbl;
    std::unordered_map<std::string, Ghost_stringObj> stringTbl;

    // decide whether the value is a constant or variable
    bool isConst(std::string val)
    {
        return localVarTbl.find(val) == localVarTbl.end() && varTbl.find(val) == varTbl.end();
    }

    // decide whether the variable is local variable
    bool isLocalVar(std::string val)
    {
        return localVarTbl.find(val) != localVarTbl.end();
    }

    // decide whether the variable is global variable
    bool isGlobalVar(std::string val)
    {
        return (!isLocalVar(val)) && varTbl.find(val) != varTbl.end();
    }

    // decide whether the value is a constant or variable
    bool isVariable(std::string val)
    {
        return isLocalVar(val) || isGlobalVar(val);
    }

    // helper function of parse()
    // check if the cmd input is a single integer, a single float number or a string variable
    // varMode = true => cmd may be the name of variable
    // varMode = false => cmd can only be the value of constant
    varType getVarType(std::string & cmd, bool varMode=false)
    {
        // may be a defined variable
        if(varMode)
        {
            if(localVarTbl.find(cmd) != localVarTbl.end())
            {
                return localVarTbl[cmd];
            }
            else if(varTbl.find(cmd) != varTbl.end())
            {
                return varTbl[cmd];
            }
        }

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

    // get Ghost_intObj by its name
    Ghost_intObj getIntVar(std::string var_name)
    {
        if(isLocalVar(var_name))
        {
            if(localVarTbl[var_name] == varType::INT_VAR)
            {
                return localIntTbl[var_name];
            }

            std::cout << "The variable is in symbol table but not integer type" << std::endl;
            return Ghost_intObj(0);
        }
        else if(isGlobalVar(var_name))
        {
            if(varTbl[var_name] == varType::INT_VAR)
            {
                return intTbl[var_name];
            }

            std::cout << "The variable is in symbol table but not integer type" << std::endl;
            return Ghost_intObj(0);
        }

        std::cout << "Get Integer Ghost Object Error" << std::endl;
        return Ghost_intObj(0);
    }

    // get Ghost_floatObj by its name
    Ghost_floatObj getFloatVar(std::string var_name)
    {
        if(isLocalVar(var_name))
        {
            if(localVarTbl[var_name] == varType::FLOAT_VAR)
            {
                return localFloatTbl[var_name];
            }

            std::cout << "The variable is in symbol table but not float type" << std::endl;
            return Ghost_floatObj(0);
        }
        else if(isGlobalVar(var_name))
        {
            if(varTbl[var_name] == varType::FLOAT_VAR)
            {
                return floatTbl[var_name];
            }

            std::cout << "The variable is in symbol table but not float type" << std::endl;
            return Ghost_floatObj(0);
        }

        std::cout << "Get Float Ghost Object Error" << std::endl;
        return Ghost_floatObj(0);
    }

    // get Ghost_stringObj by its name
    Ghost_stringObj getStringVar(std::string var_name)
    {
        if(isLocalVar(var_name))
        {
            if(localVarTbl[var_name] == varType::STRING_VAR)
            {
                return localStringTbl[var_name];
            }

            std::cout << "The variable is in symbol table but not string type" << std::endl;
            return Ghost_stringObj("");
        }
        else if(isGlobalVar(var_name))
        {
            if(varTbl[var_name] == varType::STRING_VAR)
            {
                return stringTbl[var_name];
            }

            std::cout << "The variable is in symbol table but not string type" << std::endl;
            return Ghost_stringObj("");
        }

        std::cout << "Get String Ghost Object Error" << std::endl;
        return Ghost_stringObj("");
    }
};

#endif