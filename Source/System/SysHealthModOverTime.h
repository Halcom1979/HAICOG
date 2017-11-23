#ifndef SYSTEMHEALTHMODOVERTIME_H
#define SYSTEMHEALTHMODOVERTIME_H

#include "System/GenericCollection.h"

#include "Component/ComHealthModifierOverTime.h"

class SysHealth;

class SysHealthModOverTime : public GenericCollection<ComHealthModOverTime>
{
  public:
    SysHealthModOverTime(SysHealth * sysHealth);

    int32_t modifier(EntityId id) const;

    void executeTurn();

    void add(EntityId id, const ComHealthModOverTime &c);

  private:
    DISABLE_COPY(SysHealthModOverTime)
    DISABLE_DFLT_CTOR(SysHealthModOverTime)

    SysHealth * mSystemHealth;
};

#ifdef TEST_BUILD

#include "./Tests/test_global.h"

static void SysHealthModOverTime_add_with_zero_health() {
  SysHealthModOverTime s((SysHealth*)0xDEADC0DE);
  s.add(1, ComHealthModOverTime(0,1));
}

static void unitTestSysHealthModOverTime() {
  DO_UNIT_TEST_SHOULD_ASSERT(SysHealthModOverTime_add_with_zero_health);
}

#endif // TEST_BUILD

#endif // SYSTEMHEALTHMODOVERTIME_H
