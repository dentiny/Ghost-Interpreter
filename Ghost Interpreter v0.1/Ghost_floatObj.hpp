#ifndef GHOST_FLOAT_OBJ__
#define GHOST_FLOAT_OBJ__
 
#include "Ghost_intObj.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

class Ghost_intObj;

class Ghost_floatObj
{
private:
    double val;    

public:
    Ghost_floatObj() : val{0.0} {} // constructor
    Ghost_floatObj(double _val) : val{_val} {} // parametric constructor
    Ghost_floatObj(std::string s); // parametric constructor
    Ghost_floatObj(const Ghost_floatObj & rhs) : val{rhs.val} {} // copy constructor
    Ghost_floatObj(Ghost_floatObj && rhs); // move constructor
    Ghost_floatObj & operator=(const Ghost_floatObj & rhs); // copy assignment
    Ghost_floatObj & operator=(Ghost_floatObj && rhs); // move assignment
    Ghost_floatObj operator+() const; // get positive
    Ghost_floatObj operator-() const; // get negative
    Ghost_floatObj operator+(double num) const; // operator + overload with float
    Ghost_floatObj operator+=(double num); // operator += overload with float
    Ghost_floatObj operator-(double num) const; // operator - overload with float
    Ghost_floatObj operator-=(double num); // operator -= overload with float
    Ghost_floatObj operator*(double num) const; // operator * overload with float
    Ghost_floatObj operator*=(double num); // operator *= overload with float
    Ghost_floatObj operator/(double num) const; // operator / overload with float
    Ghost_floatObj operator/=(double num); // operator /= overload with float
    Ghost_floatObj operator+(long long  num) const; // operator + overload with float
    Ghost_floatObj operator+=(long long num); // operator += overload with float
    Ghost_floatObj operator-(long long num) const; // operator - overload with float
    Ghost_floatObj operator-=(long long num); // operator -= overload with float
    Ghost_floatObj operator*(long long num) const; // operator * overload with float
    Ghost_floatObj operator*=(long long num); // operator *= overload with float
    Ghost_floatObj operator/(long long num) const; // operator / overload with float
    Ghost_floatObj operator/=(long long num); // operator /= overload with float
    Ghost_floatObj operator+(Ghost_floatObj & rhs) const; // operator + overload
    Ghost_floatObj & operator+=(Ghost_floatObj & rhs); // operator += overload
    Ghost_floatObj operator-(Ghost_floatObj & rhs) const; // operator - overload
    Ghost_floatObj & operator-=(Ghost_floatObj & rhs); // operator -= overload
    Ghost_floatObj operator*(Ghost_floatObj & rhs) const; // operator * overload
    Ghost_floatObj & operator*=(Ghost_floatObj & rhs); // operator *= overload
    Ghost_floatObj operator/(Ghost_floatObj & rhs) const; // operator / overload
    Ghost_floatObj & operator/=(Ghost_floatObj & rhs); // operator /= overload
    bool operator<(long long num) const; // less than with integer
    bool operator<=(long long num) const; // less or equal with integer
    bool operator>(long long num) const; // larger than with integer
    bool operator>=(long long num) const; // larger or equal with integer
    bool operator==(long long num) const; // equal with integer
    bool operator!=(long long num) const; // not equal with integer
    bool operator<(double num) const; // less than with float
    bool operator<=(double num) const; // less or equal with float
    bool operator>(double num) const; // larger than with float
    bool operator>=(double num) const; // larger or equal with float
    bool operator==(double num) const; // equal to with float
    bool operator!=(double num) const; // not equal with float
    bool operator<(Ghost_floatObj & rhs) const;; // less than
    bool operator<=(Ghost_floatObj & rhs) const;; // less or equal
    bool operator>(Ghost_floatObj & rhs) const; // larger than
    bool operator>=(Ghost_floatObj & rhs) const; // larger or equal
    bool operator==(Ghost_floatObj & rhs) const; // equal to
    bool operator!=(Ghost_floatObj & rhs) const; // not equal to 
    bool compare(std::string op, Ghost_floatObj & rhs) const; // decide which comparator by string
    bool compare(std::string op, Ghost_intObj & rhs) const; // decide which comparator by string, with Ghost_intObj
    double getVal() const; // get value
    std::string getVal_s() const; // get value in string
    std::string getType() const; // get type
    operator bool() const; // bool() overload
    // friend ostream
    friend std::ostream & operator<<(std::ostream & os, const Ghost_floatObj & obj)
    {
        os << obj.val << std::flush;
        return os;
    }
};

#endif