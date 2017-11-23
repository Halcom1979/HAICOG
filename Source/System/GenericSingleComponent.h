#ifndef GENERICSINGLECOMPONENT_H
#define GENERICSINGLECOMPONENT_H

#include "SystemBase.h"

#include <map>
#include <list>
#include <functional>

template<typename T>
class GenericSingleComponent : public SystemBase
{
  public:
    GenericSingleComponent(const char * name)
    : SystemBase(name)
    {}

    void clear() {
      mComponents.clear();
    }

    void add(EntityId id, const T & c) {
      dbg_assert(!hasEntity(id));
      mComponents[id] = c;
    }

    bool hasEntity(EntityId id) const {
      return (mComponents.find(id) != mComponents.end());
    }

    EntityList entities() const {
      EntityList res;
      for (const auto & entry : mComponents) {
        res.push_back(entry.first);
      }
      return res;
    }

    void kill(EntityId id) {
      EntityMap::iterator iter = mComponents.find(id);
      if(iter != mComponents.end()) {
        mComponents.erase(iter);
      }
    }

    const T & component(EntityId id) const{
      EntityMap::const_iterator iter = mComponents.find(id);
      dbg_assert(iter != mComponents.end());
      return iter->second;
    }

  protected:
    T & component(EntityId id) {
      EntityMap::iterator iter = mComponents.find(id);
      dbg_assert(iter != mComponents.end());
      return iter->second;
    }

  private:
    DISABLE_DFLT_CTOR(GenericSingleComponent)

    typedef std::map<EntityId, T> EntityMap;
    EntityMap mComponents;
};

#ifdef TEST_BUILD

#include "./Tests/test_global.h"

static void GenericSingleComponent_add() {
  GenericSingleComponent<int32_t> ga("Test");
  ga.add(1, 5);
  dbg_assert(ga.hasEntity(1));
}

static void GenericSingleComponent_kill() {
  GenericSingleComponent<int32_t> ga("Test");
  ga.add(1, 7);
  ga.add(2, 9);

  ga.kill(2);
  dbg_assert(ga.hasEntity(1));
  dbg_assert(!ga.hasEntity(2));
}

static void GenericSingleComponent_kill_invalid() {
  GenericSingleComponent<int32_t> ga("Test");
  ga.kill(1);
}

static void GenericSingleComponent_hasEntity() {
  GenericSingleComponent<int32_t> ga("Test");
  dbg_assert(!ga.hasEntity(1));

  ga.add(1, 5);
  dbg_assert(ga.hasEntity(1));
}

static void GenericSingleComponent_clear() {
  GenericSingleComponent<int32_t> ga("Test");
  ga.add(1, 1);
  ga.add(2, 2);
  ga.add(3, 3);
  ga.clear();
  dbg_assert(!ga.hasEntity(1));
  dbg_assert(!ga.hasEntity(2));
  dbg_assert(!ga.hasEntity(3));
}

static void GenericSingleComponent_entities() {
  GenericSingleComponent<int32_t> ga("Test");
  ga.add(1, 1);
  ga.add(2, 2);
  ga.add(3, 3);
  EntityList list = ga.entities();
  dbg_assert(list.size() == 3);

  dbg_assert(std::find(list.begin(), list.end(), 1) != list.end());
  dbg_assert(std::find(list.begin(), list.end(), 2) != list.end());
  dbg_assert(std::find(list.begin(), list.end(), 3) != list.end());
}

static void unitTestGenericSingleComponent() {
  DO_UNIT_TEST(GenericSingleComponent_add);
  DO_UNIT_TEST(GenericSingleComponent_kill);
  DO_UNIT_TEST(GenericSingleComponent_kill_invalid);
  DO_UNIT_TEST(GenericSingleComponent_hasEntity);
  DO_UNIT_TEST(GenericSingleComponent_clear);
  DO_UNIT_TEST(GenericSingleComponent_entities);
}
#endif // TEST_BUILD

#endif // GENERICSINGLECOMPONENT_H
