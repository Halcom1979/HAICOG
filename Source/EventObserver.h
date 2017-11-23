#ifndef EVENTOBSERVER_H
#define EVENTOBSERVER_H

#include "Entity.h"

enum EventType {
  EventHealthZero = 1
};

class EventObserver
{
  public:
    virtual void handleEvent(EventType t, EntityId id) = 0;
};

#endif // EVENTOBSERVER_H
