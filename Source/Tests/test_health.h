#ifndef TEST_HEALTH_H
#define TEST_HEALTH_H

#include "test_global.h"

bool test_health(SystemMgr & sysMgr, EntityFactory & factory) {
  const EntityId entity = factory.createEmptyEntity();
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

  // TEST ComDmgOverTime
  sysMgr.health().addComponent(entity, ComDmgOverTime(1,0));
  sysMgr.health().health(entity, current, total);
  CHECK(current == 7);
  CHECK(total == 10);

  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 7);
  CHECK(total == 10);

  sysMgr.health().addComponent(entity, ComDmgOverTime(1,1));
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

  sysMgr.health().addComponent(entity, ComDmgOverTime(1,3));
  sysMgr.executeTurn(5);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 3);
  CHECK(total == 10);

  // TEST ComHealingOverTime
  sysMgr.health().addComponent(entity, ComHealingOverTime(1,0));
  sysMgr.health().health(entity, current, total);
  CHECK(current == 4);
  CHECK(total == 10);

  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 4);
  CHECK(total == 10);


  sysMgr.health().addComponent(entity, ComHealingOverTime(1,1));
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

  sysMgr.health().addComponent(entity, ComHealingOverTime(1,3));
  sysMgr.executeTurn(5);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 8);
  CHECK(total == 10);

  // TEST first heal then dmg
  sysMgr.health().addComponent(entity, ComHealingOverTime(10,1));
  sysMgr.health().addComponent(entity, ComDmgOverTime(10,1));
  sysMgr.executeTurn(1);
  sysMgr.health().health(entity, current, total);
  CHECK(current == 8);
  CHECK(total == 10);

  return true;
}

#endif // TEST_HEALTH_H
