#ifndef TESTINTUSABLE_H
#define TESTINTUSABLE_H

#ifdef TEST_BUILD

#include "System/SystemMgr.h"
#include "EntityFactory.h"

void testInt_SysUsable() {
  INIT_INTEGRATION_TEST

  const EntityId player = entityFactory.create(std::string("TestPlayer"));
  const EntityId poison = entityFactory.create(std::string("TestPoison"));

  dbg_assert(2 == sysMgr.usable().usages(poison));

  sysMgr.usable().useOnEntity(poison, player);
  dbg_assert(1 == sysMgr.usable().usages(poison));
  dbg_assert(sysMgr.healthModifierOverTime().hasEntity(player));

  sysMgr.usable().useOnEntity(poison, player);
  dbg_assert(!sysMgr.usable().hasEntity(poison));
}

#endif

#endif // TESTINTUSABLE_H
