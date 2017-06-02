#include "SysInventory.h"

#include "Debug.h"

SysInventory::SysInventory()
{

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

}

void SysInventory::addComponent(EntityId id, const ComInventory & c)
{
  UNUSED(c);
  mInventories[id] = InventoryEntries();
}

void SysInventory::addToInventory(EntityId invId, EntityId e)
{
  InventoryList::iterator iter = mInventories.find(invId);
  dbg_assert(iter != mInventories.end());

  iter->second.push_back(InventoryEntry(e, 1));
}
