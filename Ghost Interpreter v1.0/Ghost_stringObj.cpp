#include "Ghost_intObj.hpp"
#include "Ghost_stringObj.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

// move constructor
Ghost_stringObj::Ghost_stringObj(Ghost_stringObj && rhs)
{
    std::swap(val, rhs.val);
}

// copy assignment
Ghost_stringObj & Ghost_stringObj::operator=(const Ghost_stringObj & rhs)
{
    if(this != &rhs)
    {
        val = rhs.val;
    }
    return *this;
}

// move assignment
Ghost_stringObj & Ghost_stringObj::operator=(Ghost_stringObj && rhs)
{
    if(this != &rhs)
    {
        std::swap(val, rhs.val);
    }
    return *this;
}

// Ghost_stringObj::operator + overload with string
Ghost_stringObj Ghost_stringObj::operator+(std::string rhs) const
{
    // "aaa""bbb" => "aaabbb"
    std::string catRes = val.substr(0, val.length() - 1) + rhs.substr(1, rhs.length() - 1);
    return Ghost_stringObj(catRes);
}

// Ghost_stringObj::operator += overload with string
Ghost_stringObj & Ghost_stringObj::operator+=(std::string rhs)
{
    *this = *this + rhs;
    return *this;
}

// Ghost_stringObj::operator + overload
Ghost_stringObj Ghost_stringObj::operator+(Ghost_stringObj & rhs) const
{
    std::string catRes = val.substr(0, val.length() - 1) + rhs.val.substr(1, rhs.val.length() - 1);
    return Ghost_stringObj(catRes);
}

// Ghost_stringObj::operator += overload
Ghost_stringObj & Ghost_stringObj::operator+=(Ghost_stringObj & rhs)
{
    *this = *this + rhs;
    return *this;
}

// Ghost_stringObj::operator * overload with integer
Ghost_stringObj Ghost_stringObj::operator*(long long num) const
{
    std::string temp(val);
    long long sz = num - 1;
    while(sz-- > 0) { temp += val; }
    return Ghost_stringObj(temp);
}

// Ghost_stringObj::operator *= overload with integer
Ghost_stringObj & Ghost_stringObj::operator*=(long long num)
{
    *this = *this * num;
    return *this;
}

// Ghost_stringObj::operator * overload
Ghost_stringObj Ghost_stringObj::operator*(Ghost_intObj & rhs) const
{
    Ghost_stringObj temp(*this);
    long long sz = rhs.getVal() - 1;
    while(sz-- > 0) temp.val += val;
    return temp;
}

// Ghost_stringObj::operator *= overload
Ghost_stringObj & Ghost_stringObj::operator*=(Ghost_intObj & rhs)
{
    *this = *this * rhs;
    return *this;
}

// operator * overload with Ghost_stringObj
Ghost_stringObj Ghost_stringObj::operator*(Ghost_stringObj & rhs) const
{
    Ghost_intObj obj(rhs.val);
    return *this * obj;
}

// operator *= overload with Ghost_stringObj
Ghost_stringObj & Ghost_stringObj::operator*=(Ghost_stringObj & rhs)
{
    *this = *this * rhs;
    return *this;
}

// less than with constant
bool Ghost_stringObj::operator<(std::string s) const
{
    return val < s;
} 

// less or equal with constant
bool Ghost_stringObj::operator<=(std::string s) const
{
    return val <= s;
}

// larger than with constant
bool Ghost_stringObj::operator>(std::string s) const
{
    return val > s;
}

// larger or equal with constant
bool Ghost_stringObj::operator>=(std::string s) const
{
    return val >= s;
}

// equal with constant
bool Ghost_stringObj::operator==(std::string s) const
{
    return val == s;
}

// not equal with constant
bool Ghost_stringObj::operator!=(std::string s) const
{
    return val != s;
}

// less than
bool Ghost_stringObj::operator<(Ghost_stringObj & rhs) const
{
    return val < rhs.val;
}

// less or equal
bool Ghost_stringObj::operator<=(Ghost_stringObj & rhs) const
{
    return val <= rhs.val;
}

// larger than
bool Ghost_stringObj::operator>(Ghost_stringObj & rhs) const
{
    return val > rhs.val;
}

// larger or equal
bool Ghost_stringObj::operator>=(Ghost_stringObj & rhs) const
{
    return val >= rhs.val;
}

// equal to
bool Ghost_stringObj::operator==(Ghost_stringObj & rhs) const
{
    return val == rhs.val;
}

// not equal to
bool Ghost_stringObj::operator!=(Ghost_stringObj & rhs) const
{
    return val != rhs.val;
}

// decide which comparator by string
bool Ghost_stringObj::compare(std::string op, Ghost_stringObj & rhs) const
{
    if(op == "<")
    {
        return *this < rhs;
    }
    else if(op == ">")
    {
        return *this > rhs;
    }
    else if(op == "<=")
    {
        return *this <= rhs;
    }
    else if(op == ">=")
    {
        return *this >= rhs;
    }
    else if(op == "==")
    {
        return *this == rhs;
    }
    else if(op == "!=")
    {
        return *this != rhs;
    }

    std::cout << "Unknown Ghost_stringObj::operator From Ghost_stringObj" << std::endl;
    return false;
}

// whether the object is empty
bool Ghost_stringObj::isEmpty() const
{
    return val.empty();
}

// get size
size_t Ghost_stringObj::getSize() const
{
    return val.length();
}

// get value
std::string Ghost_stringObj::getVal() const
{
    return val;
}

// get value in string
std::string Ghost_stringObj::getVal_s() const
{
    return val;
} 

// get type
std::string Ghost_stringObj::getType() const
{
    return "Ghost String";
}

// transform to uppercase
Ghost_stringObj Ghost_stringObj::toUpper() const
{
    std::string temp = val;
    std::transform(temp.begin(), temp.end(), temp.begin(), [](char c) { return std::toupper(c); });
    return Ghost_stringObj(temp);
}

// transform to lowercase
Ghost_stringObj Ghost_stringObj::toLower() const
{
    std::string temp = val;
    std::transform(temp.begin(), temp.end(), temp.begin(), [](char c) { return std::tolower(c); });
    return Ghost_stringObj(temp);
}

// transform to uppercase
void Ghost_stringObj::toUpper()
{
    std::transform(val.begin(), val.end(), val.begin(), [](char c) { return std::toupper(c); });
}

// transform to lowercase
void Ghost_stringObj::toLower()
{
    std::transform(val.begin(), val.end(), val.begin(), [](char c) { return std::tolower(c); });
}

Ghost_stringObj::operator bool() const
{
    return !val.empty();
}