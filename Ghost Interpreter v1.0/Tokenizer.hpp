// Tokenizer take charge of tokenizing string into vector

#ifndef TOKENIZER_HPP__
#define TOKENIZER_HPP__

#include "BasicDataManager.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>

class Tokenizer : virtual BasicDataManager
{
private:
    // delimiters used to split the command line input
    const std::unordered_set<char> unidelim {'=', '+', '-', '*', '/', '%', '&', '|', '>', '<', '!'};
    const std::unordered_set<char> bidelim_postfix {'=', '+', '-', '&', '|'}; // eg: +=, ==, ++

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

                // no charater between "()"
                if(j == i + 1)
                {
                    ops.push_back("(");
                    ops.push_back(")");
                    i = j;
                }

                else
                {
                    // recursively substring in the cmd string
                    std::string bracketed_cmd = cmd.substr(i + 1, j - i - 1);
                    std::vector<std::string> bracted_ops = tokenize(bracketed_cmd);
                    ops.push_back("(");
                    ops.insert(ops.end(), bracted_ops.begin(), bracted_ops.end());
                    ops.push_back(")");
                    i = j;
                }
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
/*
        // debug information
        std::for_each(ops.begin(), ops.end(), [](std::string s) { std::cout << s << " | " << std::flush; });
        std::cout << std::endl;
*/        
        return ops;
    }
};

#endif