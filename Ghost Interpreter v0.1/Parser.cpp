#include "Parser.hpp"
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

    // search variable in local symbal table
    if(!localVarTbl.empty())
    {
        if(localIntTbl.find(var_name) != localIntTbl.end())
        {
            std::cout << localIntTbl[var_name] << std::endl;
            return true;
        }
        else if(localFloatTbl.find(var_name) != localFloatTbl.end())
        {
            std::cout << localFloatTbl[var_name] << std::endl;
            return true;
        }
        else if(localStringTbl.find(var_name) != localStringTbl.end())
        {
            std::cout << localStringTbl[var_name] << std::endl;
            return true;
        }
        else if(localListTbl.find(var_name) != localListTbl.end())
        {
            std::cout << localListTbl[var_name] << std::endl;
            return true;
        }
    }

    // variable in the symbol table
    if(intTbl.find(var_name) != intTbl.end())
    {
        std::cout << intTbl[var_name] << std::endl;
        return true;
    }
    else if(floatTbl.find(var_name) != floatTbl.end())
    {
        std::cout << floatTbl[var_name] << std::endl;
        return true;
    }
    else if(stringTbl.find(var_name) != stringTbl.end())
    {
        std::cout << stringTbl[var_name] << std::endl;
        return true;
    }
    else if(listTbl.find(var_name) != listTbl.end())
    {
        std::cout << listTbl[var_name] << std::endl;
        return true;
    }

    err_no = INVALID_INPUT;
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

    err_no = INVALID_INPUT;
    return false;
}

