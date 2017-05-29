#ifndef TESTS_H
#define TESTS_H

#include "System/SystemMgr.h"
#include "EntityFactory.h"

void doTests(SystemMgr & sysMgr, EntityFactory & factory)
{
  sysMgr.clearSystems();

  const EntityId player = factory.create(std::string("PlayerPoisoned"));

  dbgEntity(player);

  print(sysMgr.health().dbgList());

  sysMgr.apply(5);

  print(sysMgr.health().dbgList());

  for(int i = 0; i < 7; ++i) {
    const EntityId poison = factory.create(std::string("Poison"));
    sysMgr.inventory().addToInventory(player, poison);
  }

  print(sysMgr.inventory().dbgList());
}

#endif // TESTS_H
