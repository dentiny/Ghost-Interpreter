// this code is created to generate expression tree from prefix expression

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

class ExprTree
{
private:
    class Node
    {
    public:
        std::string op;
        Node * left;
        Node * right;

        Node(std::string _op) : 
        op{_op},
        left{nullptr},
        right{nullptr}
        {}
    };

    // unordered map to store functionality of operators
    std::unordered_map<std::string, std::function<int(int, int)>> f
    {
        {"+", [](int num1, int num2) { return num1 + num2; }},
        {"-", [](int num1, int num2) { return num1 - num2; }},
        {"*", [](int num1, int num2) { return num1 * num2; }},
        {"/", [](int num1, int num2) { return num1 / num2; }}
    };

    // helper function for eval
    // recursively evaluate the value of the current node
    int evalHelper(Node * r)
    {
        std::string op = r->op;
        // operator
        if(f.find(op) != f.end())
        {
            int l_val = evalHelper(r->left);
            int r_val = evalHelper(r->right);
            return f[op](l_val, r_val);
        }

        // operand
        else
        {
            return std::stoi(op);
        }

        return -1;
    }

    // helper function for destructor
    // recursively in postorder delete every node in the expression tree
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
    Node * root;

    // constructor
    ExprTree() : root{nullptr} {}

    // generate expression by prefix expression
    void genTree(std::vector<std::string> & expression)
    {
        std::for_each(expression.begin(), expression.end(), [](std::string s){ std::cout << s << " " << std::flush; });
        Node ** p = &root;
        Node ** prev = &root;
        for(std::string op : expression)
        {
            *p = new Node(op);

            // operator
            if(f.find(op) != f.end())
            {
                prev = p;
                p = &((*p)->left);
            }

            // operand
            else
            {
                p = &((*prev)->right);
            }
        }
    }

    // evaluate the expression
    int eval()
    {
        return evalHelper(root);
    }

    // destructor
    ~ExprTree() noexcept
    {
        deleteHelper(root);
    }
};