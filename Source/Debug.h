#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#include "Macros.h"
#include "Entity.h"

#ifdef _DEBUG
  #ifdef TEST_BUILD
    #include <stdexcept>
    #define dbg_assert(x)\
    if(!(x)) {\
      throw std::runtime_error(__FILE__ ":" LINE_STRING);\
    }
  #else
    #include <assert.h>
    #define dbg_assert(x) assert(x)
  #endif
#else
  #define dbg_assert(x)
#endif

static void print(const char * msg) {
  std::cout << msg << std::endl;
}

static void print(const std::string & msg) {
  std::cout << msg.c_str() << std::endl;
}

template<typename T>
static std::string listToString(const T & list) {
  if(list.size() == 0) {
    return std::string("{}");
  }

  std::stringstream res;
  res << "{" << std::endl;
  for(auto e : list) {
    res << "  " << toString(e) << std::endl;
  }
  res << "}" << std::endl;

  return res.str();
}

template<typename T>
static std::string entityListToString(const char * name, const T & list) {
  if(list.size() == 0) {
    return std::string();
  }

  std::stringstream res;

  res << name;
  res << " (" << std::to_string(list.size()) << "):" << std::endl;

  for(auto e : list) {
    res << "  ";
    res << toString(e.first);
    res << " - ";
    res << toString(e.second);
    res << std::endl;
  }

  return res.str();
}

template<typename T>
static std::string fromEntityListToString(EntityId id, const T & list) {
  std::stringstream res;

  bool firstOne = true;
  for(auto e : list) {
    if(e.first == id) {
      if(firstOne) {
        firstOne = false;
        res << toString(e.second);
      } else {
        res << std::endl << toString(e.second);
      }
    }
  }

  return res.str();
}

template<typename T>
static std::string entityMapToString(const char * name, const T & map)
{
  if(map.size() == 0) {
    return std::string();
  }

  std::stringstream res;

  res << name;
  res << " (" << std::to_string(map.size()) << "):" << std::endl;

  for(auto e : map) {
    res << "  ";
    res << toString(e.first);
    res << " - ";
    res << toString(e.second);
    res << std::endl;
  }

  return res.str();
}

template<typename T>
static std::string fromEntityMapToString(EntityId id, const T & map) {
  for(auto e : map) {
    if(e.first == id) {
      return toString(e.second);
    }
  }

  return std::string();
}

#endif // DEBUG_H
