#ifndef SYSTEMMGR_H
#define SYSTEMMGR_H

#include <cstdint>

#include "SysHealth.h"
#include "SysInventory.h"

class SystemMgr
{
  public:
    SystemMgr();

    void clearSystems();

    void apply(uint32_t deltaTime);

    SysHealth &         health();
    SysInventory &      inventory();

  private:
    SysHealth           mHealth;
    SysInventory        mInventory;
};

#endif // SYSTEMMGR_H
