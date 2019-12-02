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
    bool singleVarHandle(std::vector<std::string> & cmd_vec); // handle single variable
    bool singleConstHandle(std::vector<std::string> & cmd_vec); // handle single constant
    bool singleFuncHandle(std::vector<std::string> & cmd_vec); // handle single function
    bool singleTokenHandle(std::vector<std::string> & cmd_vec); // handle single token
    bool doubleSelfOperation(std::vector<std::string> & cmd_vec); // handle double token for self-operation
    bool doubleConcatOperation(std::vector<std::string> & cmd_vec); // handle double token for string concatenation
    bool doubleTokenHandle(std::vector<std::string> & cmd_vec); // handle double token
    bool tripleTokenBuiltin(std::vector<std::string> & cmd_vec); // handle triple token for built-in function
    bool tripleTokenUpdateVar(std::vector<std::string> & cmd_vec); // handle triple token for update variable value
    bool tripleTokenCompareVar(std::vector<std::string> & cmd_vec); // handle triple token for comparison
    bool tripleTokenHandle(std::vector<std::string> & cmd_vec); // handle triple token
    bool quadrupleVarDeclare(std::vector<std::string> & cmd_vec); // handle quadruple token for variable declaration
    bool quadrupleTokenBuiltin(std::vector<std::string> & cmd_vec); // handle quadruple token for built-in function with parameter
    bool quadrupleTokenHandle(std::vector<std::string> & cmd_vec); // handle quadruple token

public:
    bool parse(std::vector<std::string> & cmd_vec)
    {
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
            return singleTokenHandleSuc;
        }

        // (1) self-increment and self-decrement: x++
        // (2) string concatenation: "aaa""bbb" => "aaabbb"
        else if(cmd_vec.size() == 2)
        {
            bool doubleVarHandleSuc = doubleTokenHandle(cmd_vec);
            return doubleVarHandleSuc;
        }

        // (1) handle triple token for built-in function => show_local(), show_global(), show_var()
        // (2) handle triple token for update variable value => v = xxx
        // (3) handle triple token for comparison => x == y
        else if(cmd_vec.size() == 3)
        {
            bool tripleTokenHandleSuc = tripleTokenHandle(cmd_vec);
            return tripleTokenHandleSuc;
        }

        // (1) handle quadruple token for built-in function with parameter => type(v), val(v), query(v)
        // (2) variable declaration => var x = xxx
        else if(cmd_vec.size() == 4)
        {
            bool quadrupleTokenHandleSuc = quadrupleTokenHandle(cmd_vec);
            return quadrupleTokenHandleSuc;
        }

        else
        {
            err_no = INVALID_INPUT;
            std::cout << "TBC" << std::endl;
            return false;
        }
    }
};

#endif