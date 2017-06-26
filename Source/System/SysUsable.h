#ifndef SYSUSABLE_H
#define SYSUSABLE_H

#include "SystemBase.h"

#include <map>

#include "../Component/ComUsable.h"

class EntityFactory;

class SysUsable : public SystemBase
{
  public:
    SysUsable();

    void init(EntityFactory * factory);

    void clear();

    std::string dbgEntity(EntityId id) const;

    std::string dbgList() const;

    void executeTurn();

    void addComponent(EntityId id, const ComUsable & c);

    void removeEntity(EntityId id);

    bool equal(EntityId a, EntityId b) const;

    void useOnEntity(EntityId id, EntityId useOnId);

    uint16_t usages(EntityId id) const;

  private:
    EntityFactory * mEntityFactory;

    typedef std::map<EntityId, ComUsable> ComUsableList;
    ComUsableList mComUsableList;
};

#endif // SYSUSABLE_H
