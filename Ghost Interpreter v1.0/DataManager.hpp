#ifndef DATA_MANAGER_HPP__
#define DATA_MANAGER_HPP__

#include "ExprTree.hpp"
#include "ScopeManager.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include <list>
#include <string>
#include <unordered_set>

class DataManager : virtual public BasicDataManager
{
private:
    std::list<ScopeManager> scopeArr;

public:
    // unordered_set to store keywords, which cannot be used as variable name
    const std::unordered_set<std::string> keywords
    {
        "var", // declaration of variable
        "def" // declaration of function
    };

    // unordered_set to store built-in function
    const std::unordered_set<std::string> built_in_func
    {
        "print", // get the value of a constant or a variable
        "val", // get the value of variable
        "type", // get the type of variable
        "query", // get the type and value of variable
        "show_local", // show local variables
        "show_var" // display all variables
    };

    bool isConst(const std::string & var); // decide whether the var could be a constant value
    void createScopeManager(); // append ScopeManager into ScopeManager array whenever enter into new scope
    void deleteScopeManager(); // delete ScopeManager from ScopeManager array whenever leave current scope
    bool hasKeyword(const std::string & var_name); // decide whether keyword exists
    bool hasBuiltinFuncVar(const std::string & var_name); // decide whether built-in function exists
    Ghost_intObj getIntVar(const std::string & var_name); // get Ghost_intObj by its name
    Ghost_floatObj getFloatVar(const std::string & var_name); // get Ghost_floatObj by its name
    Ghost_stringObj getStringVar(const std::string & var_name); // get Ghost_stringObj by its name
    Ghost_listObj getListVar(const std::string & var_name); // get Ghost_listObj by its name
    ExprTree getFuncVar(const std::string & func_name); // get ExprTree object by its name
    bool hasVariable(const std::string & var_name); // decide whether there's variable by its name
    std::string getVariable(const std::string & var_name); // get variable by its name in string version
    bool hasFuncVariable(const std::string & var_name); // decide whether there's function by its name
    bool hasIntVariable(const std::string & var_name); // decide whether there's integer by its name
    bool prefixOperation(const std::string & op, const std::string & var_name); // apply prefix operation on variable by its name
    bool postfixOperation(const std::string & var_name, const std::string & op); // apply postfix operation on variable by its name
    void showLocalVar(); // show local variables
    void showVariable(); // show all variables
    void declareFunc(const std::string & func_name, std::vector<std::string> & argList, std::vector<std::string> & expression); // declare function
    void assignVar(const std::string & var_name, const std::string & var_val); // assign type and value to variable
    void declareVar(const std::string & var_name, std::string var_val, varType var_type); // declare type and value to variable
    varType getVariableType(const std::string & var_name); // get variable type
    std::string getType(const std::string & var_name); // get variable type by its name in string version
    std::string getVal(const std::string & var_name); // get variable value by its name in string version
    std::string queryVar(const std::string & var_name); // get variable's type and value in string version
    varType evalRetType(const std::vector<std::string> & argList, ExprTree & exp); // evaluate the return type of expression
    void funcArgHandle(std::vector<std::string> & argList); // before argument evaluation, convert variable into string version 
    Ghost_intObj evalInteger(std::vector<std::string> & argList, ExprTree & exp); // evaluate integer expression
    Ghost_floatObj evalFloat(std::vector<std::string> & argList, ExprTree & exp); // evaluate float expression
    Ghost_stringObj evalString(std::vector<std::string> & argList, ExprTree & exp); // evaluate string expression
    Ghost_listObj evalList(std::vector<std::string> & argList, ExprTree & exp); // evaluate list expression
};

#endif