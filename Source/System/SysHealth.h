#ifndef SYSHEALTH_H
#define SYSHEALTH_H

#include "SystemBase.h"

#include "../Entity.h"
#include "../Component/ComHealth.h"
#include "../Component/ComHealthModifierOverTime.h"

#include <map>
#include <list>

class SysHealth : public SystemBase
{
  public:
    SysHealth();

    void clear();

    std::string dbgEntity(EntityId id) const;

    std::string dbgList() const;

    void executeTurn();

    void addComponent(EntityId id, const ComHealth & c);
    void addComponent(EntityId id, const ComHealthModifierOverTime & c);

    bool hasComponentHealth(EntityId id) const;
    bool hasComponentHealthModifierOverTime(EntityId id) const;

    void removeEntity(EntityId id);

    void health(EntityId id, uint32_t & current, uint32_t & total) const;

  private:
    typedef std::map<EntityId, ComHealth> ComHealthList;
    ComHealthList           mComHealthList;

    typedef std::list<std::pair<EntityId, ComHealthModifierOverTime> > ComModifierOverTimeList;
    ComModifierOverTimeList mComHealthModOverTimeList;

    void modifyHealth(EntityId id, int16_t v);

    void modifier(EntityId id, int32_t & inc);
};

#endif // SYSHEALTH_H
