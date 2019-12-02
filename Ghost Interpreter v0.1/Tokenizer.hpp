// Tokenizer take charge of tokenizing string into vector

#ifndef TOKENIZER_HPP__
#define TOKENIZER_HPP__

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

class Tokenizer
{
private:
    // delimiters used to split the command line input
    const std::unordered_set<char> unidelim {'=', '+', '-', '*', '/', '%', '&', '|', '>', '<', '!'};
    const std::unordered_set<char> bidelim_postfix {'=', '+', '-', '&', '|'}; // eg: +=, ==, ++

    // helper function for tokenize()
    // task is to push back and clear existing string
    inline void pushClear(std::vector<std::string> & ops, std::string & op)
    {
        if(!op.empty())
        {
            ops.push_back(op);
            op.clear();
        }
    }

    // helper function for split()
    // task is to find the next matched right character
    // char c is the character to match(targeted right half)
    // int i is the index of the left character in the cmd string
    int findMatched(std::string & cmd, char left, char right, int i)
    {
        int j = i + 1;
        int left_cnt = 0;
        int N = cmd.length();
        for(; j < N; ++j)
        {
            char c = cmd[j];
            if(c == right)
            {
               if(left_cnt == 0)
               {
                    break;
               }
               else
               {
                    --left_cnt;
               }
            }
            else if(c == left)
            {
                ++left_cnt;
            }
        }
        return j;
    }

public:
    // split the command string into vector
    std::vector<std::string> tokenize(std::string & cmd)
    {
        int N = cmd.length();
        std::vector<std::string> ops;
        std::string op;
        for(int i = 0; i < N; ++i)
        {
            char c = cmd[i];

            // space as delimiter
            // semicolon as valid terminator
            if(c == ' ' || c == '\t' || c == ',' || c == ';')
            {
                // push current string to the vector if applicable
                pushClear(ops, op);
            }

            // '"' check for string
            else if(c == '"')
            {
                // push current string to the vector if applicable
                pushClear(ops, op);

                // search for the matched right '"'
                int j = findMatched(cmd, '"', '"', i);

                // append string to ops
                ops.push_back(cmd.substr(i, j - i + 1));
                i = j; // assign right '"' to i, since next loop, i will be i + 1
            }

            // '(' check for bracket
            else if(c == '(')
            {
                // push current string to the vector if applicable
                pushClear(ops, op);

                // search for the next matched right 
                int j = findMatched(cmd, '(', ')', i);

                // recursively substring in the cmd string
                std::string bracketed_cmd = cmd.substr(i + 1, j - i - 1);
                std::vector<std::string> bracted_ops = tokenize(bracketed_cmd);
                ops.push_back("(");
                ops.insert(ops.end(), bracted_ops.begin(), bracted_ops.end());
                ops.push_back(")");
                i = j;
            }

            // '[' check for Ghost_listObj
            else if(c == '[')
            {
                // push current string to the vector if applicable
                pushClear(ops, op);

                // search for the next matched right 
                int j = findMatched(cmd, '[', ']', i);

                // append string to ops
                ops.push_back(cmd.substr(i, j - i + 1));
                i = j; // assign right '"' to i, since next loop, i will be i + 1
            }

            // uni-operator: +, - ...
            else if(unidelim.find(c) != unidelim.end() && i + 1 < N && bidelim_postfix.find(cmd[i + 1]) == bidelim_postfix.end())
            {
                // push current string to the vector if applicable
                pushClear(ops, op);
                ops.push_back(cmd.substr(i, 1));
            }

            // bi-operator: ++, +=, == ...
            else if(unidelim.find(c) != unidelim.end() && i + 1 < N && bidelim_postfix.find(cmd[i + 1]) != bidelim_postfix.end())
            {
                // push current string to the vector if applicable
                pushClear(ops, op);
                ops.push_back(cmd.substr(i, 2));
                ++i;
            }

            // common characters
            else
            {
                op += c;
            }
        }

        // the last part of the command
        pushClear(ops, op);

        // debug information
        std::for_each(ops.begin(), ops.end(), [](std::string s) { std::cout << s << " | " << std::flush; });
        std::cout << std::endl;
        
        return ops;
    }
};

#endif