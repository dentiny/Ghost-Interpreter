#ifndef FUNCTOR_HPP__
#define FUNCTOR_HPP__

#include "DataManager.hpp"
#include "Ghost_intObj.hpp"
#include "Ghost_floatObj.hpp"
#include "Ghost_stringObj.hpp"
#include "Ghost_listObj.hpp"
#include <string>
#include <unordered_set>

struct Functor : virtual public DataManager
{
    // self-defined local function
    std::unordered_set<std::string> local_func;

    // self-defined global function
    std::unordered_set<std::string> func;
};

#endif