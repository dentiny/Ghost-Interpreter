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
#include <limits>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

class Parser : virtual public DataManager, public Comparator
{
private:
    unsigned scopeDepth = 0;
    unsigned long interationDepth = 0; // while-loop iteration depth
    bool intoWhileLoop = false;
    unsigned frontCurlyBraceCnt = 0;
    std::vector<std::string> whileCond;
    std::vector<std::vector<std::string>> whileCmdVec;
    bool wait_for_front_curly_brace = false; // for if statment, if enter if statement, a curly brace must trail after or appear first next line
    bool wait_for_rear_curly_brace = false; // if "if" statement is false, don't do anything until rear curly brace appears
    bool checkArgEqualFunction(const std::vector<std::string> & argList, const std::string & func_name); // check whether formal argument is already a function
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
    bool whileStatementHandle(const std::vector<std::string> & cmd_vec); // handle while statement
    bool multipleTokenHandle(const std::vector<std::string> & cmd_vec); // handle multiple tokens

public:
    bool parse(std::vector<std::string> & cmd_vec)
    {
        // wait_for_front_curly_brace state flag
        // whether "if" statement is met, it both should be met 
        if(wait_for_front_curly_brace)
        {
            if(cmd_vec.size() == 1 && cmd_vec[0] == "{")
            {
                wait_for_front_curly_brace = false;
                createScopeManager();
                ++scopeDepth;
                return true;

            }
            else
            {
                // reset if statement related flag
                wait_for_front_curly_brace = false;
                wait_for_rear_curly_brace = false;
                intoWhileLoop = false;
                err_no = IF_ERR;
                return false;
            }
        }

        // wait for rear curly brace is only set when if decision statement is false
        if(wait_for_rear_curly_brace)
        {
            // ignore all statements between if statement and rear curly brace
            if(cmd_vec.size() != 1 || cmd_vec[0] != "}")         
            {
                return true;
            }
            else
            {
                wait_for_rear_curly_brace = false;
                deleteScopeManager();
                --scopeDepth;
                return true;
            }
        }

        // during while loop, push all instructions into a vector
        // after gathering all instruction(meet a "}") then execute all of them
        if(intoWhileLoop)
        {
            // state boolean to mark dead while loop
            bool deadLoop = false;

            if(cmd_vec.size() == 1 && cmd_vec[0] == "{")
            {
                ++frontCurlyBraceCnt;
                whileCmdVec.push_back(cmd_vec);
            }
            else if(cmd_vec.size() == 1 && cmd_vec[0] == "}")
            {
                if(frontCurlyBraceCnt > 0)
                {
                    --frontCurlyBraceCnt;
                    whileCmdVec.push_back(cmd_vec);
                }
                else
                {
                    // execute instructions inside while statement block
                    intoWhileLoop = false;
                    while(getBooleanValue(whileCond))
                    {
                        // check whether dead loop using a shreshold
                        // if so, end the loop and clear the state flag
                        if(interationDepth >= std::numeric_limits<unsigned long>::max() - 1)
                        {
                            // decide dead loop, and leave the while-loop
                            err_no = DEAD_WHILE_LOOP;
                            deadLoop = true;
                            break; 
                        }
                        ++interationDepth;

                        // execute the instruction in while-loop
                        for(std::vector<std::string> instruction : whileCmdVec)
                        {
                            parse(instruction);
                        }
                    }

                    // reset while-related variable
                    interationDepth = 0;
                    whileCmdVec.clear();
                    whileCond.clear();
                }
            }
            else
            {
                whileCmdVec.push_back(cmd_vec);
            }
            return !deadLoop;
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
        if(err_no != INVALID_INPUT) 
        {
            // otherwise the right category has been tried to execute
            return false;
        }

        // expression
        bool multipleTokenHandleSuc = multipleTokenHandle(cmd_vec);
        return multipleTokenHandleSuc;
    }
};

#endif