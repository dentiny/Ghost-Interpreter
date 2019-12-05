#ifndef PARSER_HPP__
#define PARSER_HPP__

#include "BasicDataManager.hpp"
#include "DataManager.hpp"
#include "Comparator.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

class Parser : virtual public DataManager, public Comparator
{
private:
    unsigned scopeDepth = 0;
    bool enterIfStatement = false; 
    unsigned wait_for_front_curly_brace = 0; // for if statment, if enter if statement, a curly brace must trail after or appear first next line
    unsigned wait_for_rear_curly_brace = 0; // if "if" statement is false, don't do anything until rear curly brace appears
    bool checkArgInExpression(const std::vector<std::string> & argList, const std::vector<std::string> & expression); // check whether arguments in expression
    bool singleScopeHandle(const std::string & token); // handle enter and leave scope
    bool singleVarHandle(const std::string & token, bool trailMode); // handle single variable
    bool singleConstHandle(const std::string & token, bool trailMode); // handle single constant
    bool singleFuncHandle(const std::string & token, bool trailMode); // handle single function
    bool singleTokenHandle(const std::vector<std::string> & cmd_vec); // handle single token
    bool doubleSelfOperation(const std::vector<std::string> & cmd_vec); // handle double token for self-operation
    bool doubleConcatOperation(const std::vector<std::string> & cmd_vec); // handle double token for string concatenation
    bool doubleTokenHandle(const std::vector<std::string> & cmd_vec); // handle double token
    bool tripleTokenBuiltin(const std::vector<std::string> & cmd_vec); // handle triple token for built-in function
    bool tripleTokenUpdateVar(const std::vector<std::string> & cmd_vec); // handle triple token for update variable value
    bool tripleTokenCompareVar(const std::vector<std::string> & cmd_vec); // handle triple token for comparison
    bool tripleTokenHandle(const std::vector<std::string> & cmd_vec); // handle triple token
    bool quadrupleVarDeclare(const std::vector<std::string> & cmd_vec); // handle quadruple token for variable declaration
    bool quadrupleTokenBuiltin(const std::vector<std::string> & cmd_vec); // handle quadruple token for built-in function with parameter
    bool quadrupleTokenHandle(const std::vector<std::string> & cmd_vec); // handle quadruple token
    bool functionDefHandle(const std::vector<std::string> & cmd_vec); // handle expression
    bool printVarHandle(const std::vector<std::string> & cmd_vec); // handle variadic print, supports multiple variables and constants
    bool functionExecuteHandle(const std::vector<std::string> & cmd_vec); // handle function execution
    bool getBooleanValue(const std::vector<std::string> & ifStatement); // get boolean value of "if" decision statement
    bool ifStatementHandle(const std::vector<std::string> & cmd_vec); // handle if statement
    bool multipleTokenHandle(const std::vector<std::string> & cmd_vec); // handle multiple tokens

public:
    bool parse(std::vector<std::string> & cmd_vec)
    {
        // if-statement related decision
        if(wait_for_front_curly_brace > 0)
        {
            if(cmd_vec.size() == 1 && cmd_vec[0] == "{")
            {
                createScopeManager(); 
                --wait_for_front_curly_brace;
                return true;
            }
            else
            {
                // reset if statement related flag
                wait_for_front_curly_brace = 0;
                wait_for_rear_curly_brace = 0;
                err_no = IF_ERR;
                return false;
            }
        }

        // wait for rear curly brace is only set when if decision statement is false
        if(wait_for_rear_curly_brace > 0)
        {
            // ignore all statements between if statement and rear curly brace
            if(cmd_vec.size() != 1 || cmd_vec[0] != "}")         
            {
                return true;
            }
            else
            {
                --wait_for_rear_curly_brace;
                deleteScopeManager();
                return true;
            }
        }

        // no valid argument, continue
        if(cmd_vec.size() == 0)
        {
            return true;
        }

        // (1) variable value check: x => 20
        // (2) constant value check: "Hao Jiang" => "Hao Jiang"
        // (3) function value check: f => <built-in function>
        else if(cmd_vec.size() == 1)
        {
            bool singleTokenHandleSuc = singleTokenHandle(cmd_vec);
            if(singleTokenHandleSuc)
            {
                return true;
            }
        }

        // (1) self-increment and self-decrement: x++
        // (2) string concatenation: "aaa""bbb" => "aaabbb"
        else if(cmd_vec.size() == 2)
        {
            bool doubleTokenHandleSuc = doubleTokenHandle(cmd_vec);
            if(doubleTokenHandleSuc)
            {
                return true;
            }
        }

        // (1) handle triple token for built-in function => show_local(), show_global(), show_var()
        // (2) handle triple token for update variable value => v = xxx
        // (3) handle triple token for comparison => x == y
        else if(cmd_vec.size() == 3)
        {
            bool tripleTokenHandleSuc = tripleTokenHandle(cmd_vec);
            if(tripleTokenHandleSuc)
            {
                return true;
            }
        }

        // (1) handle quadruple token for built-in function with parameter => type(v), val(v), query(v)
        // (2) variable declaration => var x = xxx
        else if(cmd_vec.size() == 4)
        {
            bool quadrupleTokenHandleSuc = quadrupleTokenHandle(cmd_vec);
            if(quadrupleTokenHandleSuc)
            {
                return true;
            }
        }

        // expression handle
        bool multipleTokenHandleSuc = multipleTokenHandle(cmd_vec);
        return multipleTokenHandleSuc;
    }
};

#endif