#ifndef TEST_GLOBAL_H
#define TEST_GLOBAL_H

#include "System/SystemMgr.h"
#include "EntityFactory.h"

#define CHECK(res) check(res, __FILE__, __LINE__);

static void check(bool result, const char * file, const int line) {
  if(!result) {
    std::cout << "Test Failed:" << std::endl;
    std::cout << "  File: " << file << " Line: " << line << std::endl;
    exit(-1);
  }
}

#endif // TEST_GLOBAL_H
