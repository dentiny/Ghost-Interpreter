#include "Ghost_floatObj.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

// parametric constructor
Ghost_floatObj::Ghost_floatObj(std::string s)
{
    val = stod(s);
}

// move constructor
Ghost_floatObj::Ghost_floatObj(Ghost_floatObj && rhs)
{
    std::swap(val, rhs.val);
}

// copy assignment
Ghost_floatObj & Ghost_floatObj::operator=(const Ghost_floatObj & rhs)
{
    if(this != &rhs)
    {
        val = rhs.val;
    }
    return *this;
}

// move assignment
Ghost_floatObj & Ghost_floatObj::operator=(Ghost_floatObj && rhs)
{
    if(this != &rhs)
    {
        std::swap(val, rhs.val);
    }
    return *this;
}

// get positive
Ghost_floatObj Ghost_floatObj::operator+() const
{
    Ghost_floatObj temp(*this);
    return temp;
}

// get negative
Ghost_floatObj Ghost_floatObj::operator-() const
{
    Ghost_floatObj temp(*this);
    temp.val *= -1;
    return temp;
}

// Ghost_floatObj::operator + overload with float
Ghost_floatObj Ghost_floatObj::operator+(double num) const
{
    Ghost_floatObj temp(*this);
    temp.val += num;
    return temp;
}

// Ghost_floatObj::operator += overload with float
Ghost_floatObj Ghost_floatObj::operator+=(double num)
{
    *this = *this + num;
    return *this;
}

// Ghost_floatObj::operator - overload with float
Ghost_floatObj Ghost_floatObj::operator-(double num) const
{
    Ghost_floatObj temp(*this);
    temp.val -= num;
    return temp;
}

// Ghost_floatObj::operator -= overload with float
Ghost_floatObj Ghost_floatObj::operator-=(double num)
{
    *this = *this - num;
    return *this;
}

// Ghost_floatObj::operator * overload with float
Ghost_floatObj Ghost_floatObj::operator*(double num) const
{
    Ghost_floatObj temp(*this);
    temp.val *= num;
    return temp;
}
    
// Ghost_floatObj::operator *= overload with float
Ghost_floatObj Ghost_floatObj::operator*=(double num)
{
    *this = *this * num;
    return *this;
}

// Ghost_floatObj::operator / overload with float
Ghost_floatObj Ghost_floatObj::operator/(double num) const
{
    Ghost_floatObj temp(*this);
    temp.val /= num;
    return temp;
}

// Ghost_floatObj::operator /= overload with float
Ghost_floatObj Ghost_floatObj::operator/=(double num)
{
    *this = *this / num;
    return *this;
}

// Ghost_floatObj::operator + overload with float
Ghost_floatObj Ghost_floatObj::operator+(long long  num) const
{
    Ghost_floatObj temp(*this);
    temp += num;
    return temp;
}

// Ghost_floatObj::operator += overload with float
Ghost_floatObj Ghost_floatObj::operator+=(long long num)
{
    *this = *this + num;
    return *this;
}

// Ghost_floatObj::operator - overload with float
Ghost_floatObj Ghost_floatObj::operator-(long long num) const
{
    Ghost_floatObj temp(*this);
    temp -= num;
    return temp;
}

// Ghost_floatObj::operator -= overload with float
Ghost_floatObj Ghost_floatObj::operator-=(long long num)
{
    *this = *this - num;
    return *this;
}

// Ghost_floatObj::operator * overload with float
Ghost_floatObj Ghost_floatObj::operator*(long long num) const
{
    Ghost_floatObj temp(*this);
    temp *= num;
    return temp;
}

// Ghost_floatObj::operator *= overload with float
Ghost_floatObj Ghost_floatObj::operator*=(long long num)
{
    *this = *this * num;
    return *this;
}

// Ghost_floatObj::operator / overload with float
Ghost_floatObj Ghost_floatObj::operator/(long long num) const
{
    Ghost_floatObj temp(*this);
    temp.val /= num;
    return temp;
}

// Ghost_floatObj::operator /= overload with float
Ghost_floatObj Ghost_floatObj::operator/=(long long num)
{
    *this = *this / num;
    return num;
}

// Ghost_floatObj::operator + overload
Ghost_floatObj Ghost_floatObj::operator+(Ghost_floatObj & rhs) const
{
    Ghost_floatObj temp(*this);
    temp.val += rhs.val;
    return temp;
}

