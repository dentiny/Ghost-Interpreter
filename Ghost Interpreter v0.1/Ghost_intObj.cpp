#include "Ghost_intObj.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

// parametric constructor
Ghost_intObj::Ghost_intObj(std::string s)
{
    val = stoll(s, nullptr, 10);
}

// move constructor
Ghost_intObj::Ghost_intObj(Ghost_intObj && rhs)
{
    std::swap(val, rhs.val);
}

// copy assignment
Ghost_intObj & Ghost_intObj::operator=(const Ghost_intObj & rhs)
{
    if(this != &rhs)
    {
        val = rhs.val;
    }
    return *this;
}

// move assignment
Ghost_intObj & Ghost_intObj::operator=(Ghost_intObj && rhs)
{
    if(this != &rhs)
    {
        std::swap(val, rhs.val);
    }
    return *this;
}

// get positive
Ghost_intObj Ghost_intObj::operator+() const
{
    Ghost_intObj temp(*this);
    return temp;
}

// get negative
Ghost_intObj Ghost_intObj::operator-() const
{
    Ghost_intObj temp(*this);
    temp.val *= -1;
    return temp;
}

// prefix increment
Ghost_intObj Ghost_intObj::operator++()
{
    Ghost_intObj temp(*this);
    ++val;
    return temp;
}

// prefix decrement
Ghost_intObj Ghost_intObj::operator--()
{
    Ghost_intObj temp(*this);
    --val;
    return temp;
}

// postfix increment
Ghost_intObj Ghost_intObj::operator++(int i)
{
    ++val;
    return *this;
}

// postfix decrement
Ghost_intObj Ghost_intObj::operator--(int i)
{
    --val;
    return *this;
}

// Ghost_intObj::operator + overload with integer
Ghost_intObj Ghost_intObj::operator+(long long num) const
{
    Ghost_intObj temp(*this);
    temp.val += num;
    return temp;
}

// Ghost_intObj::operator += overload with integer
Ghost_intObj Ghost_intObj::operator+=(long long num)
{
    *this = *this + num;
    return *this;
}

// Ghost_intObj::operator - overload with integer
Ghost_intObj Ghost_intObj::operator-(long long num) const
{
    Ghost_intObj temp(*this);
    temp.val -= num;
    return temp;
}

// Ghost_intObj::operator -= overload with integer
Ghost_intObj Ghost_intObj::operator-=(long long num)
{
    *this = *this - num;
    return *this;
}

// Ghost_intObj::operator * overload with integer
Ghost_intObj Ghost_intObj::operator*(long long num) const
{
    Ghost_intObj temp(*this);
    temp.val *= num;
    return *this;
}

// Ghost_intObj::operator *= overload with integer
Ghost_intObj Ghost_intObj::operator*=(long long num)
{
    *this = *this * num;
    return *this;
}

// Ghost_intObj::operator / overload with integer
Ghost_intObj Ghost_intObj::operator/(long long num) const
{
    Ghost_intObj temp(*this);
    temp.val /= num;
    return *this;
}
    
// Ghost_intObj::operator /= overload with integer
Ghost_intObj Ghost_intObj::operator/=(long long num)
{
    *this = *this / num;
    return *this;
}

// Ghost_intObj::operator + overload with float
Ghost_floatObj Ghost_intObj::operator+(double num) const
{
    Ghost_floatObj temp(val);
    return temp + num;
}

// Ghost_intObj::operator - overload with float
Ghost_floatObj Ghost_intObj::operator-(double num) const
{
    Ghost_floatObj temp(val);
    return temp - num;
}

// Ghost_intObj::operator * overload with float
Ghost_floatObj Ghost_intObj::operator*(double num) const
{
    Ghost_floatObj temp(val);
    return temp * num;
}

// Ghost_intObj::operator / overload with float
Ghost_floatObj Ghost_intObj::operator/(double num) const
{
    Ghost_floatObj temp(val);
    return temp * num;
}

// Ghost_intObj::operator + overload
Ghost_intObj Ghost_intObj::operator+(Ghost_intObj & rhs) const
{
    Ghost_intObj temp(*this);
    temp.val += rhs.val;
    return temp;
}

// Ghost_intObj::operator += overload
Ghost_intObj & Ghost_intObj::operator+=(Ghost_intObj & rhs)
{
    val += rhs.val;
    return *this;
}

// Ghost_intObj::operator - overload
Ghost_intObj Ghost_intObj::operator-(Ghost_intObj & rhs) const
{
    Ghost_intObj temp(*this);
    temp.val -= rhs.val;
    return temp;
}

// Ghost_intObj::operator -= overload
Ghost_intObj & Ghost_intObj::operator-=(Ghost_intObj & rhs)
{
    val -= rhs.val;
    return *this;
}

