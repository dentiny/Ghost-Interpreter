#ifndef EXPR_TREE_HPP__
#define EXPR_TREE_HPP__

#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include "BasicDataManager.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

class ExprTree : virtual BasicDataManager
{
private:
    class Node
    {
    private:
        std::unordered_map<std::string, unsigned> priorityScale
        {
            {"+", 1},
            {"-", 1},
            {"*", 2},
            {"/", 2}
        };

    public:
        std::string val;
        Node * left;
        Node * right;
        unsigned priority;

        Node(std::string _val) :
            val{_val},
            left{nullptr},
            right{nullptr}
            {
                // constant or variable
                priority = (priorityScale.find(val) == priorityScale.end()) ? 0 : priorityScale[_val];
            }

        void updatePriority(unsigned p=3)
        {
            priority = p;
        }

        unsigned getPriority()
        {
            return priority;
        }
    };

    // operators
    std::unordered_set<std::string> ops{"+", "-", "*", "/"};

    // root node of the expression tree
    Node * root;

    // parameters of the expression
    std::vector<std::string> paramTbl;

    // character-wise parse expression
    Node * buildTreeHelper(std::vector<std::string> & expression, bool inBrace=false)
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
    Node * copyHelper(Node * current)
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

    // helper function for delete()
    // recursively de-allocate allocated memory
    void deleteHelper(Node * r)
    {
        if(r != nullptr)
        {
            deleteHelper(r->left);
            deleteHelper(r->right);
            delete r;
        }
    }

public:
    // default constructor
    ExprTree() : root{nullptr} {}

    // constructor
    ExprTree(std::vector<std::string> & _paramTbl, std::vector<std::string> & _expression) : 
        root{nullptr},
        paramTbl{_paramTbl}
    {
        root = buildTreeHelper(_expression);
    }    

    // copy constructor
    ExprTree(const ExprTree & rhs) : 
        root{nullptr},
        paramTbl{rhs.paramTbl}
    {
        root = copyHelper(rhs.root);
    }

    // copy assignment
    ExprTree & operator=(const ExprTree & rhs)
    {
        if(this != &rhs)
        {
            deleteHelper(root);
            root = copyHelper(rhs.root);
            paramTbl = rhs.paramTbl;
        }
        return *this;
    }

    // move constructor
    ExprTree(ExprTree && rhs) :
        root{nullptr}
    {
        std::swap(root, rhs.root);
        std::swap(paramTbl, rhs.paramTbl);
    }

    // move assignment
    ExprTree & operator=(ExprTree && rhs)
    {
        if(this != &rhs)
        {
            std::swap(root, rhs.root);
            std::swap(paramTbl, rhs.paramTbl);
        }
        return *this;
    }

    // destructor
    ~ExprTree()
    {
        deleteHelper(root);
    }
};

#endif