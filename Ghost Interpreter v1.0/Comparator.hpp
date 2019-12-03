#ifndef COMPARATOR_HPP__
#define COMPARATOR_HPP__

#include "ErrorHandler.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

class Comparator : virtual public ErrorHandler, virtual public DataManager
{
private:
    std::unordered_set<std::string> ops = {"<", ">", "<=", ">=", "==", "!="};

    // decide whether two data types comparable
    inline bool comparable(varType type1, varType type2)
    {
        if(type1 == type2)
        {
            return true;
        }
        else if((type1 == varType::INT_VAR && type2 == varType::FLOAT_VAR) || (type1 == varType::FLOAT_VAR && type2 == varType::INT_VAR))
        {
            return true;
        }
        return false;
    }

public:
    bool compare(const std::vector<std::string> & cmd_vec)
    {
        std::string op = cmd_vec[1];
        std::string val1 = cmd_vec[0];
        std::string val2 = cmd_vec[2];

        // invalid operator
        if(ops.find(op) == ops.end())
        {
            return false;
        }

        // get the variable type of two arguments and decide whether comparable
        varType typeRes1 = varType::NULL_VAR;
        typeRes1 = getVariableType(val1);
        if(typeRes1 == varType::NULL_VAR)
        {
            typeRes1 = getVarType(val1);
        }
        varType typeRes2 = varType::NULL_VAR;
        typeRes2 = getVariableType(val2);
        if(typeRes2 == varType::NULL_VAR)
        {
            typeRes2 = getVarType(val2);
        }

        // decide if comparable
        if(!comparable(typeRes1, typeRes2))
        {
            err_no = UNCOMPARABLE;
            return false;
        }

        bool cmpRes = false;

        // (1) string comparison
        // 1 string to string
        // 2 string to Ghost_stringObj
        // 3 Ghost_stringObj to string
        // 4 Ghost_stringObj to Ghost_stringObj
        if(typeRes1 == varType::STRING_VAR && typeRes2 == varType::STRING_VAR)
        {
            // condition 4: Ghost_stringObj to Ghost_stringObj
            if(hasVariable(val1) && hasVariable(val2))
            {
                Ghost_stringObj obj1 = getStringVar(val1);
                Ghost_stringObj obj2 = getStringVar(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // condition 3: Ghost_stringObj to string
            else if(hasVariable(val1))
            {
                Ghost_stringObj obj1 = getStringVar(val1);
                Ghost_stringObj obj2 = Ghost_stringObj(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // condition 2: string to Ghost_stringObj
            else if(hasVariable(val2))
            {
                Ghost_stringObj obj1 = Ghost_stringObj(val1);
                Ghost_stringObj obj2 = getStringVar(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // condition 1: string to string
            else
            {
                Ghost_stringObj obj1 = Ghost_stringObj(val1);
                Ghost_stringObj obj2 = Ghost_stringObj(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            std::cout << (cmpRes ? "true" : "false") << std::endl;
            return true;
        }

        // (2) list object
        // 1 list to list
        // 2 list to Ghost_listObj
        // 3 Ghost_listObj to list
        // 4 Ghost_list to Ghost_listObj
        else if(typeRes1 == varType::LIST_VAR && typeRes2 == varType::LIST_VAR)
        {
            // 4 Ghost_list to Ghost_listObj
            if(hasVariable(val1) && hasVariable(val2))
            {
                Ghost_listObj obj1 = getListVar(val1);
                Ghost_listObj obj2 = getListVar(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // 3 Ghost_listObj to list
            else if(hasVariable(val1))
            {
                Ghost_listObj obj1 = getListVar(val1);
                Ghost_listObj obj2 = Ghost_listObj(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // 2 list to Ghost_listObj
            else if(hasVariable(val2))
            {
                Ghost_listObj obj1 = Ghost_listObj(val1);
                Ghost_listObj obj2 = getListVar(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // 1 list to list
            else
            {
                Ghost_listObj obj1 = Ghost_listObj(val1);
                Ghost_listObj obj2 = Ghost_listObj(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            std::cout << (cmpRes ? "true" : "false") << std::endl;
            return true;
        }

        // (3) integer object
        // 1 integer to integer
        // 2 integer to Ghost_intObj
        // 3 Ghost_intObj to integer
        // 4 Ghost_intObj to Ghost_intObj
        else if(typeRes1 == varType::INT_VAR && typeRes2 == varType::INT_VAR)
        {
            // condition 4: Ghost_intObj to Ghost_intObj
            if(hasVariable(val1) && hasVariable(val2))
            {
                Ghost_intObj obj1 = getIntVar(val1);
                Ghost_intObj obj2 = getIntVar(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // condition 3: Ghost_intObj to integer
            else if(hasVariable(val1))
            {
                Ghost_intObj obj1 = getIntVar(val1);
                Ghost_intObj obj2 = Ghost_intObj(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // condition 2: integer to Ghost_intObj
            else if(hasVariable(val2))
            {
                Ghost_intObj obj1 = Ghost_intObj(val1);
                Ghost_intObj obj2 = getIntVar(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // condition 1: integer to integer
            else
            {
                Ghost_intObj obj1 = Ghost_intObj(val1);
                Ghost_intObj obj2 = Ghost_intObj(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            std::cout << (cmpRes ? "true" : "false") << std::endl;
            return true;
        }

        // (4) float object
        // 1 float to float
        // 2 float to Ghost_floatObj
        // 3 Ghost_floatObj to float
        // 4 Ghost_floatObj to Ghost_floatObj
        else if(typeRes1 == varType::FLOAT_VAR && typeRes2 == varType::FLOAT_VAR)
        {
            // condition 4: Ghost_floatObj to Ghost_floatObj
            if(hasVariable(val1) && hasVariable(val2))
            {
                Ghost_floatObj obj1 = getFloatVar(val1);
                Ghost_floatObj obj2 = getFloatVar(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // condition 3: Ghost_floatObj to float
            else if(hasVariable(val1))
            {
                Ghost_floatObj obj1 = getFloatVar(val1);
                Ghost_floatObj obj2 = Ghost_floatObj(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // condition 2: float to Ghost_floatObj
            else if(hasVariable(val2))
            {
                Ghost_floatObj obj1 = Ghost_floatObj(val1);
                Ghost_floatObj obj2 = getFloatVar(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            // condition 1: float to float
            else
            {
                Ghost_floatObj obj1 = Ghost_floatObj(val1);
                Ghost_floatObj obj2 = Ghost_floatObj(val2);
                cmpRes = obj1.compare(op, obj2);
            }

            std::cout << (cmpRes ? "true" : "false") << std::endl;
            return true;
        }

        // (5) cross comparison
        // 1 int to float
        // 2 int to Ghost_floatObj
        // 3 Ghost_intObj to float
        // 4 Ghost_intObj to Ghost_floatObj
        // 5 float to int
        // 6 float to Ghost_intObj
        // 7 Ghost_floatObj to int
        // 8 Ghost_floatObj to Ghost_intObj
        else
        {
            // 4 Ghost_intObj to Ghost_floatObj
            // 8 Ghost_floatObj to Ghost_intObj
            if(hasVariable(val1) && hasVariable(val2))
            {
                if(typeRes1 == varType::INT_VAR && typeRes2 == varType::FLOAT_VAR)
                {
                    Ghost_intObj obj1 = getIntVar(val1);
                    Ghost_floatObj obj2 = getFloatVar(val2);
                    cmpRes = obj1.compare(op, obj2);
                }

                else if(typeRes1 == varType::FLOAT_VAR && typeRes2 == varType::INT_VAR)
                {
                    Ghost_floatObj obj1 = getFloatVar(val1);
                    Ghost_intObj obj2 = getIntVar(val2);
                    cmpRes = obj1.compare(op, obj2);
                }

                else
                {
                    std::cout << "Cross comparison condition 4 & 8 error" << std::endl;
                }
            }

            // 3 Ghost_intObj to float
            // 7 Ghost_floatObj to int
            else if(hasVariable(val1))
            {
                if(typeRes1 == varType::INT_VAR && typeRes2 == varType::FLOAT_VAR)
                {
                    Ghost_intObj obj1 = getIntVar(val1);
                    Ghost_floatObj obj2 = Ghost_floatObj(val2);
                    cmpRes = obj1.compare(op, obj2);
                }

                else if(typeRes1 == varType::FLOAT_VAR && typeRes2 == varType::INT_VAR)
                {
                    Ghost_floatObj obj1 = getFloatVar(val1);
                    Ghost_intObj obj2 = Ghost_intObj(val2);
                    cmpRes = obj1.compare(op, obj2);
                }

                else
                {
                    std::cout << "Cross comparison condition 3 & 7 error" << std::endl;
                }
            }

            // 2 int to Ghost_floatObj
            // 6 float to Ghost_intObj
            else if(hasVariable(val2))
            {
                if(typeRes1 == varType::INT_VAR && typeRes2 == varType::FLOAT_VAR)
                {
                    Ghost_intObj obj1 = Ghost_intObj(val1);
                    Ghost_floatObj obj2 = getFloatVar(val2);
                    cmpRes = obj1.compare(op, obj2);
                }

                else if(typeRes1 == varType::FLOAT_VAR && typeRes2 == varType::INT_VAR)
                {
                    Ghost_floatObj obj1 = Ghost_floatObj(val1);
                    Ghost_intObj obj2 = getIntVar(val2);
                    cmpRes = obj1.compare(op, obj2);
                }

                else
                {
                    std::cout << "Cross comparison condition 2 & 6 error" << std::endl;
                }
            }

            // 1 int to float
            // 5 float to int
            else
            {   
                if(typeRes1 == varType::INT_VAR && typeRes2 == varType::FLOAT_VAR)
                {
                    Ghost_intObj obj1 = Ghost_intObj(val1);
                    Ghost_floatObj obj2 = Ghost_floatObj(val2);
                    cmpRes = obj1.compare(op, obj2);
                }

                else if(typeRes1 == varType::FLOAT_VAR && typeRes2 == varType::INT_VAR)
                {
                    Ghost_floatObj obj1 = Ghost_floatObj(val1);
                    Ghost_intObj obj2 = Ghost_intObj(val2);
                    cmpRes = obj1.compare(op, obj2);
                }

                else
                {
                    std::cout << "Cross comparison condition 1 & 5 error" << std::endl;
                }
            }

            std::cout << (cmpRes ? "true" : "false") << std::endl;
            return true;
        }

        return false;
    }
};

#endif