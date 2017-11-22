#ifndef SystemHealthModOverTime_H
#define SystemHealthModOverTime_H

#include "SysHealth.h"
#include "System/GenericCollection.h"

#include "Component/ComHealthModifierOverTime.h"

class SysHealthModOverTime :
    public GenericCollection<ComHealthModOverTime>
{
  public:
    SysHealthModOverTime(SysHealth * sysHealth);

    int32_t modifier(EntityId id) const;

    void executeTurn();

  private:
    DISABLE_DFLT_CTOR(SysHealthModOverTime)

    SysHealth * mSystemHealth;
};

#endif // SystemHealthModOverTime_H
