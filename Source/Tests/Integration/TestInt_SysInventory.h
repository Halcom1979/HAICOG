#ifndef TESTINT_SYSINVENTORY_H
#define TESTINT_SYSINVENTORY_H

#ifdef TEST_BUILD

#include "System/SysInventory.h"

void testInt_SysInventory() {
  INIT_INTEGRATION_TEST;

  const EntityId inv = entityFactory.createEmptyEntity();

  ComInventory comInv;
  sysMgr.inventory().add(inv, comInv);

  for(int i = 0; i < 7; ++i) {
    const EntityId item = entityFactory.createEmptyEntity();
    sysMgr.inventory().addToInventory(inv, item);
  }
}

#endif // TEST_BUILD

#endif // TESTINT_SYSINVENTORY_H
