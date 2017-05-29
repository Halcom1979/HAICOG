#ifndef SYSHEALTH_H
#define SYSHEALTH_H

#include "SystemBase.h"

#include "../Entity.h"
#include "../Component/ComHealth.h"
#include "../Component/ComHealing.h"
#include "../Component/ComDmgOverTime.h"

#include <map>
#include <list>

typedef std::map<EntityId, ComHealth> ComHealthList;
typedef std::list<std::pair<EntityId, ComHealing> > ComHealingList;
typedef std::list<std::pair<EntityId, ComDmgOverTime> > ComDmgOverTimeList;

class SysHealth : public SystemBase
{
  public:
    SysHealth();

    void clear();

    std::string dbgList() const;

    void apply(uint32_t deltaTime);

    void addComponent(EntityId id, const ComHealth & c);
    void addComponent(EntityId id, const ComHealing & c);
    void addComponent(EntityId id, const ComDmgOverTime & c);

    void health(EntityId id, uint32_t & current, uint32_t & total);

    void healing(EntityId id, uint32_t & inc);

    void dmgOverTime(EntityId id, uint32_t & inc);

  private:
    ComHealthList       mComHealthList;
    ComHealingList      mComHealingList;
    ComDmgOverTimeList  mComDmgOverTimeList;

    void applyDamageOverTime();
    void applyHealing();

    void modifyHealth(EntityId id, int16_t v);
};

#endif // SYSHEALTH_H
