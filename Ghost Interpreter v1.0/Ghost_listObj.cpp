#include "BasicDataManager.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

// helper function for constuctor
// split the string into meaningful substrings which could make a Ghost object
std::vector<std::string> Ghost_listObj::tokenize(std::string & s)
{
    std::string line = s;
    if(line.length() >= 2 && line[0] == '[' && line.back() == ']')
    {
        line = line.substr(1, line.length() - 2);
    }
    std::string temp;
    std::vector<std::string> res;
    size_t N = line.length();
    for(size_t i = 0; i < N; ++i)
    {
        char c = line[i];

        // space as delimiter
        if(c == ' ' || c == '\t' || c == ',')
        {
            // push current string to the vector if applicable
            pushClear(res, temp);
        }

        // '"' check for string
        else if(c == '"')
        {
            // push current string to the vector if applicable
            pushClear(res, temp);

            // search for the matched right '"'
            int j = findMatched(line, '"', '"', i);

            // append string to ops
            res.push_back(line.substr(i, j - i + 1));
            i = j; // assign right '"' to i, since next loop, i will be i + 1
        }

        // '[' check for Ghost_listObj
        else if(c == '[')
        {
            // push current string to the vector if applicable
            pushClear(res, temp);

            // search for the matched right ']'
            int j = findMatched(line, '[', ']', i);

            // append string to ops
            res.push_back(line.substr(i, j - i + 1));
            i = j; // assign right '"' to i, since next loop, i will be i + 1
        }

        // common characters
        else
        {
            temp += c;
        }
    }   

    // the last part of the command
    pushClear(res, temp);
/*
    // debug information
    std::for_each(res.begin(), res.end(), [](std::string s) { std::cout << s << " | " << std::flush; });
    std::cout << std::endl;
*/    
    return res;
}   

// paramatric constructor
Ghost_listObj::Ghost_listObj(std::string s)
{
    std::vector<std::string> tokens = tokenize(s);
    for(std::string token : tokens)
    {
        T temp;
        varType typeRes = getVarType(token);
        if(typeRes == varType::INT_VAR)
        {
            temp.type = varType::INT_VAR;
            temp.intObj = Ghost_intObj(token);
            temp.floatObj = Ghost_floatObj();
            temp.stringObj = Ghost_stringObj();
        }
        else if(typeRes == varType::FLOAT_VAR)
        {
            temp.type = varType::FLOAT_VAR;
            temp.intObj = Ghost_intObj();
            temp.floatObj = Ghost_floatObj(token);
            temp.stringObj = Ghost_stringObj();
        }
        else if(typeRes == varType::STRING_VAR)
        {
            temp.type = varType::STRING_VAR;
            temp.intObj = Ghost_intObj();
            temp.floatObj = Ghost_floatObj();
            temp.stringObj = Ghost_stringObj(token);
        }
        else if(typeRes == varType::NULL_VAR)
        {
            if(err_no != INVALID_INPUT)
            {
                err_no = INVALID_ARG_LIST;
            }
            std::cout << "Encounter invalid object while constructing Ghost_listObj" << std::endl;
        }
        val.push_back(temp);
    }
}

// move constructor
Ghost_listObj::Ghost_listObj(Ghost_listObj && rhs)
{
    std::swap(val, rhs.val);
}

// copy assignment
Ghost_listObj & Ghost_listObj::operator=(const Ghost_listObj & rhs)
{
    if(this != &rhs)
    {
        val = rhs.val;
    }
    return *this;
}

// move assignment
Ghost_listObj & Ghost_listObj::operator=(Ghost_listObj && rhs)
{
    if(this != &rhs)
    {
        std::swap(val, rhs.val);
    }
    return *this;
}

// operator + overload
Ghost_listObj Ghost_listObj::operator+(Ghost_listObj & rhs) const
{
    Ghost_listObj temp(*this);
    std::vector<T> temp_val = rhs.getVal();
    for(T obj : temp_val)
    {
        temp.val.push_back(obj);
    }
    return temp;
}

// operator += overload
Ghost_listObj & Ghost_listObj::operator+=(Ghost_listObj & rhs)
{
    std::vector<T> temp_val = rhs.getVal();
    for(T obj : temp_val)
    {
        val.push_back(obj);
    }
    return *this;
}

// operator == overload
bool Ghost_listObj::operator==(Ghost_listObj & rhs) const
{
    return val == rhs.val;
}

// operator != overload
bool Ghost_listObj::operator!=(Ghost_listObj & rhs) const
{
    return val != rhs.val;
}

// decide comparator by string
bool Ghost_listObj::compare(std::string op, Ghost_listObj & rhs) const
{   
    if(op == "==")
    {
        return *this == rhs;
    }
    else if(op == "!=")
    {
        return *this != rhs;
    }

    std::cout << "Unknown operator from Ghost_listObj" << std::endl;
    return true;
}

// decide whether the list is empty
bool Ghost_listObj::empty() const
{
    return val.empty();
}

// append a data into the list by string
void Ghost_listObj::append(std::string token)
{
    Ghost_listObj temp(token);
    *this = *this + temp;
}

// append a integer into the list
void Ghost_listObj::append(Ghost_intObj & obj)
{
    T temp;
    temp.type = varType::INT_VAR;
    temp.intObj = obj;
    val.push_back(temp);
}

// append a float into the list
void Ghost_listObj::append(Ghost_floatObj & obj)
{
    T temp;
    temp.type = varType::FLOAT_VAR;
    temp.floatObj = obj;
    val.push_back(temp);
}

// append a string into the list
void Ghost_listObj::append(Ghost_stringObj & obj)
{
    T temp;
    temp.type = varType::STRING_VAR;
    temp.stringObj = obj;
    val.push_back(temp);
}

// get the size of the vector
size_t Ghost_listObj::getSize() const
{
    return val.size();
}

// get value
std::vector<Ghost_listObj::T> Ghost_listObj::getVal() const
{
    return val;
}

// get value in string
std::string Ghost_listObj::getVal_s() const
{
    std::vector<T> val = getVal();
    std::string val_s = "[";
    for(auto it = val.begin(); it != val.end(); ++it)
    {
        varType typeRes = it->type;
        if(typeRes == varType::INT_VAR)
        {
            val_s += (it->intObj).getVal_s();
        }
        else if(typeRes == varType::FLOAT_VAR)
        {
            val_s += (it->floatObj).getVal_s();
        }
        else if(typeRes == varType::STRING_VAR)
        {
            val_s += (it->stringObj).getVal_s();
        }
        else
        {
            std::cout << "Get object string error" << std::endl;
        }
        val_s += "  ";
    }
    val_s += "]";
    return val_s;
}

// get type
std::string Ghost_listObj::getType() const
{
    return "Ghost List";
}

// bool() overload
Ghost_listObj::operator bool() const
{
    return !val.empty();
}