#ifndef GHOST_INT_OBJ__
#define GHOST_INT_OBJ__

#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

class Ghost_floatObj;
class Ghost_stringObj;

class Ghost_intObj
{
private:
    long long val;

public:
    Ghost_intObj() : val{0} {} // constructor
    Ghost_intObj(long long _val) : val{_val} {} // parametric constructor
    Ghost_intObj(std::string s); // parametric constructor
    Ghost_intObj(const Ghost_intObj & rhs) : val{rhs.val} {} // copy constructor
    Ghost_intObj(Ghost_intObj && rhs); // move constructor
    Ghost_intObj & operator=(const Ghost_intObj & rhs); // copy assignment
    Ghost_intObj & operator=(Ghost_intObj && rhs); // move assignment
    Ghost_intObj operator+() const; // get positive
    Ghost_intObj operator-() const; // get negative
    Ghost_intObj operator++(); // prefix increment
    Ghost_intObj operator--(); // prefix decrement
    Ghost_intObj operator++(int i); // postfix increment
    Ghost_intObj operator--(int i); // postfix decrement
    Ghost_intObj operator+(long long num) const; // operator + overload with integer
    Ghost_intObj operator+=(long long num); // operator += overload with integer
    Ghost_intObj operator-(long long num) const; // operator - overload with integer
    Ghost_intObj operator-=(long long num); // operator -= overload with integer
    Ghost_intObj operator*(long long num) const; // operator * overload with integer
    Ghost_intObj operator*=(long long num); // operator *= overload with integer
    Ghost_intObj operator/(long long num) const; // operator / overload with integer
    Ghost_intObj operator/=(long long num); // operator /= overload with integer
    Ghost_floatObj operator+(double num) const; // operator + overload with float
    Ghost_floatObj operator-(double num) const; // operator - overload with float
    Ghost_floatObj operator*(double num) const; // operator * overload with float
    Ghost_floatObj operator/(double num) const; // operator / overload with float
    Ghost_intObj operator+(Ghost_intObj & rhs) const; // operator + overload
    Ghost_intObj & operator+=(Ghost_intObj & rhs); // operator += overload
    Ghost_intObj operator-(Ghost_intObj & rhs) const; // operator - overload
    Ghost_intObj & operator-=(Ghost_intObj & rhs); // operator -= overload
    Ghost_intObj operator*(Ghost_intObj & rhs) const; // operator * overload
    Ghost_intObj & operator*=(Ghost_intObj & rhs); // operator *= overload
    Ghost_stringObj operator*(std::string & rhs) const; // operator * overload with string
    Ghost_stringObj operator*(Ghost_stringObj & rhs) const; // operator * overload with Ghost_stringObj
    Ghost_intObj operator/(Ghost_intObj & rhs) const; // operator / overload
    Ghost_intObj & operator/=(Ghost_intObj & rhs); // operator /= overload
    bool operator<(long long num) const; // less than with integer
    bool operator<=(long long num) const; // less or equal with integer
    bool operator>(long long num) const; // larger with integer
    bool operator>=(long long num) const; // larger or equal with integer
    bool operator==(long long num) const; // equal to integer
    bool operator!=(long long num) const; // not equal to integer
    bool operator<(double num) const; // less than with float
    bool operator<=(double num) const; // less or equal with float
    bool operator>(double num) const; // larger than with float
    bool operator>=(double num) const; // larger or equal with float
    bool operator==(double num) const; // equal with float
    bool operator!=(double num) const; // not equal with float
    bool operator<(Ghost_intObj & rhs) const; // less than
    bool operator<=(Ghost_intObj & rhs) const; // less or equal
    bool operator>(Ghost_intObj & rhs) const; // larger than
    bool operator>=(Ghost_intObj & rhs) const; // larger or equal
    bool operator==(Ghost_intObj & rhs) const; // equal to
    bool operator!=(Ghost_intObj & rhs) const; // not equal to  
    bool compare(std::string op, Ghost_intObj & rhs) const; // decide comparator from string
    bool compare(std::string op, Ghost_floatObj & rhs) const; // decide comparator from string, with Ghost_floatObj
    long long getVal() const; // get value
    std::string getVal_s() const; // get value in string
    std::string getType() const; // get type
    operator bool() const; // bool() overload
    // friend ostream
    friend std::ostream & operator<<(std::ostream & os, const Ghost_intObj & obj)
    {
        os << obj.val << std::flush;
        return os;
    }
};

#endif