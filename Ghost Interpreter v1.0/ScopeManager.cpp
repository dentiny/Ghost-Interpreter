#include "ExprTree.hpp"
#include "ScopeManager.hpp"
#include <string>

// copy assignment
ScopeManager & ScopeManager::operator=(const ScopeManager & rhs)
{
    if(this != &rhs)
    {
        funcTbl = rhs.funcTbl;
        varTbl = rhs.varTbl;
        intTbl = rhs.intTbl;
        floatTbl = rhs.floatTbl;
        stringTbl = rhs.stringTbl;
        listTbl = rhs.listTbl;
    }
    return *this;
}

// decide whether this scope has no variable declared
bool ScopeManager::empty()
{
    return varTbl.empty();
} 

// decide whether has variable
bool ScopeManager::hasIntVar(const std::string & var_name)
{
    return intTbl.find(var_name) != intTbl.end();
}

// get Ghost_intObj
Ghost_intObj ScopeManager::getIntVar(const std::string & var_name)
{
    if(hasIntVar(var_name))
    {
        return intTbl[var_name];
    }
    std::cout << "Get Ingeter Object Error From ScopeManager" << std::endl;
    return Ghost_intObj(0);
}

// decide whether has variable
bool ScopeManager::hasFloatVar(const std::string & var_name)
{
    return floatTbl.find(var_name) != floatTbl.end();
}

// get Ghost_floatObj
Ghost_floatObj ScopeManager::getFloatVar(const std::string & var_name)
{
    if(hasFloatVar(var_name))
    {
        return floatTbl[var_name];
    }
    std::cout << "Get Float Object Error From ScopeManager" << std::endl;
    return Ghost_floatObj(0);
}

// decide whether has variable
bool ScopeManager::hasStringVar(const std::string & var_name)
{
    return stringTbl.find(var_name) != stringTbl.end();
} 

// get Ghost_stringObj
Ghost_stringObj ScopeManager::getStringVar(const std::string & var_name)
{
    if(hasStringVar(var_name))
    {
        return stringTbl[var_name];
    }
    std::cout << "Get String Object Error From ScopeManager" << std::endl;
    return Ghost_stringObj("");
} 

// decide whether has variable
bool ScopeManager::hasListVar(const std::string & var_name)
{
    return listTbl.find(var_name) != listTbl.end();
}

// get Ghost_listObj
Ghost_listObj ScopeManager::getListVar(const std::string & var_name)
{
    if(hasListVar(var_name))
    {
        return listTbl[var_name];
    }
    std::cout << "Get List Object Error From ScopeManager" << std::endl;
    return Ghost_listObj();
}

// decide whether function variable by its name
bool ScopeManager::hasFuncVariable(const std::string & var_name)
{
    return funcTbl.find(var_name) != funcTbl.end();
}

// get function object by its name
ExprTree ScopeManager::getFuncVar(const std::string & func_name)
{
    if(hasFuncVariable(func_name))
    {
        return funcTbl[func_name];
    }
    std::cout << "Get function object error in ScopeManager" << std::endl;
    return ExprTree();
}

// decide whether symbol table in scope contains variable by its name
bool ScopeManager::hasVariable(const std::string & var_name)
{
    return varTbl.find(var_name) != varTbl.end();
}

// get variable in string version by its name}
std::string ScopeManager::getVariable(const std::string & var_name)
{
    if(hasVariable(var_name))
    {
        varType typeRes = varTbl[var_name];
        if(typeRes == varType::INT_VAR)
        {
            Ghost_intObj obj = intTbl[var_name];
            return obj.getVal_s();
        }
        else if(typeRes == varType::FLOAT_VAR)
        {
            Ghost_floatObj obj = floatTbl[var_name];
            return obj.getVal_s();
        }
        else if(typeRes == varType::STRING_VAR)
        {
            Ghost_stringObj obj = stringTbl[var_name];
            return obj.getVal_s();
        }
        else if(typeRes == varType::LIST_VAR)
        {
            Ghost_listObj obj = listTbl[var_name];
            return obj.getVal_s();
        }
    }
    std::cout << "Get Variable Error From ScopeManager" << std::endl;
    return "";
}

// decide whether there's integer by its name
bool ScopeManager::hasIntVariable(const std::string & var_name)
{
    return intTbl.find(var_name) != intTbl.end();
}

// apply prefix operation on variable by its name
bool ScopeManager::prefixOperation(const std::string & op, const std::string & var_name)
{
    if(hasIntVariable(var_name))
    {
        if(op == "++")
        {
            ++intTbl[var_name];
        }
        else if(op == "--")
        {
            --intTbl[var_name];
        }
        return true;
    }
    std::cout << "Prefix operation error in ScopeManager" << std::endl;
    return false;
}

// apply postfix operation on variable by its name
bool ScopeManager::postfixOperation(const std::string & var_name, const std::string & op)
{
    if(hasIntVariable(var_name))
    {
        if(op == "++")
        {
            intTbl[var_name]++;
        }
        else if(op == "--")
        {
            intTbl[var_name]--;
        }
        return true;
    }
    std::cout << "Post operation error in ScopeManager" << std::endl;
    return false;
}

