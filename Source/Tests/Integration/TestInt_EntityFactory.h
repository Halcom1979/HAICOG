#ifndef TESTINT_ENTITYFACTORY_H
#define TESTINT_ENTITYFACTORY_H

#ifdef TEST_BUILD

#include "System/SystemMgr.h"
#include "EntityFactory.h"

void testInt_EntityFactory() {
  INIT_INTEGRATION_TEST;

  const EntityId player = entityFactory.create("testplayer");
  dbg_assert(sysMgr.health().current(player) == 20);
  dbg_assert(sysMgr.health().total(player) == 30);

  const EntityId playerPoisened = entityFactory.create("testplayerpoisoned");
  dbg_assert(sysMgr.health().current(playerPoisened) == 20);
  dbg_assert(sysMgr.health().total(playerPoisened) == 30);
  dbg_assert(sysMgr.healthModifierOverTime().modifier(playerPoisened) == -2);

  const EntityId poison = entityFactory.create("testpoison");
  dbg_assert(sysMgr.usable().usages(poison) == 2);

  const EntityId poisonEffect = entityFactory.create("testpoisoneffect");
  dbg_assert(sysMgr.healthModifierOverTime().modifier(poisonEffect) == -2);
}

#endif // TEST_BUILD

#endif // TESTINT_ENTITYFACTORY_H
