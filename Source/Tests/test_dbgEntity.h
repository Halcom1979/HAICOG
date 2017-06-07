#ifndef TEST_DBGENTITY_H
#define TEST_DBGENTITY_H

#include "System/SystemMgr.h"
#include "EntityFactory.h"

bool test_dbgEntity(SystemMgr & sysMgr, EntityFactory entityFactory) {
  const EntityId player = entityFactory.create(std::string("TestPlayer"));

  sysMgr.dbgEntity(player);

  entityFactory.addBlueprintToId(player, "TestPoison");

  sysMgr.dbgEntity(player);

  return true;
}

#endif // TEST_DBGENTITY_H
