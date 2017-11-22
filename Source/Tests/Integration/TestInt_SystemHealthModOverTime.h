#ifndef SYSTEMHEALTHMODOVERTIME_H
#define SYSTEMHEALTHMODOVERTIME_H

#ifdef TEST_BUILD
#include "System/SysHealth.h"
#include "System/SystemHealthModOverTime.h"

void testInt_SystHealthModOverTime() {
  SysHealth sh;
  SysHealthModOverTime shm(&sh);

  sh.add(1, 10);
  sh.add(2, 20);
  shm.add(1, ComHealthModOverTime(1, 1));
  shm.executeTurn();

  dbg_assert(sh.current(1) == 11);
  dbg_assert(sh.current(2) == 20);
  shm.executeTurn();
  dbg_assert(sh.current(1) == 11);
  dbg_assert(sh.current(2) == 20);

  shm.add(2, ComHealthModOverTime(-1, 2));
  shm.executeTurn();
  shm.executeTurn();
  dbg_assert(sh.current(1) == 11);
  dbg_assert(sh.current(2) == 18);

  shm.executeTurn();
  dbg_assert(sh.current(1) == 11);
  dbg_assert(sh.current(2) == 18);
}

#endif // TEST_BUILD

#endif // SYSTEMHEALTHMODOVERTIME_H
