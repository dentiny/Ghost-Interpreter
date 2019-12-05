#include "Parser.hpp"
#include "BasicDataManager.hpp"
#include "DataManager.hpp"
#include "ExprTree.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

// helper function for singleTokenHandle()
// enter into and leave from scope
bool Parser::singleScopeHandle(const std::string & op)
{
    if(op == "{")
    {
        ++scopeDepth;
        createScopeManager();
        return true;
    }
    else if(op == "}")
    {
        // make sure scope is valid
        if(scopeDepth >= 1)
        {
            --scopeDepth;
            deleteScopeManager();
            return true;
        }
    }
    return false;
}

// helper function for singleTokenHandle()
// variable value check: x => 20
bool Parser::singleVarHandle(const std::string & var_name, bool trailMode)
{
    if(hasVariable(var_name))
    {
        std::string val = getVariable(var_name);
        std::cout << val << std::flush;
        if(trailMode)
        {
            std::cout << " " << std::flush;
        }
        else 
        {
            std::cout << std::endl;
        }
        return true;
    }
    return false;
}

// helper function for singleTokenHandle()
// constant value check: x => 20
bool Parser::singleConstHandle(const std::string & var_name, bool trailMode)
{
    varType typeRes = getVarType(var_name);
    if(typeRes == varType::NULL_VAR)
    {
        err_no = INVALID_VAL; // Invalid value for Ghost
        return false;
    }
    else if(typeRes == varType::INT_VAR)
    {
        Ghost_intObj obj(var_name);
        std::cout << obj << std::flush;
        if(trailMode)
        {
            std::cout << " " << std::flush;
        }
        else 
        {
            std::cout << std::endl;
        }
        return true;
    }
    else if(typeRes == varType::FLOAT_VAR)
    {
        Ghost_floatObj obj(var_name);
        std::cout << obj << std::flush;
        if(trailMode)
        {
            std::cout << " " << std::flush;
        }
        else 
        {
            std::cout << std::endl;
        }
        return true;
    }
    else if(typeRes == varType::STRING_VAR)
    {
        Ghost_stringObj obj(var_name);
        std::cout << obj << std::flush;
        if(trailMode)
        {
            std::cout << " " << std::flush;
        }
        else 
        {
            std::cout << std::endl;
        }
        return true;
    }
    else if(typeRes == varType::LIST_VAR)
    {
        Ghost_listObj obj(var_name);
        std::cout << obj << std::flush;
        if(trailMode)
        {
            std::cout << " " << std::flush;
        }
        else 
        {
            std::cout << std::endl;
        }
        return true;
    }
    return false;
}

// single variable, constant and function output method has been added a boolean argument -- trailMode
// this argument is for the compatibility with built-in function -- printVarHandle()
// for single string input, trailMode should be set false, which may generate a newliner after every var output
// for continuous printint method, trailMode will be set on, thus space will act as splitter between strings
// helper function for singleTokenHandle()
// single function check: <function f at location>
bool Parser::singleFuncHandle(const std::string & func_name, bool trailMode)
{
    if(hasBuiltinFuncVar(func_name) || hasFuncVariable(func_name))
    {
        std::cout << "<Function object>" << std::flush;
        if(trailMode)
        {
            std::cout << " " << std::flush;
        }
        else 
        {
            std::cout << std::endl;
        }
        return true;
    }
    return false;
}

// handle single command
// (1) variable value check: x => 20 => singleVarHandle()
// (2) constant value check: "Hao Jiang" => "Hao Jiang" => singleConstHandle()
// (3) single function check: <function f at location> => singleFuncHandle()
bool Parser::singleTokenHandle(const std::vector<std::string> & cmd_vec)
{
    std::string token = cmd_vec[0];
    if(singleScopeHandle(token) || singleVarHandle(token, false) || singleConstHandle(token, false) || singleFuncHandle(token, false))
    {
        return true;
    }
    err_no = NO_VAR_CONST_FUNC;
    return false;
}

// helper function for doubleTokenHandle()
// self-operation: ++x
bool Parser::doubleSelfOperation(const std::vector<std::string> & cmd_vec)
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
    return false;
}

// helper function for doubleTokenHandle()
// string concatenation: "aaa""bbb" => "aaabbb"
bool Parser::doubleConcatOperation(const std::vector<std::string> & cmd_vec)
{
    std::string op1 = cmd_vec[0];
    std::string op2 = cmd_vec[1];

    if(getVarType(op1) == varType::STRING_VAR && getVarType(op2) == varType::STRING_VAR)
    {
        std::string catRes = op1.substr(0, op1.size() - 1) + op2.substr(1, op2.size() - 1);
        std::cout << catRes << std::endl;
        return true;
    }
    return false;
}

