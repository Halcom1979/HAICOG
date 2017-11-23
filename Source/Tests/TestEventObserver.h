#ifndef TESTEVENTOBSERVER_H
#define TESTEVENTOBSERVER_H

#include "Macros.h"
#include "EventProvider.h"

class TestEventObserver: public EventObserver
{
  public:
    TestEventObserver(EventProvider * prov, EventType type, EntityId id)
    : mEventProvider(prov)
    , mEventType(type)
    , mId(id)
    , mReceived(false)
    {
      dbg_assert(prov != nullptr);
      mEventProvider->addObserver(this);
    }

    ~TestEventObserver() { mEventProvider->removeObserver(this); }

    void handleEvent(EventType t, EntityId id) {
      if(mEventType == t && mId == id) {
        mReceived = true;
      }
    }

    bool received() { return mReceived; }
    void clear() { mReceived = false; }

  private:
    DISABLE_DFLT_CTOR(TestEventObserver)

    EventProvider * mEventProvider;
    EventType       mEventType;
    EntityId        mId;
    bool            mReceived;
};

#endif // TESTEVENTOBSERVER_H
