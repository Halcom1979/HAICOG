#ifndef SYSHEALTH_H
#define SYSHEALTH_H

#include "SystemBase.h"

#include "../Entity.h"
#include "../Component/ComHealth.h"
#include "../Component/ComHealingOverTime.h"
#include "../Component/ComDmgOverTime.h"

#include <map>
#include <list>

typedef std::map<EntityId, ComHealth> ComHealthList;
typedef std::list<std::pair<EntityId, ComHealingOverTime> > ComHealingList;
typedef std::list<std::pair<EntityId, ComDmgOverTime> > ComDmgOverTimeList;

class SysHealth : public SystemBase
{
  public:
    SysHealth();

    void clear();

    std::string dbgEntity(EntityId id) const;

    std::string dbgList() const;

    void executeTurn();

    void addComponent(EntityId id, const ComHealth & c);
    void addComponent(EntityId id, const ComHealingOverTime & c);
    void addComponent(EntityId id, const ComDmgOverTime & c);

    void removeEntity(EntityId id);

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
