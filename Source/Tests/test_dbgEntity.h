#ifndef TEST_DBGENTITY_H
#define TEST_DBGENTITY_H

#include "System/SystemMgr.h"
#include "EntityFactory.h"

bool test_dbgEntity(SystemMgr & sysMgr, EntityFactory & factory) {
  const EntityId player = factory.create(std::string("Player"));

  sysMgr.dbgEntity(player);

  factory.addBlueprintToId(player, "Poison");



  sysMgr.dbgEntity(player);

  return true;
}

#endif // TEST_DBGENTITY_H
