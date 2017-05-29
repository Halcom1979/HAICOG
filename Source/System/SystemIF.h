#ifndef SYSTEMIF_H
#define SYSTEMIF_H

#include <cstdint>
#include <list>

#include "../Entity.h"

class SystemIF
{
  public:
    virtual void apply(uint32_t deltaTime) = 0;

    virtual std::string dbgList() const = 0;
};

typedef std::list<SystemIF*> SystemIFList;

#endif // SYSTEMIF_H
