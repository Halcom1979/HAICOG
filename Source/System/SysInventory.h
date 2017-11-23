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
  uint32_t amount;
  EntityId id;

  InventoryEntry(EntityId i, uint32_t a)
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

    EntityList entities() const;

    void kill(EntityId id);

    void executeTurn();

    void add(EntityId id, const ComInventory & c);

    bool hasEntity(EntityId id) const;

    void addToInventory(EntityId invId, EntityId e);

    void removeFromInventory(EntityId invId, EntityId e);

    const InventoryEntries & entries(EntityId invId) const;

  private:
    DISABLE_COPY(SysInventory)
    DISABLE_DFLT_CTOR(SysInventory)

    SystemMgr * mSystemMgr;

    typedef std::map<EntityId, InventoryEntries> InventoryList;
    InventoryList mInventories;

    bool areStackable(EntityId a, EntityId b) const;
};

#endif // SYSINVENTORY_H
