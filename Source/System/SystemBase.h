#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H

#include "SystemIF.h"

#include "../Macros.h"

class SystemBase : public SystemIF
{
  public:
    SystemBase(const std::string & name);

    const std::string & name() const;

  private:
    DISABLE_DFLT_CTOR(SystemBase)
    DISABLE_COPY(SystemBase)

    std::string       mName;
};

#endif // SYSTEMBASE_H
