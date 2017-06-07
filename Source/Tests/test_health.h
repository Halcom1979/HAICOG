#ifndef TEST_HEALTH_H
#define TEST_HEALTH_H

#include "test_global.h"

bool test_health(SystemMgr & sysMgr, EntityFactory entityFactory) {
  const EntityId entity = entityFactory.createEmptyEntity();
  uint32_t current, total;

  // TEST ComHealth
  sysMgr.health().addComponent(entity, ComHealth(8,10));
  sysMgr.health().health(entity, current, total);
  CHECK(current == 8);
  CHECK(total == 10);

  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 8);
  CHECK(total == 10);

  // TEST negativ modifier
  sysMgr.health().addComponent(entity, ComHealthModifierOverTime(-1,0));
  sysMgr.health().health(entity, current, total);
  CHECK(current == 7);
  CHECK(total == 10);

  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 7);
  CHECK(total == 10);

  sysMgr.health().addComponent(entity, ComHealthModifierOverTime(-1,1));
  sysMgr.health().health(entity, current, total);
  CHECK(current == 7);
  CHECK(total == 10);

  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 6);
  CHECK(total == 10);

  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 6);
  CHECK(total == 10);

  sysMgr.health().addComponent(entity, ComHealthModifierOverTime(-1,3));
  sysMgr.executeTurn(5);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 3);
  CHECK(total == 10);

  // TEST positive modifier
  sysMgr.health().addComponent(entity, ComHealthModifierOverTime(1,0));
  sysMgr.health().health(entity, current, total);
  CHECK(current == 4);
  CHECK(total == 10);

  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 4);
  CHECK(total == 10);

  sysMgr.health().addComponent(entity, ComHealthModifierOverTime(1,1));
  sysMgr.health().health(entity, current, total);
  CHECK(current == 4);
  CHECK(total == 10);

  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 5);
  CHECK(total == 10);

  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 5);
  CHECK(total == 10);

  sysMgr.health().addComponent(entity, ComHealthModifierOverTime(1,3));
  sysMgr.executeTurn(5);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 8);
  CHECK(total == 10);

  sysMgr.health().addComponent(entity, ComHealthModifierOverTime(10,1));
  sysMgr.health().addComponent(entity, ComHealthModifierOverTime(-10,1));
  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 8);
  CHECK(total == 10);

  sysMgr.health().addComponent(entity, ComHealthModifierOverTime(100,1));
  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 10);
  CHECK(total == 10);

  sysMgr.health().addComponent(entity, ComHealthModifierOverTime(-100,1));
  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 0);
  CHECK(total == 0);

  return true;
}

#endif // TEST_HEALTH_H
