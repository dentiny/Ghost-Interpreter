#ifndef BUILT_IN_FUNC_HPP__
#define BUILT_IN_FUNC_HPP__

#include "DataManager.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include <string>
#include <functional>
#include <unordered_set>
#include <unordered_map>

struct BuiltinFunctor : virtual public DataManager
{
public:
    // unordered_set to store built-in function
    // (1) cannot be used as function name or variable name
    // (2) examined before parsing on vector number
    const std::unordered_set<std::string> built_in_func
    {
        "val", // get the value of variable
        "type", // get the type of variable
        "query", // get the type and value of variable
        "show_local", // display local variables
        "show_global", // display glocal variables
        "show_var" // display all variables
    };

    // helper function for parse()
    // helper function for category 6: built-in function type()
    // helper function for category 7: built-in function
    std::string getType(const std::string & var_name,
        std::unordered_map<std::string, varType> & varTbl, 
        std::unordered_map<std::string, Ghost_intObj> & intTbl,
        std::unordered_map<std::string, Ghost_floatObj> & floatTbl,
        std::unordered_map<std::string, Ghost_stringObj> & stringTbl,
        std::unordered_map<std::string, Ghost_listObj> & listTbl)
    {
        // variable not declared
        if(varTbl.find(var_name) == varTbl.end())
        {
            return "Invalid Type";
        }

        varType curType = varTbl[var_name];
        if(curType == varType::INT_VAR)
        {
            return intTbl[var_name].getType();
        }
        else if(curType == varType::FLOAT_VAR)
        {
            return floatTbl[var_name].getType();
        }
        else if(curType == varType::STRING_VAR)
        {
            return stringTbl[var_name].getType();
        } 
        else if(curType == varType::LIST_VAR)
        {
            return listTbl[var_name].getType();
        }
        return "Invalid Type";
    }

    // helper function for parse()
    // helper function for category 6: built-in function val()
    // helper function for category 7: built-in function
    std::string getVal(const std::string & var_name, 
            std::unordered_map<std::string, varType> & varTbl, 
            std::unordered_map<std::string, Ghost_intObj> & intTbl,
            std::unordered_map<std::string, Ghost_floatObj> & floatTbl,
            std::unordered_map<std::string, Ghost_stringObj> & stringTbl,
            std::unordered_map<std::string, Ghost_listObj> & listTbl)
    {
        // variable not declared
        if(varTbl.find(var_name) == varTbl.end())
        {
            return "Invalid Value";
        }

        varType curType = varTbl[var_name];
        if(curType == varType::INT_VAR)
        {
            return intTbl[var_name].getVal_s();
        }
        else if(curType == varType::FLOAT_VAR)
        {
            return floatTbl[var_name].getVal_s();
        }
        else if(curType == varType::STRING_VAR)
        {
            return stringTbl[var_name].getVal_s();
        }   
        else if(curType == varType::LIST_VAR)
        {
            return listTbl[var_name].getVal_s();
        }
        return "Invalid Value";
    }

    // helper function for parse()
    // helper function for category 7: built-in function
    std::string query(const std::string & var_name, 
            std::unordered_map<std::string, varType> & varTbl, 
            std::unordered_map<std::string, Ghost_intObj> & intTbl,
            std::unordered_map<std::string, Ghost_floatObj> & floatTbl,
            std::unordered_map<std::string, Ghost_stringObj> & stringTbl,
            std::unordered_map<std::string, Ghost_listObj> & listTbl)
    {
        std::string type = getType(var_name, varTbl, intTbl, floatTbl, stringTbl, listTbl);
        std::string val = getVal(var_name, varTbl, intTbl, floatTbl, stringTbl, listTbl);
        if(type == "Invalid Type" || val == "Invalid Value")
        {
            return "Invalid";
        }
        std::string ret = var_name + " " + type + " " + val;
        return ret; 
    }

    // helper function for parse()
    // helper function for category 7: built-in function show_local()
    void showLocal()
    {
        // corner case: there is no local variable
        if(localVarTbl.empty())
        {
            std::cout << "No local Variable" << std::endl;
            return;
        }

        std::cout << "Local Variables:" << std::endl;
        for(auto it = localVarTbl.begin(); it != localVarTbl.end(); ++it)
        {
            std::string var_name = it->first;
            std::string var_type = getType(var_name, localVarTbl, localIntTbl, localFloatTbl, localStringTbl, localListTbl);
            std::string var_val = getVal(var_name, localVarTbl, localIntTbl, localFloatTbl, localStringTbl, localListTbl);
            std::cout << var_name << "  " << var_type << "   " << var_val << std::endl;
        }
    }

    // helper function for parse()
    // helper function for category 7: built-in function show_global()
    void showGlobal()
    {
        // corner case: there is no local variable
        if(varTbl.empty())
        {
            std::cout << "No global Variable" << std::endl;
            return;
        }

        std::cout << "Global Variables:" << std::endl;
        for(auto it = varTbl.begin(); it != localVarTbl.end(); ++it)
        {
            std::string var_name = it->first;
            std::string var_type = getType(var_name, varTbl, intTbl, floatTbl, stringTbl, listTbl);
            std::string var_val = getVal(var_name, varTbl, intTbl, floatTbl, stringTbl, listTbl);
            std::cout << var_name << "  " << var_type << "   " << var_val << std::endl;
        }
    }

    // helper function for parse()
    // helper function for category 7: built-in function show_global()
    void showVar()
    {
        showLocal();
        showGlobal();
    }
};

#endif