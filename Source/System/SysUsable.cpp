#include "SysUsable.h"

#include "../Debug.h"
#include "Helper.h"

#include "EntityFactory.h"

SysUsable::SysUsable()
: GenericSingleComponent("SysUsable")
, mEntityFactory(nullptr)
{

}

void SysUsable::init(EntityFactory * factory)
{
  dbg_assert(factory != nullptr);
  mEntityFactory = factory;
}

bool SysUsable::equal(EntityId a, EntityId b) const
{
  const bool found_a = hasEntity(a);
  if(!found_a) {
    return false;
  }

  const bool found_b = hasEntity(b);
  if(!found_b) {
    return false;
  }

  const ComUsable & comp_a = component(a);
  const ComUsable & comp_b = component(b);
  return comp_a == comp_b;
}

void SysUsable::useOnEntity(EntityId id, EntityId useOnId)
{
  dbg_assert(mEntityFactory != nullptr);

  ComUsable & comp = component(id);

  mEntityFactory->addBlueprintToId(useOnId, comp.blueprint);

  if(comp.usages <= 1) {
    kill(id);
  } else {
    comp.usages -= 1;
  }
}

uint16_t SysUsable::usages(EntityId id) const
{
  dbg_assert(hasEntity(id));
  return component(id).usages;
}
