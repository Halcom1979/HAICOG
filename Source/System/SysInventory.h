#ifndef SYSINVENTORY_H
#define SYSINVENTORY_H

#include "Debug.h"
#include "Macros.h"

#include "SystemBase.h"

#include "../Entity.h"
#include "../Component/ComInventory.h"

#include <map>
#include <list>

class SystemMgr;

struct InventoryEntry {
  uint64_t amount;
  EntityId id;

  InventoryEntry(EntityId i, uint64_t a)
  : id(i)
  , amount(a)
  {}
};

static std::string toString(InventoryEntry e) {
  std::ostringstream res;

  res << "InventoryEntry: {";
  res << "amount: " << std::to_string(e.amount) << ", " << toString(e.id);
  res << "}";

  return res.str();
}

typedef std::list<InventoryEntry> InventoryEntries;

static std::string toString(const InventoryEntries & e) {
  std::ostringstream res;
  res << "Inventory: " << listToString<InventoryEntries>(e);

  return res.str();
}

class SysInventory : public SystemIF
{
  public:
    SysInventory(SystemMgr * systemMgr);

    void clear();

    std::string dbgEntity(EntityId id) const;

    std::string dbgList() const;

    void executeTurn();

    void removeEntity(EntityId id);

    void addComponent(EntityId id, const ComInventory & c);

    bool hasComponentInventory(EntityId id) const;

    void addToInventory(EntityId invId, EntityId e);

    void removeFromInventory(EntityId invId, EntityId e);

    InventoryEntries inventoryEntries(EntityId invId);

  private:
    DISABLE_COPY(SysInventory)
    DISABLE_DFLT_CTOR(SysInventory)

    SystemMgr * mSystemMgr;

    typedef std::map<EntityId, InventoryEntries> InventoryList;
    InventoryList mInventories;

    bool areStackable(EntityId a, EntityId b) const;
};

#endif // SYSINVENTORY_H
