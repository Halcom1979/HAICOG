#include "SysInventory.h"

#include "Debug.h"

#include "SystemMgr.h"

SysInventory::SysInventory(SystemMgr * systemMgr)
: mSystemMgr(systemMgr)
{
  dbg_assert(systemMgr != nullptr);
}

void SysInventory::clear()
{
  mInventories.clear();
}

std::string SysInventory::dbgEntity(EntityId id) const
{
  return fromEntityMapToString(id, mInventories);
}

std::string SysInventory::dbgList() const
{
  std::stringstream r;
  r << entityMapToString<InventoryList>("Inventories", mInventories);
  return r.str();
}

void SysInventory::executeTurn()
{

}

void SysInventory::removeEntity(EntityId id)
{
  mInventories.erase(id);
}

void SysInventory::addComponent(EntityId id, const ComInventory & c)
{
  UNUSED(c);
  mInventories[id] = InventoryEntries();
}

bool SysInventory::hasComponentInventory(EntityId id) const
{
  InventoryList::const_iterator iter = mInventories.find(id);
  return iter != mInventories.end();
}

void SysInventory::addToInventory(EntityId invId, EntityId e)
{
  InventoryList::iterator iter = mInventories.find(invId);
  dbg_assert(iter != mInventories.end());

  // if it is not stackable with itself,
  // it is not stackable with any other entity
  const bool selfStackable = areStackable(e, e);
  if(selfStackable) {
    InventoryEntries::iterator entIter = iter->second.begin();
    while(entIter != iter->second.end()) {
      const EntityId invEntity = (*entIter).id;
      const bool stackable = areStackable(e, invEntity);
      if(stackable) {
        (*entIter).amount++;

        mSystemMgr->removeEntity(e);
        return;
      }
    }
  }

  iter->second.push_back(InventoryEntry(e, 1));
}

InventoryEntries SysInventory::inventoryEntries(EntityId invId)
{
  InventoryList::iterator iter = mInventories.find(invId);
  dbg_assert(iter != mInventories.end());

  return iter->second;
}

bool SysInventory::areStackable(EntityId a, EntityId b) const
{
  // we cant stack anything that has a inventory
  if(hasComponentInventory(a) ||
     hasComponentInventory(b) )
  {
    return false;
  }

  // we cant stack anything that has a health component
  if(mSystemMgr->health().hasComponentHealth(a) ||
     mSystemMgr->health().hasComponentHealth(b) ||
     mSystemMgr->health().hasComponentHealthModifierOverTime(a) ||
     mSystemMgr->health().hasComponentHealthModifierOverTime(b) )
  {
    return false;
  }

  // must have same usable effect
  if(!mSystemMgr->usable().equal(a, b)) {
    return false;
  }

  return true;
}