// helper function for singleTokenHandle()
// single function check: <function f at location>
bool Parser::singleFuncHandle(std::vector<std::string> & cmd_vec)
{
    std::string func_name = cmd_vec[0];
    if(local_func.find(func_name) != local_func.end() || 
        func.find(func_name) != func.end() || 
        built_in_func.find(func_name) != built_in_func.end())
    {
        std::cout << "<Function object>" << std::endl;
        return true;
    }

    err_no = INVALID_INPUT;
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

        // try get variable in local intTbl
        if(localIntTbl.find(var_name) != localIntTbl.end())
        {
            // prefix increment
            if(op1 == "++")
            {
                ++localIntTbl[var_name];
            }

            // prefix decrement
            else if(op1 == "--")
            {
                --localIntTbl[var_name];
            }

            return true;
        }

        // try get variable in global intTbl
        else if(intTbl.find(var_name) != intTbl.end())
        {
            // prefix increment
            if(op1 == "++")
            {
                ++intTbl[var_name];
            }
            
            // prefix decrement
            else if(op1 == "--")
            {
                --intTbl[var_name];
            }

            return true;
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

        // try get variable in local intTbl
        if(localIntTbl.find(var_name) != localIntTbl.end())
        {
            // prefix increment
            if(op2 == "++")
            {
                localIntTbl[var_name]++;
            }

            // prefix decrement
            else if(op2 == "--")
            {
                localIntTbl[var_name]--;
            }

            return true;
        }

        // try get variable in global intTbl
        else if(intTbl.find(var_name) != intTbl.end())
        {
            // prefix increment
            if(op2 == "++")
            {
                // prefix increment
                intTbl[var_name]++;
            }
            
            // prefix decrement
            else if(op2 == "--")
            {
                intTbl[var_name]--;
            }

            return true;
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
            showLocal();
        }
        else if(f == "show_global")
        {
            showGlobal();
        }
        else if(f == "show_var")
        {
            showVar();
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

    // check if variable in the local symbol table
    if(localVarTbl.find(var_name) != localVarTbl.end())
    {
        // get value type, check if type change is necessary
        varType typeRes = getVarType(var_val);
        varType curType = localVarTbl[var_name];

        // if value assigned is a new type, delete type information first
        if(typeRes != curType)
        {
            // assignment error
            if(curType == varType::NULL_VAR)
            {
                err_no = INVALID_VAL; // invalid value for Ghost
                return false;
            }
            else if(curType == varType::INT_VAR)
            {
                localIntTbl.erase(var_name);
            }
            else if(curType == varType::FLOAT_VAR)
            {
                localFloatTbl.erase(var_name);
            }
            else if(curType == varType::STRING_VAR)
            {
                localStringTbl.erase(var_name);
            }
            else if(curType == varType::LIST_VAR)
            {
                localListTbl.erase(var_name);
            }
            localVarTbl[var_name] = typeRes;
        }

        // after dealing with type issue, update value
        if(typeRes == varType::INT_VAR)
        {
            localIntTbl[var_name] = Ghost_intObj(var_val);
        }
        else if(typeRes == varType::FLOAT_VAR)
        {
            localFloatTbl[var_name] = Ghost_floatObj(var_val);
        }
        else if(typeRes == varType::STRING_VAR)
        {
            localStringTbl[var_name] = Ghost_stringObj(var_val);
        }
        else if(typeRes == varType::LIST_VAR)
        {
            localListTbl[var_name] = Ghost_listObj(var_val);
        }

        return true;
    }

    // check if variable in the local symbol table
    else if(varTbl.find(var_name) != varTbl.end())
    {
        // get value type, check if type change is necessary
        varType typeRes = getVarType(var_val);
        varType curType = varTbl[var_name];

        // if value assigned is a new type, delete type information first
        if(typeRes != curType)
        {
            // assignment error
            if(curType == varType::NULL_VAR)
            {
                ErrorHandler::err_no = INVALID_VAL; // invalid value for Ghost
                return false;
            }
            else if(curType == varType::INT_VAR)
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
            varTbl[var_name] = typeRes;
        }

        // after dealing with type issue, update value
        if(typeRes == varType::INT_VAR)
        {
            intTbl[var_name] = Ghost_intObj(var_val);
        }
        else if(typeRes == varType::FLOAT_VAR)
        {
            floatTbl[var_name] = Ghost_floatObj(var_val);
        }
        else if(typeRes == varType::STRING_VAR)
        {
            stringTbl[var_name] = Ghost_stringObj(var_val);
        }
        else if(typeRes == varType::LIST_VAR)
        {
            listTbl[var_name] = Ghost_listObj(var_val);
        }

        return true;
    }
    
    err_no = INVALID_INPUT;
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
    else if(built_in_func.find(var_name) != built_in_func.end())
    {
        err_no = BUILT_FUNC_AS_VAR; // Cannot use built-in function name as variable or name
        return false;
    }
    else if(local_func.find(var_name) != local_func.end() || func.find(var_name) != func.end())
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
    else if(varTbl.find(var_name) != varTbl.end())
    {
        err_no = VAR_REDEF; // Variable redefinition
        return false;
    }

    // update typeTbl
    varTbl[var_name] = typeRes;
    if(typeRes == varType::INT_VAR)
    {
        intTbl[var_name] = Ghost_intObj(var_val);
    }
    else if(typeRes == varType::FLOAT_VAR)
    {
        floatTbl[var_name] = Ghost_floatObj(var_val);
    }
    else if(typeRes == varType::STRING_VAR)
    {
        stringTbl[var_name] = Ghost_stringObj(var_val);
    }
    else if(typeRes == varType::LIST_VAR)
    {
        listTbl[var_name] = Ghost_listObj(var_val);
    }
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
        std::string type_name = getType(var_name, varTbl, intTbl, floatTbl, stringTbl, listTbl);
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
        std::string val = getVal(var_name, varTbl, intTbl, floatTbl, stringTbl, listTbl);
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
        std::string ret = query(var_name, varTbl, intTbl, floatTbl, stringTbl, listTbl);
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
    if(quadrupleVarDeclare(cmd_vec) || quadrupleTokenBuiltin(cmd_vec))
    {
        return true;
    }
    return false;
}