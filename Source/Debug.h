#ifndef DEBUG_H
#define DEBUG_H

#ifdef _DEBUG
  #include <assert.h>
#endif

#include <iostream>

#include "Macros.h"
#include "Entity.h"

static void dbg_assert(bool x) {
  #ifdef _DEBUG
    assert(x);
  #endif
}

static void dbgEntity(EntityId player) {
  UNUSED(player);
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

#endif // DEBUG_H
