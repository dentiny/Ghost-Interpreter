#ifndef SCOPE_MANAGER_HPP__
#define SCOPE_MANAGER_HPP__

#include "ExprTree.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include "BasicDataManager.hpp"
#include <string>
#include <unordered_map>

class ScopeManager : virtual public BasicDataManager
{
private:
    // self-defined function
    std::unordered_map<std::string, ExprTree> funcTbl;

    // symbol table
//    std::map<std::string, varType> varTbl;
    std::unordered_map<std::string, varType> varTbl;
    std::unordered_map<std::string, Ghost_intObj> intTbl;
    std::unordered_map<std::string, Ghost_floatObj> floatTbl;
    std::unordered_map<std::string, Ghost_stringObj> stringTbl;
    std::unordered_map<std::string, Ghost_listObj> listTbl;

public:
    ScopeManager() : 
        funcTbl{},
        varTbl{},
        intTbl{},
        floatTbl{},
        stringTbl{},
        listTbl{}
        {} // default constructor
    ScopeManager(const ScopeManager & rhs) :
        funcTbl{rhs.funcTbl},
        varTbl{rhs.varTbl},
        intTbl{rhs.intTbl},
        floatTbl{rhs.floatTbl},
        stringTbl{rhs.stringTbl},
        listTbl{rhs.listTbl}
        {} // copy constructor
    ScopeManager & operator=(const ScopeManager & rhs); // copy assignment
    bool empty(); // decide whether this scope has no variable declared
    bool hasIntVar(const std::string & var_name); // decide whether has variable
    Ghost_intObj getIntVar(const std::string & var_name); // get Ghost_intObj
    bool hasFloatVar(const std::string & var_name); // decide whether has variable
    Ghost_floatObj getFloatVar(const std::string & var_name); // get Ghost_floatObj
    bool hasStringVar(const std::string & var_name); // decide whether has variable
    Ghost_stringObj getStringVar(const std::string & var_name); // get Ghost_stringObj
    bool hasListVar(const std::string & var_name); // decide whether has variable
    Ghost_listObj getListVar(const std::string & var_name); // get Ghost_listObj
    bool hasVariable(const std::string & var_name); // decide whether symbol table in scope contains variable by its name
    std::string getVariable(const std::string & var_name); // get variable in string version by its name
    bool hasFuncVariable(const std::string & var_name); // decide whether function variable by its name
    bool hasIntVariable(const std::string & var_name); // decide whether there's integer by its name
    bool prefixOperation(const std::string & op, const std::string & var_name); // apply prefix operation on variable by its name
    bool postfixOperation(const std::string & var_name, const std::string & op); // apply postfix operation on variable by its name
    void showVariable(); // display all variables in this scope
    void declareFunc(const std::string & func_name, std::vector<std::string> & paramList, std::vector<std::string> & expression); // declare function
    void assignVar(const std::string & var_name, const std::string & var_val); // assign value and type to variable
    void declareVar(const std::string & var_name, std::string var_val, varType var_type); // declare type and value to variable
    varType getVariableType(const std::string & var_name); // get variable type
    std::string getType(const std::string & var_name); // get variable type by its name in string version
    std::string getVal(const std::string & var_name); // get variable value by its name in string version
    std::string queryVar(const std::string & var_name); // get variable's type and value in string version
};

#endif