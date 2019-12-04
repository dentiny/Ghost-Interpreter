#include "ExprTree.hpp"
#include "DataManager.hpp"
#include <string>
#include <iostream>

// decide whether the var could be a constant value
bool DataManager::isConst(const std::string & var)
{
    return getVarType(var) != varType::NULL_VAR;
}

// append ScopeManager into ScopeManager array whenever enter into new scope
void DataManager::createScopeManager()
{
    ScopeManager scpm;
    scopeArr.push_back(scpm);
} 
    
// delete ScopeManager from ScopeManager array whenever leave current scope
void DataManager::deleteScopeManager()
{
    if(scopeArr.empty())
    {
        std::cout << "ScopeManager array error from DataManager" << std::endl;
        return;
    }
    scopeArr.pop_back();
}

// decide whether keyword exists
bool DataManager::hasKeyword(const std::string & var_name)
{
    return keywords.find(var_name) != keywords.end();
}

// decide whether contains built-in function
bool DataManager::hasBuiltinFuncVar(const std::string & var_name)
{
    return built_in_func.find(var_name) != built_in_func.end();
}

// get Ghost_intObj by its name
Ghost_intObj DataManager::getIntVar(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasIntVar(var_name))
        {
            return it->getIntVar(var_name);
        }
    }
    std::cout << "Get Integer Ghost Object Error" << std::endl;
    return Ghost_intObj(0);
}

// get Ghost_floatObj by its name
Ghost_floatObj DataManager::getFloatVar(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasFloatVar(var_name))
        {
            return it->getFloatVar(var_name);
        }
    }
    std::cout << "Get Float Ghost Object Error" << std::endl;
    return Ghost_floatObj(0);
}

// get Ghost_stringObj by its name
Ghost_stringObj DataManager::getStringVar(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasStringVar(var_name))
        {
            return it->getStringVar(var_name);
        }
    }
    std::cout << "Get String Ghost Object Error" << std::endl;
    return Ghost_stringObj("");
}

// get Ghost_listObj by its name
Ghost_listObj DataManager::getListVar(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasListVar(var_name))
        {
            return it->getListVar(var_name);
        }
    }
    std::cout << "Get List Ghost Object Error" << std::endl;
    return Ghost_listObj();
}

// get ExprTree object by its name
ExprTree DataManager::getFuncVar(const std::string & func_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasFuncVariable(func_name))
        {
            return it->getFuncVar(func_name);
        }
    }
    std::cout << "Get function object error" << std::endl;
    return ExprTree();
} 

// decide whether there's variable by its name
bool DataManager::hasVariable(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasVariable(var_name))
        {
            return true;
        }
    }
    return false;
}

// get variable by its name in string version
std::string DataManager::getVariable(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasVariable(var_name))
        {
            return it->getVariable(var_name);
        }
    }
    return "";
}

// decide whether there's function by its name
bool DataManager::hasFuncVariable(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasFuncVariable(var_name))
        {
            return true;
        }
    }
    return false;
}

// helper function for self-operation
// decide whether there's integer by its name
bool DataManager::hasIntVariable(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasIntVariable(var_name))
        {
            return true;
        }
    }
    return false;
}

// apply prefix operation on variable by its name
bool DataManager::prefixOperation(const std::string & op, const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasIntVariable(var_name))
        {
            bool prefixOperationSuc = it->prefixOperation(op, var_name);
            return prefixOperationSuc;
        }
    }
    return false;
}

// apply postfix operation on variable by its name}
bool DataManager::postfixOperation(const std::string & var_name, const std::string & op)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasIntVariable(var_name))
        {
            bool prefixOperationSuc = it->postfixOperation(var_name, op);
            return prefixOperationSuc;
        }
    }
    return false;
}

// show local variables
void DataManager::showLocalVar()
{
    // corner case: there is no scope manager
    if(scopeArr.empty() || scopeArr.back().empty())
    {
        std::cout << "No local variable" << std::endl;
        return;
    }

    ScopeManager scpm = scopeArr.back();
    scpm.showVariable();
}

// show all variables
void DataManager::showVariable()
{
    // corner case: there is no scope manager
    if(scopeArr.empty())
    {
        std::cout << "No variable declared" << std::endl;
        return;
    }

    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        it->showVariable();
    }
}

// assign type and value to variable
void DataManager::assignVar(const std::string & var_name, const std::string & var_val)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasVariable(var_name))
        {
            it->assignVar(var_name, var_val);
            return;
        }
    }
    std::cout << "Assign value error from DataManager" << std::endl;
}

// declare function
void DataManager::declareFunc(const std::string & func_name, std::vector<std::string> & argList, std::vector<std::string> & expression)
{
    auto it = scopeArr.rbegin();
    it->declareFunc(func_name, argList, expression);
}

// declare type and value to variable
void DataManager::declareVar(const std::string & var_name, std::string var_val, varType var_type)
{
    auto it = scopeArr.rbegin();
    it->declareVar(var_name, var_val, var_type);
}

// get variable type
BasicDataManager::varType DataManager::getVariableType(const std::string & var_name)
{
    // varMode: get variable type in the symbol table
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasVariable(var_name))
        {
            varType typeRes = it->getVariableType(var_name);
            return typeRes;
        }
    }
    return getVarType(var_name); // use varType() in BasicDataManager
}

// helper function for built-in function type()
// get variable type by its name in string version
std::string DataManager::getType(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasVariable(var_name))
        {
            return it->getType(var_name);
        }
    }
    return "Invalid";
}

// helper function for built-in function val()
// get variable value by its name in string version
std::string DataManager::getVal(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasVariable(var_name))
        {
            return it->getVal(var_name);
        }
    }
    return "Invalid";
}

// helper function for built-in function query()
// get variable's type and value in string version
std::string DataManager::queryVar(const std::string & var_name)
{
    for(auto it = scopeArr.rbegin(); it != scopeArr.rend(); ++it)
    {
        if(it->hasVariable(var_name))
        {
            return it->queryVar(var_name);
        }
    }
    return "Invalid";
}

// evaluate the return type of expression
BasicDataManager::varType DataManager::evalRetType(const std::vector<std::string> & argList, ExprTree & exp)
{
    // check return type pre-evaluated by expression tree
    varType retType = exp.getRetType();
    if(retType == varType::LIST_VAR || retType == varType::STRING_VAR)
    {
        return retType;
    }

    // check return type by variables
    for(const std::string & var_name : argList)
    {
        varType typeRes = getVariableType(var_name);
        if(typeRes == varType::LIST_VAR || typeRes == varType::STRING_VAR)
        {
            return typeRes;
        }
        retType = (retType == varType::INT_VAR) ? typeRes : retType;
    }
    return retType;
}

// evaluate integer expression
Ghost_intObj DataManager::evalInteger(const std::vector<std::string> & argList, ExprTree & exp)
{
    Ghost_intObj res = exp.evalInteger(argList);
    return res;
}

// evaluate float expression
Ghost_floatObj DataManager::evalFloat(const std::vector<std::string> & argList, ExprTree & exp)
{
    Ghost_floatObj res = exp.evalFloat(argList);
    return res;
}

// evaluate string expression
Ghost_stringObj DataManager::evalString(const std::vector<std::string> & argList, ExprTree & exp)
{
    Ghost_stringObj res = exp.evalString(argList);
    return res;
}

// evaluate list expression
Ghost_listObj DataManager::evalList(const std::vector<std::string> & argList, ExprTree & exp)
{
    Ghost_listObj res = exp.evalList(argList);
    return res;
}
