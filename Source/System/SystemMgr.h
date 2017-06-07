#ifndef SYSTEMMGR_H
#define SYSTEMMGR_H

#include <cstdint>

#include "SysHealth.h"
#include "SysInventory.h"
#include "SysUsable.h"

class EntityFactory;

class SystemMgr
{
  public:
    SystemMgr();

    void init(EntityFactory * factory);

    void dbgEntity(EntityId id) const;

    void clearSystems();

    void executeTurn(uint32_t deltaTime);

    SysHealth &           health();
    SysInventory &        inventory();
    SysUsable &           usable();

  private:
    SysHealth             mHealth;
    SysInventory          mInventory;
    SysUsable             mUsable;

    std::list<SystemIF*>  mSystems;
};

#endif // SYSTEMMGR_H
