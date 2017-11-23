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

EntityList SysInventory::entities() const
{
  EntityList res;
  for (const auto & kv : mInventories) {
    res.push_back(kv.first);
  }
  return res;
}

void SysInventory::executeTurn()
{

}

void SysInventory::kill(EntityId id)
{
  mInventories.erase(id);
}

void SysInventory::add(EntityId id, const ComInventory & c)
{
  UNUSED(c);
  dbg_assert(!hasEntity(id));
  mInventories[id] = InventoryEntries();
}

bool SysInventory::hasEntity(EntityId id) const
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

        mSystemMgr->kill(e);
        return;
      }
    }
  }

  iter->second.push_back(InventoryEntry(e, 1));
}

const InventoryEntries & SysInventory::entries(EntityId invId) const
{
  InventoryList::const_iterator iter = mInventories.find(invId);
  dbg_assert(iter != mInventories.end());

  return iter->second;
}

bool SysInventory::areStackable(EntityId a, EntityId b) const
{
  // we cant stack anything that has a inventory
  if(hasEntity(a) ||
     hasEntity(b) )
  {
    return false;
  }

  // we cant stack anything that has a health component
  if(mSystemMgr->health().hasEntity(a) ||
     mSystemMgr->health().hasEntity(b) )
  {
    return false;
  }

  // must have same usable effect
  //if(!mSystemMgr->usable().equal(a, b)) {
  //  return false;
  //}

  return true;
}
