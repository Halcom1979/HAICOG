#ifndef TESTINT_SYSTEMHEALTHMODOVERTIME_H
#define TESTINT_SYSTEMHEALTHMODOVERTIME_H

#ifdef TEST_BUILD

#include "System/SysHealth.h"
#include "System/SysHealthModOverTime.h"

void testInt_SystHealthModOverTime() {
  SysHealth sh;
  SysHealthModOverTime shm(&sh);

  sh.add(1, 10);
  sh.add(2, 20);

  shm.add(2, ComHealthModOverTime(-1, 2));
  shm.executeTurn();
  shm.executeTurn();
  dbg_assert(sh.current(1) == 10);
  dbg_assert(sh.current(2) == 18);

  shm.add(2, ComHealthModOverTime(1, 1));
  shm.executeTurn();
  dbg_assert(sh.current(1) == 10);
  dbg_assert(sh.current(2) == 19);

  shm.executeTurn();
  dbg_assert(sh.current(1) == 10);
  dbg_assert(sh.current(2) == 19);

  shm.add(1, ComHealthModOverTime(-6, 0));
  dbg_assert(sh.current(1) == 4);
  dbg_assert(sh.current(2) == 19);
}

#endif // TEST_BUILD

#endif // TESTINT_SYSTEMHEALTHMODOVERTIME_H
