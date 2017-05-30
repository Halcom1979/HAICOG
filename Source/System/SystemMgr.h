#ifndef SYSTEMMGR_H
#define SYSTEMMGR_H

#include <cstdint>

#include "SysHealth.h"
#include "SysInventory.h"

class SystemMgr
{
  public:
    SystemMgr();

    void dbgEntity(EntityId id) const;

    void clearSystems();

    void apply(uint32_t deltaTime);

    SysHealth &         health();
    SysInventory &      inventory();

  private:
    SysHealth             mHealth;
    SysInventory          mInventory;

    std::list<SystemIF*>  mSystems;
};

#endif // SYSTEMMGR_H