// Ghost_intObj::operator * overload
Ghost_intObj Ghost_intObj::operator*(Ghost_intObj & rhs) const
{
    Ghost_intObj temp(*this);
    temp.val *= rhs.val;
    return temp;
}

// Ghost_intObj::operator *= overload
Ghost_intObj & Ghost_intObj::operator*=(Ghost_intObj & rhs)
{
    val *= rhs.val;
    return *this;
}

// Ghost_intObj::operator * overload with string
Ghost_stringObj Ghost_intObj::operator*(std::string & rhs) const
{
    std::string temp(rhs);
    long long sz = val - 1;
    while(sz-- > 0) { temp += rhs; }
    return Ghost_stringObj(temp);
}

// Ghost_intObj::operator * overload with Ghost_stringObj
Ghost_stringObj Ghost_intObj::operator*(Ghost_stringObj & rhs) const
{
    std::string temp(rhs.getVal());
    long long sz = val - 1;
    while(sz-- > 0) { temp += rhs.getVal(); }
    return Ghost_stringObj(temp);
}

// Ghost_intObj::operator / overload
Ghost_intObj Ghost_intObj::operator/(Ghost_intObj & rhs) const
{
    Ghost_intObj temp(*this);
    temp.val /= rhs.val;
    return temp;
}

// Ghost_intObj::operator /= overload
Ghost_intObj & Ghost_intObj::operator/=(Ghost_intObj & rhs)
{
    // check divide by zero error
    if (rhs.val == 0) 
    { 
        throw std::runtime_error("Divide by zero\n");
    } 
    val /= rhs.val;
    return *this;
}

// less than with integer
bool Ghost_intObj::operator<(long long num) const
{
    return val < num;
} 

// less or equal with integer
bool Ghost_intObj::operator<=(long long num) const
{
    return val <= num;
}

// larger with integer
bool Ghost_intObj::operator>(long long num) const
{
    return val > num;
}

// larger or equal with integer
bool Ghost_intObj::operator>=(long long num) const
{
    return val >= num;
}

// equal to integer
bool Ghost_intObj::operator==(long long num) const
{
    return val == num;
}

// not equal to integer
bool Ghost_intObj::operator!=(long long num) const
{
    return val != num;
}

// less than with float
bool Ghost_intObj::operator<(double num) const
{
    return val < num;
}

// less or equal with float
bool Ghost_intObj::operator<=(double num) const
{
    return val <= num;
}

// larger than with float
bool Ghost_intObj::operator>(double num) const
{
    return val > num;
}

// larger or equal with float
bool Ghost_intObj::operator>=(double num) const
{
    return val >= num;
}

// equal with float
bool Ghost_intObj::operator==(double num) const
{
    return val > num;
}

// not equal with float
bool Ghost_intObj::operator!=(double num) const
{
    return val != num;
}

// less than
bool Ghost_intObj::operator<(Ghost_intObj & rhs) const
{
    return val < rhs.val;
}

// less or equal
bool Ghost_intObj::operator<=(Ghost_intObj & rhs) const
{
    return val <= rhs.val;
}

// larger than
bool Ghost_intObj::operator>(Ghost_intObj & rhs) const
{
    return val > rhs.val;
}

// larger or equal
bool Ghost_intObj::operator>=(Ghost_intObj & rhs) const
{
    return val >= rhs.val;
}

// equal to
bool Ghost_intObj::operator==(Ghost_intObj & rhs) const
{
    return val == rhs.val;
}

// not equal to
bool Ghost_intObj::operator!=(Ghost_intObj & rhs) const
{
    return val != rhs.val;
}

// decide comparator from string
bool Ghost_intObj::compare(std::string op, Ghost_intObj & rhs) const
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
    
    std::cout << "Unknown operator From Ghost_intObj" << std::endl;
    return false;
}

// decide which comparator by string, with Ghost_floatObj
bool Ghost_intObj::compare(std::string op, Ghost_floatObj & rhs) const
{
    if(op == "<")
    {
        return val < rhs.getVal();
    }
    else if(op == ">")
    {
        return val > rhs.getVal();
    }
    else if(op == "<=")
    {
        return val <= rhs.getVal();
    }
    else if(op == ">=")
    {
        return val >= rhs.getVal();
    }
    else if(op == "==")
    {
        return val == rhs.getVal();
    }
    else if(op == "!=")
    {
        return val != rhs.getVal();
    }
    std::cout << "Unknown operator From Ghost_intObj" << std::endl;
    return false;
}

// get value
long long Ghost_intObj::getVal() const
{
    return val;
}

// get value in string
std::string Ghost_intObj::getVal_s() const
{
    return std::to_string(val);
}

// get type
std::string Ghost_intObj::getType() const
{
    return "Ghost Integer";
}

// operator bool() overload
Ghost_intObj::operator bool() const
{
    return val != 0;
}