#ifndef SYSTEMIF_H
#define SYSTEMIF_H

#include "Debug.h"
#include "Entity.h"

class SystemIF
{
  public:
    SystemIF(){}
    ~SystemIF(){}

    virtual EntityList entities() const = 0;

    virtual void clear() = 0;

    virtual void kill(EntityId id) = 0;

    virtual void executeTurn() {
      // not implemented
      dbg_assert(false);
    }
};

typedef std::list<SystemIF*> SystemIFList;

#endif // SYSTEMIF_H
