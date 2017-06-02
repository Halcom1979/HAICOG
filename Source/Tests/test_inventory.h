#ifndef TEST_INVENTORY_H
#define TEST_INVENTORY_H

#include "test_global.h"

bool test_inventory(SystemMgr & sysMgr, EntityFactory & factory) {
  const EntityId inv = factory.createEmptyEntity();

  ComInventory comInv;
  sysMgr.inventory().addComponent(inv, comInv);

  for(int i = 0; i < 7; ++i) {
    const EntityId item = factory.createEmptyEntity();
    sysMgr.inventory().addToInventory(inv, item);
  }

  sysMgr.dbgEntity(inv);

  return true;
}

#endif // TEST_INVENTORY_H
