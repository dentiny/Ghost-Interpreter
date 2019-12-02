#ifndef GHOST_LIST_OBJ__
#define GHOST_LIST_OBJ__

#include "BasicDataManager.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Ghost_intObj;
class Ghost_floatObj;
class Ghost_stringObj;

class Ghost_listObj : virtual public BasicDataManager
{
private:
    struct T
    {
        varType type;
        Ghost_intObj intObj;
        Ghost_floatObj floatObj;
        Ghost_stringObj stringObj;

        // operator == overload
        bool operator==(const T & rhs) const
        {
            return type == rhs.type 
                && intObj.getVal() == rhs.intObj.getVal() 
                && floatObj.getVal() == rhs.floatObj.getVal() 
                && stringObj.getVal() == rhs.stringObj.getVal();
        }

        // operator != overload
        bool operator!=(const T & rhs) const
        {
            return type != rhs.type
                || intObj.getVal() != rhs.intObj.getVal()
                || floatObj.getVal() != rhs.floatObj.getVal()
                || stringObj.getVal() != rhs.stringObj.getVal();
        }
    };
    std::vector<T> val;

    inline void pushClear(std::vector<std::string> & res, std::string & temp); // helper function for tokenize()
    inline int findMatched(std::string & cmd, char left, char right, int i); // helper function for tokenize()
    std::vector<std::string> tokenize(std::string & s); // helper function of constructor
    std::vector<T> getVal() const; // get value

public:
    Ghost_listObj() {} // default constructor
    Ghost_listObj(std::string s); // paramatric constructor
    Ghost_listObj(const Ghost_listObj & rhs) : val{rhs.val} {} // copy constructor
    Ghost_listObj(Ghost_listObj && rhs); // move constructor
    Ghost_listObj & operator=(const Ghost_listObj & rhs); // copy assignment
    Ghost_listObj & operator=(Ghost_listObj && rhs); // move assignment
    Ghost_listObj operator+(Ghost_listObj & rhs) const; // operator + overload
    Ghost_listObj & operator+=(Ghost_listObj & rhs); // operator += overload
    bool operator==(Ghost_listObj & rhs) const; // operator == overload
    bool operator!=(Ghost_listObj & rhs) const; // operator != overload
    bool compare(std::string op, Ghost_listObj & rhs) const; // decide comparator by string
    bool empty() const; // decide whether the list is empty
    void append(std::string s); // append a member into the list by string
    void append(Ghost_intObj & obj); // append a integer into the list
    void append(Ghost_floatObj & obj); // append a float into the list
    void append(Ghost_stringObj & obj); // append a string into the list
    std::string getVal_s() const; // get value in string
    std::string getType() const; // get type
    operator bool() const; // bool() overload
    // friend ostream
    friend std::ostream & operator<<(std::ostream & os, const Ghost_listObj & obj)
    {
        std::vector<T> temp = obj.getVal();
        for(auto temp_val : temp)
        {
            varType typeRes = temp_val.type;
            if(typeRes == varType::INT_VAR)
            {
                os << temp_val.intObj << " " << std::flush;
            }
            else if(typeRes == varType::FLOAT_VAR)
            {
                os << temp_val.floatObj << " " << std::flush;
            }
            else
            {
                os << temp_val.stringObj << " " << std::flush;
            }
        }
        return os;
    }
};

#endif 