#ifndef SYSTEMMGR_H
#define SYSTEMMGR_H

#include <cstdint>

#include "System/SysHealth.h"
#include "System/SysHealthModOverTime.h"
#include "System/SysInventory.h"
#include "System/SysUsable.h"
#include "System/SysEquipmentSlotsBody.h"

class EntityFactory;

class SystemMgr
{
  public:
    SystemMgr();

    void init(EntityFactory * factory);

    void dbgEntity(EntityId id) const;

    void clearSystems();

    void executeTurn(uint32_t deltaTime);

    void kill(EntityId id);

    SysHealth &             health();
    SysHealthModOverTime &  healthModifierOverTime();
    SysInventory &          inventory();
    SysUsable &             usable();
    SysEquipmentSlotsBody & equipmentSlotsBody();

  private:
    SysHealth             mHealth;
    SysHealthModOverTime  mHealthMod;
    SysInventory          mInventory;
    SysUsable             mUsable;
    SysEquipmentSlotsBody mEquipmentSlotsBody;

    std::list<SystemIF*>  mSystems;
};

#endif // SYSTEMMGR_H
