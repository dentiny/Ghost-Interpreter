#include "Parser.hpp"
#include "BasicDataManager.hpp"
#include "DataManager.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include <vector>
#include <string>
#include <iostream>

// helper function for singleTokenHandle()
// variable value check: x => 20
bool Parser::singleVarHandle(std::vector<std::string> & cmd_vec)
{
    std::string var_name = cmd_vec[0];
    if(hasVariable(var_name))
    {
        std::string val = getVariable(var_name);
        std::cout << val << std::endl;
        return true;
    }
    return false;
}

// helper function for singleTokenHandle()
// constant value check: x => 20
bool Parser::singleConstHandle(std::vector<std::string> & cmd_vec)
{
    std::string var_name = cmd_vec[0];
    varType typeRes = getVarType(var_name);
    if(typeRes == varType::NULL_VAR)
    {
        err_no = INVALID_VAL; // Invalid value for Ghost
        return false;
    }
    else if(typeRes == varType::INT_VAR)
    {
        Ghost_intObj obj(var_name);
        std::cout << obj << std::endl;
        return true;
    }
    else if(typeRes == varType::FLOAT_VAR)
    {
        Ghost_floatObj obj(var_name);
        std::cout << obj << std::endl;
        return true;
    }
    else if(typeRes == varType::STRING_VAR)
    {
        Ghost_stringObj obj(var_name);
        std::cout << obj << std::endl;
        return true;
    }
    else if(typeRes == varType::LIST_VAR)
    {
        Ghost_listObj obj(var_name);
        std::cout << obj << std::endl;
        return true;
    }
    return false;
}

// helper function for singleTokenHandle()
// single function check: <function f at location>
bool Parser::singleFuncHandle(std::vector<std::string> & cmd_vec)
{
    std::string func_name = cmd_vec[0];
    if(hasBuiltinFuncVar(func_name) || hasFuncVariable(func_name))
    {
        std::cout << "<Function object>" << std::endl;
        return true;
    }
    return false;
}

// handle single command
// (1) variable value check: x => 20 => singleVarHandle()
// (2) constant value check: "Hao Jiang" => "Hao Jiang" => singleConstHandle()
// (3) single function check: <function f at location> => singleFuncHandle()
bool Parser::singleTokenHandle(std::vector<std::string> & cmd_vec)
{
    if(singleVarHandle(cmd_vec) || singleConstHandle(cmd_vec) || singleFuncHandle(cmd_vec))
    {
        return true;
    }
    err_no = NO_VAR_CONST_FUNC;
    return false;
}

// helper function for doubleTokenHandle()
// self-operation: ++x
bool Parser::doubleSelfOperation(std::vector<std::string> & cmd_vec)
{
    std::string op1 = cmd_vec[0];
    std::string op2 = cmd_vec[1];

    // prefix operation
    if(op1 == "++" || op1 == "--")
    {
        std::string var_name = op2;
        if(hasIntVariable(var_name))
        {
            bool prefixOperationSuc = prefixOperation(op1, var_name);
            if(prefixOperationSuc)
            {
                return true;
            }
            err_no = SELF_OP_ERROR;
            return false;
        }
        // variable not declared or not an integer type
        else
        {
            err_no = UNDECLARED_OR_NOT_INT; // variable not declared or not integer type
            return false;
        }
    }

    // postfix operation
    else if(op2 == "++" || op2 == "--")
    {
        std::string var_name = op1;
        if(hasIntVariable(var_name))
        {
            bool postfixOperationSuc = postfixOperation(var_name, op2);
            if(postfixOperationSuc)
            {
                return true;
            }
            err_no = SELF_OP_ERROR;
            return false;
        }

        // variable not declared or not an integer type
        else
        {
            err_no = UNDECLARED_OR_NOT_INT; // integer not declared or not integer type
            return false;
        }
    }
    
    err_no = INVALID_INPUT;
    return false;
}

// helper function for doubleTokenHandle()
// string concatenation: "aaa""bbb" => "aaabbb"
bool Parser::doubleConcatOperation(std::vector<std::string> & cmd_vec)
{
    std::string op1 = cmd_vec[0];
    std::string op2 = cmd_vec[1];

    if(getVarType(op1) == varType::STRING_VAR && getVarType(op2) == varType::STRING_VAR)
    {
        std::string catRes = op1.substr(0, op1.size() - 1) + op2.substr(1, op2.size() - 1);
        std::cout << catRes << std::endl;
        return true;
    }

    err_no = INVALID_INPUT;
    return false;
}

// handle two token command
// (1) self-increment and self-decrement: x++ => doubleSelfOperation()
// (2) string concatenation: "aaa""bbb" => "aaabbb"
bool Parser::doubleTokenHandle(std::vector<std::string> & cmd_vec)
{
    if(doubleSelfOperation(cmd_vec) || doubleConcatOperation(cmd_vec))
    {
        return true;
    }
    return false;
}

