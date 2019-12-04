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

class ExprTree : virtual public BasicDataManager
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

    // pre-evaluate the return type after building the expression tree
    varType retType;

    // parameters of the expression
    std::vector<std::string> argTbl;

    // argument mapping from formal argument ot actual argument
    // using formal argument as key, actual argument as value
    std::unordered_map<std::string, std::string> argMap;

    Node * buildTreeHelper(std::vector<std::string> & expression, bool inBrace); // character-wise parse expression
    Node * copyHelper(Node * current); // helper function for copy constructor and copy assignment    
    void evalRetTypeHelper(Node * r); // pre-evaluate the return type of the expression after building the expression tree    
    void deleteHelper(Node * r); // recursively de-allocate allocated memory

public:
    // default constructor
    ExprTree() : 
        root{nullptr},
        retType{varType::NULL_VAR} 
        {}

    // constructor
    ExprTree(std::vector<std::string> & _argTbl, std::vector<std::string> & _expression) : 
        root{nullptr},
        retType{varType::NULL_VAR},
        argTbl{_argTbl}
    {
        root = buildTreeHelper(_expression, false);
        evalRetTypeHelper(root);
    }    

    // copy constructor
    ExprTree(const ExprTree & rhs) : 
        root{nullptr},
        retType{rhs.retType},
        argTbl{rhs.argTbl},
        argMap{rhs.argMap}
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
            retType = rhs.retType;
            argTbl = rhs.argTbl;
            argMap = rhs.argMap;
        }
        return *this;
    }

    // move constructor
    ExprTree(ExprTree && rhs) :
        root{nullptr}
    {
        std::swap(root, rhs.root);
        std::swap(retType, rhs.retType);
        std::swap(argTbl, rhs.argTbl);
        std::swap(argMap, rhs.argMap);
    }

    // move assignment
    ExprTree & operator=(ExprTree && rhs)
    {
        if(this != &rhs)
        {
            std::swap(root, rhs.root);
            std::swap(retType, rhs.retType);
            std::swap(argTbl, rhs.argTbl);
            std::swap(argMap, rhs.argMap);
        }
        return *this;
    }

    // destructor
    ~ExprTree() noexcept
    {
        deleteHelper(root);
    }

    bool isValidArgument(const std::vector<std::string> & _argTbl) const; // check validility of argument list
    varType getRetType() const; // get pre-evaluated return type




    void inorder(Node * r)
    {
        if(r != nullptr)
        {
            inorder(r->left);
            std::cout << r->val << " " << std::flush;
            inorder(r->right);
        }
    }


    void inorder()
    {
        inorder(root);
    }



};

#endif