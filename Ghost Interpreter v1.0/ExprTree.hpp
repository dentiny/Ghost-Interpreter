#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

class ExprTree
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
            right{nullptr},
            priority{priorityScale[_val]}
            {}

        void updatePriority(unsigned p=3)
        {
            priority = p;
        }

        unsigned getPriority()
        {
            return priority;
        }
    };

    std::unordered_map<std::string, std::function<int(int, int)>> ops
    {
        {"+", [](int num1, int num2) { return num1 + num2; }},
        {"-", [](int num1, int num2) { return num1 - num2; }},
        {"*", [](int num1, int num2) { return num1 * num2; }},
        {"/", [](int num1, int num2) { return num1 / num2; }}
    };

    // root node of the expression tree
    Node * root;

    // find the first match right parenthesis
    int findMatched(std::vector<std::string> & expression, int i)
    {
        int N = expression.size();
        int j = i + 1;
        int left = 0;
        for(; j < N; ++j)
        {
            std::string token = expression[j];
            if(token == ")")
            {
                if(left == 0)
                {
                    break;
                }
                else
                {
                    --left;
                }
            }
            else if(token == "(")
            {
                ++left;
            }
        }
        return j;
    }

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
                int j = findMatched(expression, i);
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

    // helper function for eval()
    // recursively eval the node
    int evalHelper(Node * r)
    {
        if(r->left != nullptr && r->right != nullptr)
        {
            int leftVal = evalHelper(r->left);
            int rightVal = evalHelper(r->right);
            return ops[r->val](leftVal, rightVal);
        }
        return stol(r->val);
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
    // constructor
    ExprTree() : root{nullptr} {}    

    // build the expression tree
    void buildTree(std::vector<std::string> & expression)
    {
        root = buildTreeHelper(expression);
    }

    // evaluate the expression
    int eval()
    {
        return evalHelper(root);
    }

    // destructor
    ~ExprTree()
    {
        deleteHelper(root);
    }
};