// Ghost_floatObj::operator += overload
Ghost_floatObj & Ghost_floatObj::operator+=(Ghost_floatObj & rhs)
{
    *this = *this + rhs;
    return *this;
}

// Ghost_floatObj::operator - overload
Ghost_floatObj Ghost_floatObj::operator-(Ghost_floatObj & rhs) const
{
    Ghost_floatObj temp(*this);
    temp.val -= rhs.val;
    return temp;
}

// Ghost_floatObj::operator -= overload
Ghost_floatObj & Ghost_floatObj::operator-=(Ghost_floatObj & rhs)
{
    *this = *this - rhs;
    return *this;
}

// Ghost_floatObj::operator * overload
Ghost_floatObj Ghost_floatObj::operator*(Ghost_floatObj & rhs) const
{
    Ghost_floatObj temp(*this);
    temp.val *= rhs.val;
    return temp;
}

// Ghost_floatObj::operator *= overload
Ghost_floatObj & Ghost_floatObj::operator*=(Ghost_floatObj & rhs)
{
    *this = *this * rhs;
    return *this;
}

// Ghost_floatObj::operator / overload
Ghost_floatObj Ghost_floatObj::operator/(Ghost_floatObj & rhs) const
{
    Ghost_floatObj temp(*this);
    temp.val /= rhs.val;
    return temp;
}

// Ghost_floatObj::operator /= overload
Ghost_floatObj & Ghost_floatObj::operator/=(Ghost_floatObj & rhs)
{
    *this = *this / rhs;
    return *this;
}

// less than with integer
bool Ghost_floatObj::operator<(long long num) const
{
    return val < num;
}

// less or equal with integer
bool Ghost_floatObj::operator<=(long long num) const
{
    return val <= num;
} 

// larger than with integer
bool Ghost_floatObj::operator>(long long num) const
{
    return val > num;
}

// larger or equal with integer
bool Ghost_floatObj::operator>=(long long num) const
{
    return val >= num;
}

// equal with integer
bool Ghost_floatObj::operator==(long long num) const
{
    return val == num;
}

// not equal with integer
bool Ghost_floatObj::operator!=(long long num) const
{
    return val != num;
}

// less than with float
bool Ghost_floatObj::operator<(double num) const
{
    return  val < num;
}

// less or equal with float
bool Ghost_floatObj::operator<=(double num) const
{
    return val <= num;
}

// larger than with float
bool Ghost_floatObj::operator>(double num) const
{
    return val > num;
}

// larger or equal with float
bool Ghost_floatObj::operator>=(double num) const
{
    return val >= num;
}

// equal to with float
bool Ghost_floatObj::operator==(double num) const
{
    return val == num;
}

// not equal with float
bool Ghost_floatObj::operator!=(double num) const
{
    return val != num;
}

// less than
bool Ghost_floatObj::operator<(Ghost_floatObj & rhs) const
{
    return val < rhs.val;
}

// less or equal
bool Ghost_floatObj::operator<=(Ghost_floatObj & rhs) const
{
    return val <= rhs.val;
}

// larger than
bool Ghost_floatObj::operator>(Ghost_floatObj & rhs) const
{
    return val > rhs.val;
}

// larger or equal
bool Ghost_floatObj::operator>=(Ghost_floatObj & rhs) const
{
    return val >= rhs.val;
}

// equal to
bool Ghost_floatObj::operator==(Ghost_floatObj & rhs) const
{
    return val == rhs.val;
}

// not equal to
bool Ghost_floatObj::operator!=(Ghost_floatObj & rhs) const
{
    return val != rhs.val;
}

// decide which comparator by string
bool Ghost_floatObj::compare(std::string op, Ghost_floatObj & rhs) const
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
    std::cout << "Unknown operator From Ghost_floatObj" << std::endl;
    return false;
}

// decide which comparator by string, with Ghost_intObj
bool Ghost_floatObj::compare(std::string op, Ghost_intObj & rhs) const
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
    std::cout << "Unknown operator From Ghost_floatObj" << std::endl;
    return false;
}

// get value
double Ghost_floatObj::getVal() const
{
    return val;
}

// get value in string
std::string Ghost_floatObj::getVal_s() const
{
    return std::to_string(val);
}

// get type
std::string Ghost_floatObj::getType() const
{
    return "Ghost Float";
}

// bool() overload
Ghost_floatObj::operator bool() const
{
    return val != 0;
} 