// display all variables in this scope
void ScopeManager::showVariable()
{
    // display Ghost_intObj
    for(auto it = intTbl.begin(); it != intTbl.end(); ++it)
    {
        std::string var_name = it->first;
        Ghost_intObj var_val = it->second;
        std::cout << var_name << "   " << "Ghost Integer" << "   " << var_val << std::endl;
    }

    // display Ghost_floatObj
    for(auto it = floatTbl.begin(); it != floatTbl.end(); ++it)
    {
        std::string var_name = it->first;
        Ghost_floatObj var_val = it->second;
        std::cout << var_name << "   " << "Ghost Float" << "   " << var_val << std::endl;
    }

    // display Ghost_stringObj
    for(auto it = stringTbl.begin(); it != stringTbl.end(); ++it)
    {
        std::string var_name = it->first;
        Ghost_stringObj var_val = it->second;
        std::cout << var_name << "   " << "Ghost String" << "   " << var_val << std::endl;
    }

    // display Ghost_listObj
    for(auto it = listTbl.begin(); it != listTbl.end(); ++it)
    {
        std::string var_name = it->first;
        Ghost_listObj var_val = it->second;
        std::cout << var_name << "   " << "Ghost List" << "   " << var_val << std::endl;
    }
}

// assign value and type to variable
void ScopeManager::assignVar(const std::string & var_name, const std::string & var_val)
{
    if(hasVariable(var_name))
    {
        // update current variable type
        varType curType = varTbl[var_name];
        varType var_type = getVarType(var_val);
        if(curType != var_type)
        {
            varTbl[var_name] = var_type;
            if(curType == varType::INT_VAR)
            {
                intTbl.erase(var_name);
            }
            else if(curType == varType::FLOAT_VAR)
            {
                floatTbl.erase(var_name);
            }
            else if(curType == varType::STRING_VAR)
            {
                stringTbl.erase(var_name);
            }
            else if(curType == varType::LIST_VAR)
            {
                listTbl.erase(var_name);
            }
            else
            {
                std::cout << "Delete variable type error in ScopeManager" << std::endl;
                return;
            }
        }

        // update present value
        if(var_type == varType::INT_VAR)
        {
            intTbl[var_name] = Ghost_intObj(var_val);
        }
        else if(var_type == varType::FLOAT_VAR)
        {
            floatTbl[var_name] = Ghost_floatObj(var_val);
        }
        else if(var_type == varType::STRING_VAR)
        {
            stringTbl[var_name] = Ghost_stringObj(var_val);
        }
        else if(var_type == varType::LIST_VAR)
        {
            listTbl[var_name] = Ghost_listObj(var_val);
        }
        else
        {
            std::cout << "Update variable value error in ScopeManager" << std::endl;
        }
        return;
    }
    std::cout << "Assignment error in ScopeManager" << std::endl;
}

// declare function
void ScopeManager::declareFunc(const std::string & func_name, 
        std::vector<std::string> & argList, 
        std::vector<std::string> & expression,
        std::vector<std::vector<std::string>> & nestedFuncList)
{
    if(hasFuncVariable(func_name))
    {
        std::cout << "Declare function error from ScopeManager" << std::endl;
    }
    funcTbl[func_name] = ExprTree(argList, expression, nestedFuncList);
}

// declare type and value to variable
void ScopeManager::declareVar(const std::string & var_name, std::string var_val, varType var_type)
{
    varTbl[var_name] = var_type;
    if(var_type == varType::INT_VAR)
    {
        intTbl[var_name] = Ghost_intObj(var_val);
    }
    else if(var_type == varType::FLOAT_VAR)
    {
        floatTbl[var_name] = Ghost_floatObj(var_val);
    }
    else if(var_type == varType::STRING_VAR)
    {
        stringTbl[var_name] = Ghost_stringObj(var_val);
    } 
    else if(var_type == varType::LIST_VAR)
    {
        listTbl[var_name] = Ghost_listObj(var_val);
    }
    else
    {
        std::cout << "Declare variable error in ScopeManager" << std::endl;
    }
}

// get variable type
BasicDataManager::varType ScopeManager::getVariableType(const std::string & var_name)
{
    if(hasVariable(var_name))
    {
        return varTbl[var_name];
    }
    std::cout << "Get variable type error in varMode from ScopeManager" << std::endl;
    return varType::NULL_VAR;
}

// helper function for built-in function type()
// get variable type by its name in string version
std::string ScopeManager::getType(const std::string & var_name)
{
    if(hasVariable(var_name))
    {
        varType typeRes = varTbl[var_name];
        if(typeRes == varType::INT_VAR)
        {
            return "Ghost Integer";
        }
        else if(typeRes == varType::FLOAT_VAR)
        {
            return "Ghost Float";
        }
        else if(typeRes == varType::STRING_VAR)
        {
            return "Ghost String";
        }
        else if(typeRes == varType::LIST_VAR)
        {
            return "Ghost List";
        }
    }
    std::cout << "Get type error in ScopeManager" << std::endl;
    return "Invalid";
}

// helper function for built-in function val()
// get variable value by its name in string version
std::string ScopeManager::getVal(const std::string & var_name)
{
    if(hasVariable(var_name))
    {
        varType typeRes = varTbl[var_name];
        if(typeRes == varType::INT_VAR)
        {
            Ghost_intObj obj = intTbl[var_name];
            return obj.getVal_s();
        }
        else if(typeRes == varType::FLOAT_VAR)
        {
            Ghost_floatObj obj = floatTbl[var_name];
            return obj.getVal_s();
        }
        else if(typeRes == varType::STRING_VAR)
        {
            Ghost_stringObj obj = stringTbl[var_name];
            return obj.getVal_s();
        }
        else if(typeRes == varType::LIST_VAR)
        {
            Ghost_listObj obj = listTbl[var_name];
            return obj.getVal_s();
        }
    }
    std::cout << "Get value error in ScopeManager" << std::endl;
    return "Invalid";
}

// helper function for built-in function query()
// get variable's type and value in string version
std::string ScopeManager::queryVar(const std::string & var_name)
{
    std::string type = getType(var_name);
    std::string val = getVal(var_name);
    if(type == "Invalid" || val == "Invalid")
    {
        return "Invalid";
    }
    std::string res = var_name + "   " + type + "   " + val;
    return res;
}
