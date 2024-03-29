// Error Handler to handle error related constants

#ifndef ERROR_HANDLER_HPP__
#define ERROR_HANDLER_HPP__

#include <array>
#include <string>

struct ErrorHandler 
{
public:
    // every time an unexpected error happens,
    // update the err_no, main execute() trace error message by error number
    enum err_t
    {
        EXIT_CONFIRM, // exit confirmation
        SIM_EXIT, // similar exit command
        INVALID_INPUT, // invalid input command
        VAR_REDEF, // variable re-definition
        INVALID_VAL, // invalid value for Ghost
        KWD_AS_VAR, // keyword as variable name
        UNDECLARED_VAR, // usage of undeclared variable
        BUILT_FUNC_AS_VAR, // usage of built-in function as variable name
        FUNC_AS_VAR, // usage of function as variable name
        INVALID_ASSIGN, // invalid assignment
        UNDECLARED_OR_NOT_INT, // variable not declared or not integer
        UNCOMPARABLE, // two data types cannot make a comparison
        INVALID_FUNC, // invalid function called
        NO_VAR_CONST_FUNC, // not a valid variable, constant or function
        SELF_OP_ERROR, // self-operation error
        INVALID_ARG_LIST, // invalid arguments for list construction
        KWD_AS_FUNC, // keyword as function name
        BUILT_FUNC_AS_FUNC, // usage of built-in function as function name
        FUNC_REDEF, // function re-definition
        ARG_FAULT, // wrong argument for the function called
        ARG_NOT_EXPR, // argument doesn't exist in expression
        NO_ARG, // No argument provided for this expression
        IF_ERR, // if statement error, front curly brace needed
        SCOPE_ERR, // should first enter into a scope
        FUNC_NAME_AS_ARG, // argument cannot be a function
        DEAD_WHILE_LOOP, // exceed maximum while loop depth, suspect dead while loop
        UNDECLARED_OR_NOT_STR, // variable not declared or not string
        UNLENGTHABLE // variable or constant value cannot get a length
    };
    
    const std::array<std::string, 50> errMsg = 
    {
        "Exit program successfully",
        "Use exit() or quit() to exit",
        "Invalid command line input", 
        "Variable redefinition",
        "Invalid value for Ghost",
        "Cannot use keywords as variable name",
        "Cannot update a variable un-declared, declare first",
        "Cannot use built-in function name as variable name",
        "Cannot use function name as variable name",
        "Invalid assignment",
        "The variable is not declared or is not integer type",
        "Comparison cannot be applied on these two data types",
        "Invalid function called",
        "Not a valid variable, constant or function",
        "Self operation error",
        "Invalid arguments for list construction",
        "Cannot use keywords as function name",
        "Cannot use built-in function name as function name",
        "Function re-definition",
        "Wrong argument for the function called",
        "Arguments doesn't exist in expression",
        "No argument provided for this function",
        "If statement error, front curly brace needed",
        "Should first enter into a scope",
        "Argument cannot be a function",
        "Exceed maximum while loop depth, suspect dead while loop",
        "The variable is not declared or is not string type",
        "Variable or constant value cannot get a length"
    };

    // err_no have to be initialized at first
    // otherwise expression handle may depend on uninitialized variable
    unsigned err_no = INVALID_INPUT;
};

#endif