#ifndef TEST_HEALTH_H
#define TEST_HEALTH_H

#include "System/SystemMgr.h"
#include "EntityFactory.h"

bool test_health(SystemMgr & sysMgr, EntityFactory & factory) {
  const EntityId player = factory.create(std::string("PlayerPoisoned"));

  print(sysMgr.health().dbgList());

  sysMgr.apply(5);

  print(sysMgr.health().dbgList());

  return true;
}

#endif // TEST_HEALTH_H