// helper function for tripleTokenHandle()
// built-in function with no argument
bool Parser::tripleTokenBuiltin(std::vector<std::string> & cmd_vec)
{
    std::string f = cmd_vec[0];

    // argument is not a built-in function
    if(built_in_func.find(f) != built_in_func.end())
    {
        if(f == "show_local")
        {
            showLocalVar();
        }
        else if(f == "show_var")
        {
            showVariable();
        }
        return true;
    }

    err_no = INVALID_INPUT;
    return false;
}

// helper function for tripleTokenHandle()
// update variable value
bool Parser::tripleTokenUpdateVar(std::vector<std::string> & cmd_vec)
{
    // get corresponding parts of the expression
    std::string var_name = cmd_vec[0];
    std::string eq_sgn = cmd_vec[1];
    std::string var_val = cmd_vec[2];

    // check if assignment expression
    if(eq_sgn != "=")
    {
        err_no = INVALID_INPUT;
        return false;
    }

    if(hasVariable(var_name))
    {
        // valid variable and valid value to assign
        assignVar(var_name, var_val);
        return true;
    }
    
    // variable doesn't exist in the symbol table
    err_no = UNDECLARED_VAR;
    return false;
}

// helper function for tripleTokenHandle()
// compare between type objects and constant values
bool Parser::tripleTokenCompareVar(std::vector<std::string> & cmd_vec)
{
    bool cmpRes = compare(cmd_vec);
    if(cmpRes)
    {
        return true;
    }
    
    err_no = INVALID_INPUT;
    return false;
}

// handle three token command
// (1) handle triple token for built-in function => tripleTokenBuiltin()
// (2) handle triple token for update variable value => tripleTokenUpdateVar()
// (3) handle triple token for comparison => tripleTokenCompareVar()
bool Parser::tripleTokenHandle(std::vector<std::string> & cmd_vec)
{
    if(tripleTokenUpdateVar(cmd_vec) || tripleTokenBuiltin(cmd_vec) || tripleTokenCompareVar(cmd_vec))
    {
        return true;
    }
    return false;
}

// helper function for quadrupleTokenHandle()
// handle quadruple token for variable declaration
bool Parser::quadrupleVarDeclare(std::vector<std::string> & cmd_vec)
{
    // decide whether variable declaration
    if(cmd_vec[0] != "var" || cmd_vec[2] != "=")
    {
        err_no = INVALID_INPUT; // Invalid command line input
        return false;
    }

    // first check value is valid in Ghost
    // then check variable name whether already exists in symbol table
    // if so, update ErrorHandler::err_no and return false
    // if not, add variable to the table
    std::string var_name = cmd_vec[1];
    std::string var_val = cmd_vec[3];
    varType typeRes = getVarType(var_val);

    // check validility of variable name
    if(keywords.find(var_name) != keywords.end())
    {
        err_no = KWD_AS_VAR; // "Cannot use keywords as variable name"
        return false;
    }
    else if(hasBuiltinFuncVar(var_name))
    {
        err_no = BUILT_FUNC_AS_VAR; // Cannot use built-in function name as variable or name
        return false;
    }
    else if(hasFuncVariable(var_name))
    {
        err_no = FUNC_AS_VAR;
        return false;
    }

    // error case:
    // (1) invalid value
    // (2) variable already exists in the varTbl, which means re-definition occurs
    if(typeRes == varType::NULL_VAR)
    {
        err_no = INVALID_VAL; // Invalid value for Ghost
        return false;
    }
    // check if re-definition by varTbl
    else if(hasVariable(var_name))
    {
        err_no = VAR_REDEF; // Variable redefinition
        return false;
    }

    // update varTbl
    declareVar(var_name, var_val, typeRes);
    return true;
}

// helper function for quadrupleTokenHandle()
// handle quadruple token for built-in function with parameter
bool Parser::quadrupleTokenBuiltin(std::vector<std::string> & cmd_vec)
{
    std::string f = cmd_vec[0];
    std::string var_name = cmd_vec[2];

    if(f == "type")
    {
        std::string type_name = getType(var_name);
        if(type_name == "Invalid Type")
        {
            err_no = UNDECLARED_VAR;
            return false;
        }
        std::cout << type_name << std::endl;
        return true;
    }

    else if(f == "val")
    {
        std::string val = getVal(var_name);
        if(val == "Invalid Value")
        {
            err_no = UNDECLARED_VAR;
            return false;
        }
        std::cout << val << std::endl;
        return true;
    }

    else if(f == "query")
    {
        std::string ret = queryVar(var_name);
        if(ret == "Invalid")
        {
            err_no = UNDECLARED_VAR;
            return false;
        }
        std::cout << ret << std::endl;
        return true;
    }

    err_no = INVALID_FUNC;
    return false;
}

// handle four token command
// (1) handle quadruple token for built-in function with parameter => quadrupleTokenBuiltin()
// (2) handle quadruple token for variable declaration => quadrupleVarDeclare()
bool Parser::quadrupleTokenHandle(std::vector<std::string> & cmd_vec)
{
    if(quadrupleTokenBuiltin(cmd_vec) || quadrupleVarDeclare(cmd_vec))
    {
        return true;
    }
    return false;
}