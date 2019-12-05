#ifndef GHOST_STRING_OBJ__
#define GHOST_STRING_OBJ__

#include "Ghost_intObj.hpp"
#include <string>
#include <iostream>
#include <stdexcept>

class Ghost_intObj;

class Ghost_stringObj
{
private:
    std::string val;
    
public:
    Ghost_stringObj() : val{""} {} // constructor
    Ghost_stringObj(std::string _val); // parametric constructor
    Ghost_stringObj(const Ghost_stringObj & rhs) : val{rhs.val} {} // copy constructor
    Ghost_stringObj(Ghost_stringObj && rhs); // move constructor
    Ghost_stringObj & operator=(const Ghost_stringObj & rhs); // copy assignment
    Ghost_stringObj & operator=(Ghost_stringObj && rhs); // move assignment
    Ghost_stringObj operator+(std::string rhs) const; // operator + overload with string
    Ghost_stringObj & operator+=(std::string rhs); // operator += overload with string
    Ghost_stringObj operator+(Ghost_stringObj & rhs) const; // operator + overload
    Ghost_stringObj & operator+=(Ghost_stringObj & rhs); // operator += overload
    Ghost_stringObj operator*(long long num) const; // operator * overload with integer
    Ghost_stringObj & operator*=(long long num); // operator *= overload with integer
    Ghost_stringObj operator*(Ghost_intObj & rhs) const; // operator * overload
    Ghost_stringObj & operator*=(Ghost_intObj & rhs); // operator *= overload
    Ghost_stringObj operator*(Ghost_stringObj & rhs) const; // operator * overload with Ghost_stringObj
    Ghost_stringObj & operator*=(Ghost_stringObj & rhs); // operator *= overload with Ghost_stringObj
    bool operator<(std::string s) const; // less than with constant
    bool operator<=(std::string s) const; // less or equal with constant
    bool operator>(std::string s) const; // larger than with constant
    bool operator>=(std::string s) const; // larger or equal with constant
    bool operator==(std::string s) const; // equal with constant
    bool operator!=(std::string s) const; // not equal with constant
    bool operator<(Ghost_stringObj & rhs) const; // less than
    bool operator<=(Ghost_stringObj & rhs) const; // less or equal
    bool operator>(Ghost_stringObj & rhs) const; // larger than
    bool operator>=(Ghost_stringObj & rhs) const; // larger or equal
    bool operator==(Ghost_stringObj & rhs) const; // equal to
    bool operator!=(Ghost_stringObj & rhs) const; // not equal to
    bool compare(std::string s, Ghost_stringObj & rhs) const; // decide which comparator by string
    bool isEmpty() const; // whether the object is empty  
    size_t getSize() const; // get size
    std::string getVal() const; // get value
    std::string getVal_s() const; // get value in string
    std::string getType() const; // get type
    Ghost_stringObj toUpper() const; // transform to uppercase
    Ghost_stringObj toLower() const; // transform to lowercase
    void toUpper(); // transform to uppercase in-place
    void toLower(); // transform to lowercase in-place
    operator bool() const; // bool() overload
    // friend ostream
    friend std::ostream & operator<<(std::ostream & os, const Ghost_stringObj & obj)
    {
        os << obj.val << std::flush;
        return os;
    }
};

#endif