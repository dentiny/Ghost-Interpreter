#ifndef UNCOMMENTER_HPP__
#define UNCOMMENTER_HPP__

#include <string>

class Uncommenter
{
public:
    // like C and C++, Ghost Language use // and /* */ as comment block
    void uncomment(std::string & cmd)
    {
        // uncomment the statement
        bool in_block = false; // whether in comment block
        std::string buffer; // buffer as uncommented statement
        int N = cmd.length();
        for(int i = 0; i < N; ++i)
        {
            char c = cmd[i];

            // "//" -> line comment
            if(c == '/' && i + 1 < N && cmd[i + 1] == '/' && !in_block)
            {
                i = N;
            }

            // "/*" -> start of block comment
            else if(c == '/' && i + 1 < N && cmd[i + 1] == '*' && !in_block)
            {
                ++i;
                in_block = true;
            }

            // "*/" -> end of block comment
            else if(c == '*' && i + 1 < N && cmd[i + 1] == '/' && in_block)
            {
                ++i;
                in_block = false;
            }

            // normal characters
            else if(!in_block)
            {
                buffer += c;
            }
        }
        cmd = buffer;
    }
};

#endif