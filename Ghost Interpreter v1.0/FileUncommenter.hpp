#ifndef FILE_UNCOMMENTER_HPP__
#define FILE_UNCOMMENTER_HPP__

#include <vector>
#include <string>
#include <iostream>

class FileUncommenter
{
private:
    bool in_block = false;

public:
    // like C and C++, Ghost Language use // and /* */ as comment block
    std::vector<std::string> uncomment(const std::vector<std::string> & content)
    {
        std::string buffer;
        std::vector<std::string> res;
        bool in_block = false;
        for(std::string line: content)
        {
            int N = line.length();
            for(int i = 0; i < N; i++)
            {
                char c = line[i];
                
                // '//' -> Line Comment
                if(c == '/' && i + 1 < N && line[i + 1] == '/' && !in_block) i = N;
                
                // '/*' -> Start of Block Comment
                else if(c == '/' && i + 1 < N && line[i + 1] == '*' && !in_block)
                {
                    i++;
                    in_block = true;
                }
                
                // '*/' -> End of Block Comment
                else if(c == '*' && i + 1 < N && line[i + 1] == '/' and in_block)
                {
                    i++;
                    in_block = false;
                }
                
                // Normal Charaters
                else if(!in_block) buffer += c;
            }
            
            if(!in_block && !buffer.empty()) 
            {
                res.push_back(buffer);
                buffer = "";
            }
        }
        
        return res;
    }
};

#endif