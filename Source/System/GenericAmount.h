#ifndef GENERICAMOUNT_H
#define GENERICAMOUNT_H

#include "GenericSumUp.h"

template<typename T>
class GenericAmount: public GenericSumUp<T>
{
  public:
    GenericAmount(const char * name)
    : GenericSumUp(name)
    {}

    void clear() {
      GenericSumUp::clear();

      mCurrent.clear();
    }

    void add(EntityId id, const T & c) {
      GenericSumUp::add(id, c);

      std::map<EntityId, T>::iterator iter = mCurrent.find(id);
      if(iter == mCurrent.end()) {
        mCurrent[id] = c;
      } else {
        modify(id, c);
      }
    }

    bool hasEntity(EntityId id) {
      std::map<EntityId, T>::iterator iter = mCurrent.find(id);
      return (iter != mCurrent.end());
    }

    void remove(EntityId id, const T & c) {
      GenericSumUp::remove(id, c);
      modify(id, -c);
    }

    T current(EntityId id) const {
      std::map<EntityId, T>::const_iterator iter = mCurrent.find(id);
      dbg_assert(iter != mCurrent.end());

      return iter->second;
    }

    void kill(EntityId id) {
      std::map<EntityId, T>::iterator iter = mCurrent.find(id);
      if(iter != mCurrent.end()) {
        mCurrent.erase(iter);
        GenericSumUp::kill(id);
      }
    }

    void modify(EntityId id, T v) {
      std::map<EntityId, T>::iterator iter = mCurrent.find(id);
      dbg_assert(iter != mCurrent.end());

      iter->second += v;
    }

  private:
    DISABLE_COPY(GenericAmount)
    DISABLE_DFLT_CTOR(GenericAmount)

    std::map<EntityId, T> mCurrent;
};

#ifdef TEST_BUILD

#include "./Tests/test_global.h"

static void GenericAmmount_add() {
  GenericAmount<int32_t> ga("Test");
  ga.add(1, 5);
  assert(ga.total(1) == 5);
  assert(ga.current(1) == 5);
}

static void GenericAmmount_remove() {
  GenericAmount<int32_t> ga("Test");
  ga.add(1, 5);
  ga.add(1, 7);
  ga.add(1, 9);
  ga.add(2, 7);
  ga.add(2, 9);

  ga.remove(1, 7);
  assert(ga.total(1) == 14);
  assert(ga.current(1) == 14);
  assert(ga.total(2) == 16);
  assert(ga.current(2) == 16);

  ga.remove(1, 5);
  assert(ga.total(1) == 9);
  assert(ga.current(1) == 9);
  assert(ga.total(2) == 16);
  assert(ga.current(2) == 16);
}

static void GenericAmmount_remove_invalid_id() {
  GenericAmount<int32_t> ga("Test");
  ga.remove(1, 7);
}

static void GenericAmmount_remove_invalid_comp() {
  GenericAmount<int32_t> ga("Test");
  ga.add(1, 5);
  ga.remove(1, 7);
}

static void GenericAmmount_total_invalid_id() {
  GenericAmount<int32_t> ga("Test");
  ga.total(1);
}

static void GenericAmount_kill() {
  GenericAmount<int32_t> ga("Test");
  ga.add(1, 5);
  ga.kill(1);
  dbg_assert(!ga.hasEntity(1));

  GenericSumUp<int32_t> * gs = (GenericSumUp<int32_t>*) &ga;
  dbg_assert(!gs->hasEntity(1));
}

static void GenericAmount_kill_invalid() {
  GenericAmount<int32_t> ga("Test");
  ga.kill(1);
}

static void GenericAmount_clear() {
  GenericAmount<int32_t> ga("Test");
  ga.add(1, 1);
  ga.add(2, 2);
  ga.add(3, 3);
  ga.clear();
  dbg_assert(!ga.hasEntity(1));
  dbg_assert(!ga.hasEntity(2));
  dbg_assert(!ga.hasEntity(3));

  GenericSumUp<int32_t> * gs = (GenericSumUp<int32_t>*) &ga;
  dbg_assert(!gs->hasEntity(1));
  dbg_assert(!gs->hasEntity(2));
  dbg_assert(!gs->hasEntity(3));
}

static void unitTestGenericAmmount() {
  DO_UNIT_TEST(GenericAmmount_add);
  DO_UNIT_TEST(GenericAmmount_remove);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericAmmount_remove_invalid_id);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericAmmount_remove_invalid_comp);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericAmmount_total_invalid_id);
  DO_UNIT_TEST(GenericAmount_kill);
  DO_UNIT_TEST(GenericAmount_kill_invalid);
}
#endif

#endif // GENERICAMOUNT_H
