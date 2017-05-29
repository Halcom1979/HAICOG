#ifndef SYSTEMMGR_H
#define SYSTEMMGR_H

#include <cstdint>

#include "SysHealth.h"

class SystemMgr
{
  public:
    SystemMgr();

    void apply(uint32_t deltaTime);

    SysHealth &         health();

  private:
    SysHealth           mHealth;
};

#endif // SYSTEMMGR_H