// handle two token command
// (1) self-increment and self-decrement: x++ => doubleSelfOperation()
// (2) string concatenation: "aaa""bbb" => "aaabbb"
bool Parser::doubleTokenHandle(const std::vector<std::string> & cmd_vec)
{
    err_no = INVALID_INPUT;
    if(doubleSelfOperation(cmd_vec) || doubleConcatOperation(cmd_vec))
    {
        return true;
    }
    return false;
}

// helper function for tripleTokenHandle()
// built-in function with no argument
bool Parser::tripleTokenBuiltin(const std::vector<std::string> & cmd_vec)
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
bool Parser::tripleTokenUpdateVar(const std::vector<std::string> & cmd_vec)
{
    // get corresponding parts of the expression
    std::string var_name = cmd_vec[0];
    std::string eq_sgn = cmd_vec[1];
    std::string var_val = cmd_vec[2];

    // check if assignment expression
    if(eq_sgn != "=")
    {
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
bool Parser::tripleTokenCompareVar(const std::vector<std::string> & cmd_vec)
{
    bool cmpRes = compare(cmd_vec);
    if(cmpRes)
    {
        return true;
    }
    return false;
}

// handle three token command
// (1) handle triple token for built-in function => tripleTokenBuiltin()
// (2) handle triple token for update variable value => tripleTokenUpdateVar()
// (3) handle triple token for comparison => tripleTokenCompareVar()
bool Parser::tripleTokenHandle(const std::vector<std::string> & cmd_vec)
{
    err_no = INVALID_INPUT;
    if(tripleTokenUpdateVar(cmd_vec) || tripleTokenBuiltin(cmd_vec) || tripleTokenCompareVar(cmd_vec))
    {
        return true;
    }
    return false;
}

// helper function for quadrupleTokenHandle()
// handle quadruple token for variable declaration
bool Parser::quadrupleVarDeclare(const std::vector<std::string> & cmd_vec)
{
    // decide whether variable declaration
    if(cmd_vec[0] != "var" || cmd_vec[2] != "=")
    {
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
bool Parser::quadrupleTokenBuiltin(const std::vector<std::string> & cmd_vec)
{
    std::string f = cmd_vec[0];
    std::string var_name = cmd_vec[2];

    if(f == "print")
    {
        bool printVarHandleSuc = printVarHandle(cmd_vec);   
        return printVarHandleSuc;
    }
    else if(f == "type")
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
    return false;
}

// handle four token command
// (1) handle quadruple token for built-in function with parameter => quadrupleTokenBuiltin()
// (2) handle quadruple token for variable declaration => quadrupleVarDeclare()
bool Parser::quadrupleTokenHandle(const std::vector<std::string> & cmd_vec)
{
    err_no = INVALID_INPUT;
    if(quadrupleTokenBuiltin(cmd_vec) || quadrupleVarDeclare(cmd_vec))
    {
        return true;
    }
    return false;
}

// helper function for functionDefHandle()
// check whether arguments in expression
// return true if valid, else return false
bool Parser::checkArgInExpression(const std::vector<std::string> & argList, const std::vector<std::string> & expression)
{   
    std::unordered_set<std::string> expressionKwd(expression.begin(), expression.end());
    for(const std::string & arg : argList)
    {
        if(expressionKwd.find(arg) == expressionKwd.end())
        {
            return false;
        }
    }
    return true;
}

bool Parser::functionDefHandle(const std::vector<std::string> & cmd_vec)
{
    // function declaration statement begins with def
    if(cmd_vec[0] != "def")
    {
        return false;
    }

    // check validility of variable name
    std::string func_name = cmd_vec[1];
    if(hasKeyword(func_name))
    {
        err_no = KWD_AS_FUNC; // "Cannot use keywords as variable name"
        return false;
    }
    else if(hasBuiltinFuncVar(func_name))
    {
        err_no = BUILT_FUNC_AS_FUNC; // Cannot use built-in function name as variable or name
        return false;
    }
    else if(hasFuncVariable(func_name))
    {
        err_no = FUNC_AS_VAR;
        return false;
    }

    // tokenize parameter list and built expression tree object
    int j = findMatched(cmd_vec, "(", ")", 2); // "(" index is 2
    if(j == 3) // if no argument, j should be 3
    {
        err_no = NO_ARG;
        return false;
    }
    std::vector<std::string> argList(cmd_vec.begin() + 3, cmd_vec.begin() + j); // arguments of the function
    std::vector<std::string> expression;
    std::vector<std::vector<std::string>> nestedFuncList;
    unsigned nestFunc = 0;
    for(size_t i = j + 2; i < cmd_vec.size(); ++i)
    {
        std::string var = cmd_vec[i];
        if(hasFuncVariable(var))
        {
            // find the match parenthesis, and for get formal arguments
            int rightParenthesis = findMatched(cmd_vec, "(", ")", i + 1); // i + 1 is the index of "("
            
           // formal argument for nested function
            std::vector<std::string> nestedFuncArg(cmd_vec.begin() + i + 2, cmd_vec.begin() + rightParenthesis); // f(x, y) => x, y
            i = rightParenthesis;

            // get expression tree for nested function, and replace to current arguments
            ExprTree exprTree = getFuncVar(var);
            BasicDataManager::ExprPair exprTreePair = exprTree.getExprTree(); // first for arguments, second for expression
            std::vector<std::string> originalFuncArgList = exprTreePair.first; // f(a, b) = a + b
            std::vector<std::string> exprTreeVec = exprTreePair.second; // ( a + b )

            // build a mapping relation for replacement
            std::unordered_map<std::string, std::string> oriToCur;
            for(size_t i = 0; i < originalFuncArgList.size(); ++i)
            {
                oriToCur[originalFuncArgList[i]] = nestedFuncArg[i];
            }

            // replacement
            for(size_t i = 0; i < exprTreeVec.size(); ++i)
            {
                std::string token = exprTreeVec[i];
                if(oriToCur.find(token) != oriToCur.end())
                {
                    exprTreeVec[i] = oriToCur[token];
                }
            }

            // append replaced expression
            nestedFuncList.push_back(exprTreeVec);
            expression.push_back("_expression marker " + std::to_string(nestFunc));
            ++nestFunc;
        }
        else
        {
            expression.push_back(var);
        }
    }
/*
    // check arguments if exist in expression
    if(!checkArgInExpression(argList, expression))
    {
        err_no = ARG_NOT_EXPR;
        return false;
    }
*/
    declareFunc(func_name, argList, expression, nestedFuncList);
    return true;
}

// handle variadic print, supports multiple variables and constants
bool Parser::printVarHandle(const std::vector<std::string> & cmd_vec)
{
    // print() statement begins with "print"
    if(cmd_vec[0] != "print")
    {
        return false;
    }

    // eg: print(a, b, c, end="HaoJiang")
    // => print | ( | a | b | c | end | = | "HaoJiang" | ) 

    // management trailing string of output
    size_t N = cmd_vec.size();
    std::string endOutput = "\n";
    if(N >= 4 && cmd_vec[N - 4] == ("end") && cmd_vec[N - 3] == "=") // check whether ending starts with "end="
    {
        endOutput = cmd_vec[N - 2];
        endOutput = endOutput.substr(1, endOutput.length() - 2);
        N -= 3;
    }
    
    // iterative print variable, function or constant
    // stop outputing whenever encountering invalid string
    for(size_t i = 2; i < N - 1; ++i)
    {
        std::string token = cmd_vec[i];
        if((!singleVarHandle(token, true)) && (!singleFuncHandle(token, true)) && (!singleConstHandle(token, true)))
        {
            return false;
        }
    }
    std::cout << endOutput << std::flush;
    return true;
}

// handle function execution
bool Parser::functionExecuteHandle(const std::vector<std::string> & cmd_vec)
{
    // check whether function call
    if(!hasFuncVariable(cmd_vec[0]) || cmd_vec[1] != "(" || cmd_vec.back() != ")")
    {
        return false;
    }

    // get argument list
    std::string func_name = cmd_vec[0];
    ExprTree exp = getFuncVar(func_name);
    std::vector<std::string> argList(cmd_vec.begin() + 2, cmd_vec.begin() + (cmd_vec.size() - 1));
    bool argValid = exp.isValidArgument(argList);

    // check argument number
    if(!argValid)
    {
        err_no = ARG_FAULT;
        return false;
    }

    // check argument either variable or constant
    for(std::string var_name : argList)
    {
        if(!hasVariable(var_name) && !isConst(var_name))
        {
            err_no = ARG_FAULT;
            return false;
        }
    }

    // evaluate the function call
    varType retType = evalRetType(argList, exp);
    if(retType == varType::INT_VAR)
    {
        Ghost_intObj res = evalInteger(argList, exp);
        std::cout << res << std::endl;
        return true;
    }
    else if(retType == varType::FLOAT_VAR)
    {
        Ghost_floatObj res = evalFloat(argList, exp);
        std::cout << res << std::endl;
        return true;
    }
    else if(retType == varType::STRING_VAR)
    {
        Ghost_stringObj res = evalString(argList, exp);
        std::cout << res << std::endl;
        return true;
    }
    else if(retType == varType::LIST_VAR)
    {
        Ghost_listObj res = evalList(argList, exp);
        std::cout << res << std::endl;
        return true;
    }
    std::cout << "Return type error in Parser" << std::endl;
    return false;
}

// handle multiple tokens
bool Parser::multipleTokenHandle(const std::vector<std::string> & cmd_vec)
{
    err_no = INVALID_INPUT;
    if(functionDefHandle(cmd_vec) || printVarHandle(cmd_vec) || functionExecuteHandle(cmd_vec))
    {
        return true;
    }
    return false;
}