#ifndef TEST_USABLE_H
#define TEST_USABLE_H

#include "test_global.h"

#include "System/SystemMgr.h"
#include "EntityFactory.h"

bool test_usable(SystemMgr & sysMgr, EntityFactory entityFactory) {
  const EntityId player = entityFactory.create(std::string("TestPlayer"));
  const EntityId poison = entityFactory.create(std::string("TestPoison"));

  CHECK(2 == sysMgr.usable().usages(poison));

  sysMgr.usable().useOnEntity(poison, player);
  CHECK(1 == sysMgr.usable().usages(poison));

  sysMgr.usable().useOnEntity(poison, player);
  CHECK(0 == sysMgr.usable().usages(poison));

  sysMgr.dbgEntity(poison);
  sysMgr.dbgEntity(player);

  return true;
}

#endif // TEST_USABLE_H
