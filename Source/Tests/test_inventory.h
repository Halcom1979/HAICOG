#ifndef TEST_INVENTORY_H
#define TEST_INVENTORY_H

#include "test_global.h"

bool test_inventory(SystemMgr & sysMgr, EntityFactory entityFactory) {
  const EntityId inv = entityFactory.createEmptyEntity();

  ComInventory comInv;
  sysMgr.inventory().addComponent(inv, comInv);

  for(int i = 0; i < 7; ++i) {
    const EntityId item = entityFactory.createEmptyEntity();
    sysMgr.inventory().addToInventory(inv, item);
  }

  sysMgr.dbgEntity(inv);

  return true;
}

#endif // TEST_INVENTORY_H
