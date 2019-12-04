#include "ExprTree.hpp"
#include "BasicDataManager.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// character-wise parse expression
ExprTree::Node * ExprTree::buildTreeHelper(std::vector<std::string> & expression, bool inBrace)
{
    Node * r = nullptr;
    Node * cur = nullptr;
    int N = expression.size();
    for(int i = 0; i < N; ++i)
    {
        std::string token = expression[i];

        // bracket
        if(token == "(")
        {
            int j = findMatched(expression, "(", ")", i);
            std::vector<std::string> bracket(expression.begin() + i + 1, expression.begin() + j);
            Node * p = buildTreeHelper(bracket, true);
            i = j;

            if(r == nullptr)
            {
                r = p;
            }
            else if(r->right == nullptr)
            {
                r->right = p;
            }
            else if(cur->right == nullptr)
            {
                cur->right = p;
            }
            else 
            {
                std::cout << "Bracket error" << std::endl;
            }
        }

        // operand
        else if(ops.find(token) == ops.end())
        {
            Node * p = new Node(token);
            if(r == nullptr)
            {
                cur = p;
            }
            else if(r->right == nullptr)
            {
                r->right = p;
            }
            else if(cur->right == nullptr)
            {
                cur->right = p;
            }
            else
            {
                std::cout << "Operand error" << std::endl;
            }
        }

        // operator
        else if(ops.find(token) != ops.end())
        {
            Node * p = new Node(token);
            if(r == nullptr)
            {
                r = p;
                r->left = cur;
                cur = nullptr;
            }
            else if(p->getPriority() <= r->getPriority())
            {
                p->left = r;
                r = p;
                cur = nullptr;
            }
            else if(p->getPriority() > r->getPriority())
            {
                p->left = r->right;
                r->right = p;
                cur = p;
            }
            else
            {
                std::cout << "Operator error" << std::endl;
            }
        }
    }

    if(inBrace)
    {
        r->updatePriority();
    }
    return r;
}


// helper function for copy constructor and copy assignment
ExprTree::Node * ExprTree::copyHelper(ExprTree::Node * current)
{
    if(current == nullptr)
    {
        return nullptr;
    }
    Node * r = new Node(current->val);
    r->left = copyHelper(current->left);
    r->right = copyHelper(current->right);
    return r;
}

// pre-evaluate the return type of the expression after building the expression tree
void ExprTree::evalRetTypeHelper(ExprTree::Node * r)
{
    if(r != nullptr)
    {
        // retType is already Ghost_stringObj or Ghost_listObj
        if(retType == varType::STRING_VAR || retType == varType::LIST_VAR)
        {
            return;
        }

        std::string var = r->val;
        // if variable or operator
        if(ops.find(var) != ops.end() || find(argTbl.begin(), argTbl.end(), var) != argTbl.end())
        {
            evalRetTypeHelper(r->left);
            evalRetTypeHelper(r->right);
            return;
        }

        // constant node
        varType typeRes = getVarType(var);

        // if variable is Ghost_listObj or Ghost_stringObj
        // return type must be themselves
        if(typeRes == varType::LIST_VAR || typeRes == varType::STRING_VAR)
        {
            retType = typeRes;
        }
        else if(typeRes == varType::FLOAT_VAR || retType == varType::FLOAT_VAR)
        {
            retType = varType::FLOAT_VAR;
        }
        else
        {
            retType = varType::INT_VAR;
        }
    }
}

// helper function for delete()
// recursively de-allocate allocated memory
void ExprTree::deleteHelper(ExprTree::Node * r)
{
    if(r != nullptr)
    {
        deleteHelper(r->left);
        deleteHelper(r->right);
        delete r;
    }
}

// check validility of argument list
bool ExprTree::isValidArgument(const std::vector<std::string> & _argTbl) const
{
    return argTbl.size() == _argTbl.size();
}

// get pre-evaluated return type
BasicDataManager::varType ExprTree::getRetType() const
{
    return retType;
}

// helper function for evalInteger()
// evaluate Ghost_intObj
Ghost_intObj ExprTree::evalIntHelper(ExprTree::Node * r)
{
    std::string var = r->val;

    // operator
    if(r->left != nullptr && r->right != nullptr)
    {
        Ghost_intObj leftVal = evalIntHelper(r->left);
        Ghost_intObj rightVal = evalIntHelper(r->right);
        return intOps[var](leftVal, rightVal);
    }

    // operand
    if(argMap.find(var) != argMap.end())
    {
        return argMap[var];
    }
    else
    {
        return Ghost_intObj(var);
    }
}   

// helper function for evalFloat()
// evaluate Ghost_floatObj
Ghost_floatObj ExprTree::evalFloatHelper(ExprTree::Node * r)
{
    std::string var = r->val;

    // operator
    if(r->left != nullptr && r->right != nullptr)
    {
        Ghost_floatObj leftVal = evalFloatHelper(r->left);
        Ghost_floatObj rightVal = evalFloatHelper(r->right);
        return floatOps[var](leftVal, rightVal);
    }

    // operand
    if(argMap.find(var) != argMap.end())
    {
        return argMap[var];
    }
    else
    {
        return Ghost_floatObj(var);
    }
}

// helper function for evalString()
// evaluate Ghost_stringObj
Ghost_stringObj ExprTree::evalStringHelper(ExprTree::Node * r)
{
    std::string var = r->val;

    // operator
    if(r->left != nullptr && r->right != nullptr)
    {
        Ghost_stringObj leftVal = evalStringHelper(r->left);
        Ghost_stringObj rightVal = evalStringHelper(r->right);
        return stringOps[var](leftVal, rightVal);
    }

    // operand
    if(argMap.find(var) != argMap.end())
    {
        return argMap[var];
    }
    else
    {
        return Ghost_stringObj(var);
    }
}

// helper function for evalList()
// evaluate Ghost_listObj
Ghost_listObj ExprTree::evalListHelper(ExprTree::Node * r)
{
    std::string var = r->val;

    // operator
    if(r->left != nullptr && r->right != nullptr)
    {
        Ghost_listObj leftVal = evalListHelper(r->left);
        Ghost_listObj rightVal = evalListHelper(r->right);
        return listOps[var](leftVal, rightVal);
    }
    
    // operand
    if(argMap.find(var) != argMap.end())
    {
        return argMap[var];
    }
    else
    {
        return Ghost_listObj(var);
    }
}

// update argument mapping table everytime call function
inline void ExprTree::setArgMap(const std::vector<std::string> & argList)
{
    for(size_t i = 0; i < argList.size(); ++i)
    {
        argMap[argTbl[i]] = argList[i];
    }
}

// evaluate integer
Ghost_intObj ExprTree::evalInteger(const std::vector<std::string> & argList)
{
    setArgMap(argList);
    return evalIntHelper(root);
}

// evaluate float
Ghost_floatObj ExprTree::evalFloat(const std::vector<std::string> & argList)
{
    setArgMap(argList);
    return evalFloatHelper(root);
}

// evaluate string
Ghost_stringObj ExprTree::evalString(const std::vector<std::string> & argList)
{
    setArgMap(argList);
    return evalStringHelper(root);
}

// evaluate list
Ghost_listObj ExprTree::evalList(const std::vector<std::string> & argList)
{
    setArgMap(argList);
    return evalListHelper(root);
}