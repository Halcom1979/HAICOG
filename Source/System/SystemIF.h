#ifndef SYSTEMIF_H
#define SYSTEMIF_H

#include <cstdint>
#include <list>

#include "../Entity.h"

class SystemIF
{
  public:
    virtual void clear() = 0;

    virtual std::string dbgEntity(EntityId id) const = 0;

    virtual std::string dbgList() const = 0;

    virtual void executeTurn() = 0;

    virtual void removeEntity(EntityId id) = 0;
};

typedef std::list<SystemIF*> SystemIFList;

#endif // SYSTEMIF_H
