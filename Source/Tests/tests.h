#ifndef TESTS_H
#define TESTS_H

#include "Debug.h"

#include "System/SystemMgr.h"
#include "EntityFactory.h"

#include "test_health.h"
#include "test_inventory.h"
#include "test_dbgEntity.h"
#include "test_usable.h"

#define DO_TEST(method) \
{\
  sysMgr.clearSystems();\
  print(#method);\
  const bool result = method(sysMgr, factory);\
  if(!result) {\
    print("FAILED!!!");\
    exit(-1);\
  }\
}

void doTests(SystemMgr & sysMgr, EntityFactory & factory)
{
  //DO_TEST(test_health);
  //DO_TEST(test_inventory);
  //DO_TEST(test_dbgEntity);
  DO_TEST(test_usable);

  print("Test finished!!!");
}

#endif // TESTS_H
