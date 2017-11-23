#ifndef EVENTPROVIDER_H
#define EVENTPROVIDER_H

#include "EventObserver.h"

class EventProvider
{
  public:
    EventProvider();

    void sendEvent(EventType type, EntityId id);

    void addObserver(EventObserver * obs);

    void removeObserver(EventObserver * obs);

  private:
    typedef std::list<EventObserver*> ObserverList;
    ObserverList mList;
};

#endif // EVENTPROVIDER_H
