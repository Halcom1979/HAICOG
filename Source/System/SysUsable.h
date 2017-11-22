#ifndef SYSUSABLE_H
#define SYSUSABLE_H

#include "GenericSingleComponent.h"

#include <map>

#include "../Component/ComUsable.h"

class EntityFactory;

class SysUsable : public GenericSingleComponent<ComUsable>
{
  public:
    SysUsable();

    void init(EntityFactory * factory);

    bool equal(EntityId a, EntityId b) const;

    void useOnEntity(EntityId id, EntityId useOnId);

    uint16_t usages(EntityId id) const;

  private:
    EntityFactory * mEntityFactory;
};

#endif // SYSUSABLE_H
