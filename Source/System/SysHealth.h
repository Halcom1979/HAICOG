#ifndef SYSHEALTH_H
#define SYSHEALTH_H

#include "Component/ComHealth.h"
#include "GenericAmount.h"
#include "EventProvider.h"

class SysHealth : public GenericAmount<ComHealth>, public EventProvider
{
  public:
    SysHealth();

    void remove(EntityId id, const ComHealth &c) {
      const ComHealth newCurrent = GenericAmount::remove(id, c);
      if(newCurrent == 0) {
        sendEvent(EventHealthZero, id);
      }
    }

    void modify(EntityId id, const ComHealth &c) {
      const bool newCurrent = GenericAmount::modify(id, c);
      if(newCurrent == 0) {
        sendEvent(EventHealthZero, id);
      }
    }

  private:
    DISABLE_COPY(SysHealth)
};

#ifdef TEST_BUILD

#include "./Tests/test_global.h"
#include "./Tests/TestEventObserver.h"

static void SysHealth_modify() {
  SysHealth  s;
  s.add(1, 10);
  s.modify(1, -4);
  dbg_assert(s.current(1) == 6);
}

static void SysHealth_remove_no_zero_event() {
  SysHealth  s;
  s.add(1, 10);
  s.add(1, 5);

  TestEventObserver e(&s, EventHealthZero, 1);
  s.remove(1, 5);
  dbg_assert(!e.received());
}

static void SysHealth_remove_zero_event() {
  SysHealth  s;
  s.add(1, 10);
  s.add(1, 5);
  s.modify(1, -14);

  TestEventObserver e(&s, EventHealthZero, 1);
  s.remove(1, 5);
  dbg_assert(e.received());
}

static void SysHealth_remove_of_last() {
  SysHealth  s;
  s.add(1, 10);

  TestEventObserver e(&s, EventHealthZero, 1);
  s.remove(1, 10);
  dbg_assert(!e.received());
}

static void SysHealth_modify_no_event() {
  SysHealth  s;
  s.add(1, 10);
  s.add(1, 5);

  TestEventObserver e(&s, EventHealthZero, 1);
  s.modify(1, 14);
  dbg_assert(!e.received());
}

static void SysHealth_modify_zero_event() {
  SysHealth  s;
  s.add(1, 10);

  TestEventObserver e(&s, EventHealthZero, 1);
  s.modify(1, -100);
  dbg_assert(e.received());
}

static void unitTestSysHealth() {
  DO_UNIT_TEST(SysHealth_modify);
  DO_UNIT_TEST(SysHealth_remove_no_zero_event);
  DO_UNIT_TEST(SysHealth_remove_zero_event);
  DO_UNIT_TEST(SysHealth_remove_of_last);
  DO_UNIT_TEST(SysHealth_modify_no_event);
  DO_UNIT_TEST(SysHealth_modify_zero_event);
}

#endif // TEST_BUILD

#endif // SYSHEALTH_H
