#include "EventProvider.h"

#include "Debug.h"

EventProvider::EventProvider()
{

}

void EventProvider::sendEvent(EventType type, EntityId id)
{
  for(auto e : mList) {
    e->handleEvent(type, id);
  }
}

void EventProvider::addObserver(EventObserver * obs)
{
  dbg_assert(std::find(mList.begin(), mList.end(), obs) == mList.end());
  mList.push_back(obs);
}

void EventProvider::removeObserver(EventObserver * obs)
{
  ObserverList::iterator iter = std::find(mList.begin(), mList.end(), obs);
  dbg_assert(iter != mList.end());
  mList.erase(iter);
}
