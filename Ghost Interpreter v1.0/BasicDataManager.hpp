#ifndef BASIC_DATA_MANAGER_HPP__
#define BASIC_DATA_MANAGER_HPP__

#include "ErrorHandler.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include <cctype>
#include <string>
#include <vector>

struct BasicDataManager : virtual public ErrorHandler
{
public:
    // enum class to define variable type
    enum class varType { INT_VAR, FLOAT_VAR, STRING_VAR, LIST_VAR, NULL_VAR };

    // check value type of string command input
    varType getVarType(const std::string & cmd)
    {
        // LIST_VAR: start with '[' and ends with ']'
        if(cmd[0] == '[' && cmd.back() == ']')
        {
            return varType::LIST_VAR;
        }

        // STRING_VAR: start with '"', and ends with '"'
        else if(cmd[0] == '"' && cmd.back() == '"')
        {
            return varType::STRING_VAR;
        }

        size_t cnt = 0; // count the amount of dot(.)
        for(char c : cmd)
        {
            if(c == '.')
            {
                ++cnt;
                if(cnt > 1)
                {
                    return varType::NULL_VAR;
                }
            }
            else if(!isdigit(c))
            {
                return varType::NULL_VAR;
            }
        }
        return cnt == 0 ? varType::INT_VAR : varType::FLOAT_VAR;
    }

    // task is to push back and clear existing string
    void pushClear(std::vector<std::string> & ops, std::string & op)
    {
        if(!op.empty())
        {
            ops.push_back(op);
            op.clear();
        }
    }

    // task is to find the next matched right character
    // char c is the character to match(targeted right half)
    // int i is the index of the left character in the cmd string
    int findMatched(const std::string & cmd, char left, char right, int i)
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

    // task is to find the next matched right character
    // char c is the character to match(targeted right half)
    // int i is the index of the left character in the cmd string
    int findMatched(const std::vector<std::string> & cmd_vec, const std::string & left, const std::string & right, int i)
    {
        int j = i + 1;
        int left_cnt = 0;
        int N = cmd_vec.size();
        for(; j < N; ++j)
        {
            std::string s = cmd_vec[j];
            if(s == right)
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
            else if(s == left)
            {
                ++left_cnt;
            }
        }
        return j;
    }
};

#endif