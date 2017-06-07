#include "SysUsable.h"

#include "../Debug.h"
#include "Helper.h"

#include "EntityFactory.h"

SysUsable::SysUsable()
: SystemBase("SysUsable")
, mEntityFactory(nullptr)
{

}

void SysUsable::init(EntityFactory * factory)
{
  dbg_assert(factory != nullptr);
  mEntityFactory = factory;
}

void SysUsable::clear()
{
  mComUsableList.clear();
}

std::string SysUsable::dbgEntity(EntityId id) const
{
  return fromEntityListToString(id, mComUsableList);
}

std::string SysUsable::dbgList() const
{
  return entityListToString("SysUsable", mComUsableList);
}

void SysUsable::executeTurn()
{

}

void SysUsable::addComponent(EntityId id, const ComUsable & c)
{
  mComUsableList[id] = c;
}

void SysUsable::removeEntity(EntityId id)
{
  removeFromEntityMap(id, mComUsableList);
}

void SysUsable::useOnEntity(EntityId id, EntityId useOnId)
{
  dbg_assert(mEntityFactory != nullptr);

  ComUsableList::iterator iter = mComUsableList.find(id);
  dbg_assert(iter != mComUsableList.end());

  mEntityFactory->addBlueprintToId(useOnId, iter->second.blueprint);

  if(iter->second.usages <= 1) {
    removeEntity(id);
  } else {
    iter->second.usages -= 1;
  }
}

uint16_t SysUsable::usages(EntityId id) const
{
  ComUsableList::const_iterator iter = mComUsableList.find(id);
  if(iter != mComUsableList.end()) {
    return iter->second.usages;
  }

  return 0;
}
