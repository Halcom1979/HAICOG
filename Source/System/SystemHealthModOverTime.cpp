#include "SystemHealthModOverTime.h"

SysHealthModOverTime::SysHealthModOverTime(SysHealth * sysHealth)
: GenericCollection("SystemHealthModifierOverTime")
, mSystemHealth(sysHealth)
{
  dbg_assert(mSystemHealth != nullptr);

}

int32_t SysHealthModOverTime::modifier(EntityId id) const {
  int32_t sum = 0;

  const std::list<ComHealthModOverTime> & list = components(id);

  for (const auto & kv : list) {
    sum += kv.health;
  }

  return sum;
}

void SysHealthModOverTime::executeTurn()
{
  applyAndRemoveIf([=](EntityId id, ComHealthModOverTime & c)
                    {
                      mSystemHealth->modify(id, c.health);
                      c.rounds -= 1;
                    },
                   [](const ComHealthModOverTime & c){return (c.rounds == 0);});
}
