#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>

class InfixExprTree
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

        void updataPriority(unsigned p=3)
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

/*
            debug information
            std::cout << "current node is " << token << std::endl;
            if(r)
            {
                std::cout << "root is " << r->val << std::endl;
                if(r->left)
                {
                    std::cout << "left node is " << r->left->val << std::endl;
                    if(r->left->left)
                    {
                        std::cout << "left left node is " << r->left->left->val << std::endl;
                        if(r->left->left->left) 
                        {
                            std::cout << "left left left node is " << r->left->left->left->val << std::endl;
                            if(r->left->left->left->left)
                            {
                                std::cout << "left left left left node is " << r->left->left->left->left->val << std::endl;
                            }
                            if(r->left->left->left->right)
                            {
                                std::cout << "left left left right node is " << r->left->left->left->right->val << std::endl;
                            }
                        }
                        if(r->left->left->right)
                        {
                            std::cout << "left left right node is " << r->left->left->right->val << std::endl;
                            if(r->left->left->right->left)
                            {
                                std::cout << "left left right left node is " << r->left->left->right->left->val << std::endl;
                            }
                            if(r->left->left->right->right)
                            {
                                std::cout << "left left right right node is " << r->left->left->right->right->val << std::endl;
                            }
                        }
                    }
                    if(r->left->right)
                    {
                        std::cout << "left right node is " << r->left->right->val << std::endl;
                        if(r->left->right->left) 
                        {
                            std::cout << "left right left node is " << r->left->right->left->val << std::endl;
                            if(r->left->right->left->left)
                            {
                                std::cout << "left right left left node is " << r->left->right->left->left->val << std::endl;
                            }
                            if(r->left->right->left->right)
                            {
                                std::cout << "left right left right node is " << r->left->right->left->right->val << std::endl;
                            }
                        }
                        if(r->left->right->right)
                        {
                            std::cout << "left right right node is " << r->left->right->right->val << std::endl;
                            if(r->left->right->right->left)
                            {
                                std::cout << "left right right left node is " << r->left->right->right->left->val << std::endl;
                            }
                            if(r->left->right->right->right)
                            {
                                std::cout << "left right right right node is " << r->left->right->right->right->val << std::endl;
                            }
                        }
                    }
                }
                if(r->right)
                {
                    std::cout << "right node is " << r->right->val << std::endl;
                    if(r->right->left)
                    {
                        std::cout << "right left node is " << r->right->left->val << std::endl;
                        if(r->right->left->left) 
                        {
                            std::cout << "right left left node is " << r->right->left->left->val << std::endl;
                            if(r->right->left->left->left)
                            {
                                std::cout << "right left left left node is " << r->right->left->left->left->val << std::endl;
                            }
                            if(r->right->left->left->right)
                            {
                                std::cout << "right left left right node is " << r->right->left->left->right->val << std::endl;
                            }
                        }
                        if(r->right->left->right)
                        {
                            std::cout << "right left right node is " << r->right->left->right->val << std::endl;
                            if(r->right->left->right->left)
                            {
                                std::cout << "right left right left node is " << r->right->left->right->left->val << std::endl;
                            }
                            if(r->right->left->right->right)
                            {
                                std::cout << "right left right right node is " << r->right->left->right->right->val << std::endl;
                            }
                        }
                    }
                    if(r->right->right)
                    {
                        std::cout << "right right node is " << r->right->right->val << std::endl;
                        if(r->right->right->left) 
                        {
                            std::cout << "right right left node is " << r->right->right->left->val << std::endl;
                            if(r->right->right->left->left)
                            {
                                std::cout << "right right left left node is " << r->right->right->left->left->val << std::endl;
                            }
                            if(r->right->right->left->right)
                            {
                                std::cout << "right right left right node is " << r->right->right->left->right->val << std::endl;
                            }
                        }
                        if(r->right->right->right)
                        {
                            std::cout << "right right right node is " << r->right->right->right->val << std::endl;
                            if(r->right->right->right->left)
                            {
                                std::cout << "right right right left node is " << r->right->right->right->left->val << std::endl;
                            }
                            if(r->right->right->right->right)
                            {
                                std::cout << "right right right right node is " << r->right->right->right->right->val << std::endl;
                            }
                        }
                    }
                }
            }
*/
        }

        if(inBrace)
        {
            r->updataPriority();
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

int main(void)
{
    //1+2+555*(8/4+5)/3*(6-2)
    std::vector<std::string> expression1{"(", "1", "+", "2", ")", "*", "(", "3", "+", "2", ")", "+", "2", "+", "5", "+", "(", "5", "+", "7", ")"};
    std::vector<std::string> expression2{"1", "+", "2"};
    std::vector<std::string> expression3{"3", "*", "2", "+", "5", "/", "2", "*", "(", "4", "-", "1", ")", "-", "1", "*", "3"};
    std::vector<std::string> expression4{"1", "+", "2", "+", "555", "*", "(", "8", "/", "4", "+", "5", ")", "/", "3", "*", "(", "6", "-", "2", ")"};
    ExprTree exprTree = ExprTree();
    exprTree.buildTree(expression4);
//    exprTree.inorder();
    std::cout << exprTree.eval() << std::endl;
}