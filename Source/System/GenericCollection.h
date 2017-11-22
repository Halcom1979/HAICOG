#ifndef GENERICCOLLECTION_H
#define GENERICCOLLECTION_H

#include "SystemBase.h"

#include <map>
#include <list>
#include <functional>

template<typename T>
class GenericCollection : public SystemBase
{
  public:
    GenericCollection(const char * name)
    : SystemBase(name)
    {}

    void clear() {
      mComponents.clear();
    }

    void add(EntityId id, const T & c) {
      mComponents[id].push_back(c);
    }

    bool hasEntity(EntityId id) const{
      EntityMap::const_iterator iter = mComponents.find(id);
      return (iter != mComponents.end());
    }

    EntityList entities() const {
      EntityList res;
      for (const auto & entry : mComponents) {
        res.push_back(entry.first);
      }
      return res;
    }

    void remove(EntityId id, const T & c) {
      EntityMap::iterator iter = mComponents.find(id);
      dbg_assert(iter != mComponents.end());

      ComponentList::iterator listIter = iter->second.begin();
      while(listIter != iter->second.end()) {
        if(*listIter == c) {
          iter->second.erase(listIter);

          if(iter->second.empty()) {
            mComponents.erase(iter);
          }

          return;
        }

        ++listIter;
      }

      dbg_assert(false);
    }

    void kill(EntityId id) {
      EntityMap::iterator iter = mComponents.find(id);
      if(iter != mComponents.end()) {
        mComponents.erase(iter);
      }
    }

    void apply(const std::function<void(T &)> & doThis) {
      for (auto & compList : mComponents) {
        for (auto & comp : compList.second) {
          doThis(comp);
        }
      }
    }

    void applyAndRemoveIf(const std::function<void(EntityId, T &)> & doThis,
                          const std::function<bool(const T &)> & removeIf)
    {
      EntityMap::iterator iterComp = mComponents.begin();
      while(iterComp != mComponents.end())
      {
        const EntityId id = iterComp->first;
        ComponentList::iterator iterList = iterComp->second.begin();
        while(iterList != iterComp->second.end())
        {
          doThis(id, *iterList);
          if(removeIf(*iterList)) {
            iterList = iterComp->second.erase(iterList);
          } else {
            ++iterList;
          }
        }

        if(iterComp->second.empty()) {
          iterComp = mComponents.erase(iterComp);
        } else {
          ++iterComp;
        }
      }
    }

  protected:
    typedef std::list<T> ComponentList;
    const ComponentList & components(EntityId id) const {
      EntityMap::const_iterator iter = mComponents.find(id);
      dbg_assert(iter != mComponents.end());
      return iter->second;
    }

  private:
    DISABLE_DFLT_CTOR(GenericCollection)

    typedef std::map<EntityId, ComponentList> EntityMap;
    EntityMap mComponents;
};

#ifdef TEST_BUILD

#include "./Tests/test_global.h"

static void GenericCollection_add() {
  GenericCollection<int32_t> ga("Test");
  ga.add(1, 5);
  dbg_assert(ga.hasEntity(1));
}

static void GenericCollection_remove() {
  GenericCollection<int32_t> ga("Test");
  ga.add(1, 7);
  ga.add(1, 9);

  ga.remove(1, 7);
  dbg_assert(ga.hasEntity(1));
  ga.remove(1, 9);
  dbg_assert(!ga.hasEntity(2));
}

static void GenericCollection_remove_invalid_id() {
  GenericCollection<int32_t> ga("Test");
  ga.remove(1, 7);
}

static void GenericCollection_remove_invalid_comp() {
  GenericCollection<int32_t> ga("Test");
  ga.add(1, 5);
  ga.remove(1, 7);
}

static void GenericCollection_kill() {
  GenericCollection<int32_t> ga("Test");
  ga.add(1, 5);
  ga.kill(1);
  dbg_assert(!ga.hasEntity(1));
}

static void GenericCollection_kill_invalid() {
  GenericCollection<int32_t> ga("Test");
  ga.kill(1);
}

static void GenericCollection_hasEntity() {
  GenericCollection<int32_t> ga("Test");
  dbg_assert(!ga.hasEntity(1));

  ga.add(1, 5);
  dbg_assert(ga.hasEntity(1));
}

static void GenericCollection_clear() {
  GenericCollection<int32_t> ga("Test");
  ga.add(1, 1);
  ga.add(2, 2);
  ga.add(3, 3);
  ga.clear();
  dbg_assert(!ga.hasEntity(1));
  dbg_assert(!ga.hasEntity(2));
  dbg_assert(!ga.hasEntity(3));
}

static void GenericCollection_entities() {
  GenericCollection<int32_t> ga("Test");
  ga.add(1, 1);
  ga.add(2, 2);
  ga.add(3, 3);
  EntityList list = ga.entities();
  dbg_assert(list.size() == 3);

  dbg_assert(std::find(list.begin(), list.end(), 1) != list.end());
  dbg_assert(std::find(list.begin(), list.end(), 2) != list.end());
  dbg_assert(std::find(list.begin(), list.end(), 3) != list.end());
}

class GenericCollectionTest: public GenericCollection<int32_t>
{
  public:
    GenericCollectionTest():GenericCollection("Test"){}

    void test_apply() {
      add(1, 10);
      add(2, 30);
      apply([](int32_t & a){a *= 2;});

      {
        std::list<int32_t> list = components(1);
        dbg_assert(list.size() == 1);
        dbg_assert(std::find(list.begin(), list.end(), 20) != list.end());
      }

      {
        std::list<int32_t> list = components(2);
        dbg_assert(list.size() == 1);
        dbg_assert(std::find(list.begin(), list.end(), 60) != list.end());
      }
    }

    void test_applyAndRemoveIf() {
      add(1, 10);
      add(2, 20);
      applyAndRemoveIf([](EntityId id, int32_t & a){a -= 1;},
                       [](const int32_t & a){return (a == 9);});

      dbg_assert(!hasEntity(1));
      dbg_assert(hasEntity(2));
    }
};

static void GenericCollection_apply() {
  GenericCollectionTest gct;
  gct.test_apply();
}

static void GenericCollection_applyAndRemoveIf() {
  GenericCollectionTest gct;
  gct.test_applyAndRemoveIf();
}

static void unitTestGenericCollection() {
  DO_UNIT_TEST(GenericCollection_add);
  DO_UNIT_TEST(GenericCollection_remove);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericCollection_remove_invalid_id);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericCollection_remove_invalid_comp);
  DO_UNIT_TEST(GenericCollection_kill);
  DO_UNIT_TEST(GenericCollection_kill_invalid);
  DO_UNIT_TEST(GenericCollection_hasEntity);
  DO_UNIT_TEST(GenericCollection_clear);
  DO_UNIT_TEST(GenericCollection_entities);
  DO_UNIT_TEST(GenericCollection_apply);
  DO_UNIT_TEST(GenericCollection_applyAndRemoveIf);
}
#endif

#endif // GENERICCOLLECTION_H
