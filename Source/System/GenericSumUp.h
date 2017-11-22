#ifndef GENERICSUMUP_H
#define GENERICSUMUP_H

#include "GenericCollection.h"

#include <list>

template<typename T>
class GenericSumUp: public GenericCollection<T>
{
  public:
    GenericSumUp(const char * name)
    : GenericCollection<T>(name)
    {}

    T total(EntityId id) const {
      T sum = 0;

      const std::list<T> & list = components(id);

      std::list<T>::const_iterator iter = list.begin();
      while(iter != list.end()) {
        sum += *iter;
        ++iter;
      }

      return sum;
    }
};

#ifdef TEST_BUILD

#include "./Tests/test_global.h"

static void GenericSumUp_add() {
  GenericSumUp<int32_t> ga("Test");
  ga.add(1, 5);
  dbg_assert(ga.total(1) == 5);
}

static void GenericSumUp_remove() {
  GenericSumUp<int32_t> ga("Test");
  ga.add(1, 5);
  ga.add(1, 7);
  ga.add(1, 9);
  ga.add(2, 7);
  ga.add(2, 9);

  ga.remove(1, 7);
  dbg_assert(ga.total(1) == 14);
  dbg_assert(ga.total(2) == 16);

  ga.remove(1, 5);
  dbg_assert(ga.total(1) == 9);
  dbg_assert(ga.total(2) == 16);
}

static void GenericSumUp_remove_invalid_id() {
  GenericSumUp<int32_t> ga("Test");
  ga.remove(1, 7);
}

static void GenericSumUp_remove_invalid_comp() {
  GenericSumUp<int32_t> ga("Test");
  ga.add(1, 5);
  ga.remove(1, 7);
}

static void GenericSumUp_total_invalid_id() {
  GenericSumUp<int32_t> ga("Test");
  ga.total(1);
}

static void GenericSumUp_kill() {
  GenericSumUp<int32_t> ga("Test");
  ga.add(1, 5);
  ga.kill(1);
  dbg_assert(!ga.hasEntity(1));
}

static void GenericSumUp_kill_invalid() {
  GenericSumUp<int32_t> ga("Test");
  ga.kill(1);
}

static void GenericSumUp_hasEntity() {
  GenericSumUp<int32_t> ga("Test");
  dbg_assert(!ga.hasEntity(1));

  ga.add(1, 5);
  dbg_assert(ga.hasEntity(1));
}

static void GenericSumUp_clear() {
  GenericSumUp<int32_t> ga("Test");
  ga.add(1, 1);
  ga.add(2, 2);
  ga.add(3, 3);
  ga.clear();
  dbg_assert(!ga.hasEntity(1));
  dbg_assert(!ga.hasEntity(2));
  dbg_assert(!ga.hasEntity(3));
}

static void GenericSumUp_entities() {
  GenericSumUp<int32_t> ga("Test");
  ga.add(1, 1);
  ga.add(2, 2);
  ga.add(3, 3);
  EntityList list = ga.entities();
  dbg_assert(list.size() == 3);

  dbg_assert(std::find(list.begin(), list.end(), 1) != list.end());
  dbg_assert(std::find(list.begin(), list.end(), 2) != list.end());
  dbg_assert(std::find(list.begin(), list.end(), 3) != list.end());
}

static void unitTestGenericSumUp() {
  DO_UNIT_TEST(GenericSumUp_add);
  DO_UNIT_TEST(GenericSumUp_remove);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericSumUp_remove_invalid_id);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericSumUp_remove_invalid_comp);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericSumUp_total_invalid_id);
  DO_UNIT_TEST(GenericSumUp_kill);
  DO_UNIT_TEST(GenericSumUp_kill_invalid);
  DO_UNIT_TEST(GenericSumUp_hasEntity);
  DO_UNIT_TEST(GenericSumUp_clear);
  DO_UNIT_TEST(GenericSumUp_entities);
}
#endif

#endif // GENERICSUMUP_H
