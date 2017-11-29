#ifndef TESTINT_SYSEQUIPMENTSLOTSBODY_H
#define TESTINT_SYSEQUIPMENTSLOTSBODY_H

#ifdef TEST_BUILD

#include "System/SystemMgr.h"

void testInt_SysEquipmentSlotsBody() {
  INIT_INTEGRATION_TEST;

  const EntityId player = entityFactory.create("testplayer");

  dbg_assert(sysMgr.equipmentSlotsBody().hasEntity(player));
  dbg_assert(sysMgr.equipmentSlotsBody().available(player) == BodyAll);
  dbg_assert(sysMgr.equipmentSlotsBody().used(player) == LeftHand);

}

#endif // TEST_BUILD

#endif // TESTINT_SYSEQUIPMENTSLOTSBODY_H
