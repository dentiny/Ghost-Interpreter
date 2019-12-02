#ifndef DATA_MANAGER_HPP__
#define DATA_MANAGER_HPP__

#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include <cctype>
#include <string>
#include <unordered_set>
#include <unordered_map>

struct DataManager : virtual public BasicDataManager
{
public:
    // symbol table to store local variable
    std::unordered_map<std::string, Ghost_listObj> localListTbl;

    // symbol table to store variable and its corresponding object
    std::unordered_map<std::string, Ghost_listObj> listTbl;

    // get Ghost_listObj by its name
    Ghost_listObj getListVar(std::string var_name)
    {
        if(isLocalVar(var_name))
        {
            if(localVarTbl[var_name] == varType::LIST_VAR)
            {
                return localListTbl[var_name];
            }

            std::cout << "The variable is in symbol table but not list type" << std::endl;
            return Ghost_listObj();
        }
        else if(isGlobalVar(var_name))
        {
            if(varTbl[var_name] == varType::LIST_VAR)
            {
                return listTbl[var_name];
            }

            std::cout << "The variable is in symbol table but not list type" << std::endl;
            return Ghost_listObj();
        }

        std::cout << "Get List Ghost Object Error" << std::endl;
        return Ghost_listObj();
    }
};

#endif