#ifndef SYSHEALTH_H
#define SYSHEALTH_H

#include "Component/ComHealth.h"
#include "GenericAmount.h"

class SysHealth : public GenericAmount<ComHealth>
{
  public:
    SysHealth();

  private:
    DISABLE_COPY(SysHealth)
};

#endif // SYSHEALTH_H
