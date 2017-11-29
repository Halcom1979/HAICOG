#ifndef GENERICEQUIPMENTSLOTS_H
#define GENERICEQUIPMENTSLOTS_H

#include "System/SystemBase.h"
#include "Helper.hpp"

#include <map>

template<typename T, int S>
class GenericEquipmentSlots : public SystemBase
{
  public:
    GenericEquipmentSlots(const char * name)
    : SystemBase(name)
    {}

    void clear() {
      mEquipmentSlots.clear();
    }

    void add(EntityId id, T EquipmentSlot) {
      const uint32_t bits = uint32_t(EquipmentSlot);
      EquipmentSlotMap::iterator iter = mEquipmentSlots.find(id);
      if(iter == mEquipmentSlots.end()) {
        mEquipmentSlots[id] = EquipmentSlotData(bits);
      } else {
        dbg_assert(!BITMASK_HAS_MATCH_BIT(iter->second.available, bits));
        BITMASK_SET(iter->second.available, bits);
      }
    }

    bool hasEntity(EntityId id) const {
      return (mEquipmentSlots.find(id) != mEquipmentSlots.end());
    }

    uint32_t available(EntityId id) const {
      dbg_assert(hasEntity(id));
      EquipmentSlotMap::const_iterator iter = mEquipmentSlots.find(id);
      return iter->second.available;
    }

    uint32_t used(EntityId id) const {
      dbg_assert(hasEntity(id));
      EquipmentSlotMap::const_iterator iter = mEquipmentSlots.find(id);
      uint32_t used = 0;
      for(int i = 0; i < S; ++i) {
        if(iter->second.attached[i] != 0) {
          BITMASK_SET(used, (1 << i));
        }
      }

      return used;
    }

    void attach(EntityId id, T EquipmentSlot, EntityId id_att) {
      dbg_assert(hasEntity(id));
      EquipmentSlotMap::iterator iter = mEquipmentSlots.find(id);

      dbg_assert(BITMASK_MATCH(available(id), EquipmentSlot));
      dbg_assert(!BITMASK_HAS_MATCH_BIT(used(id), EquipmentSlot));

      for(int i = 0; i < S; ++i) {
        if(BITMASK_HAS_MATCH_BIT((1 << i), EquipmentSlot)) {
          iter->second.attached[i] = id_att;
        }
      }
    }

    EntityId attached(EntityId id, T slot) const {
      dbg_assert(hasEntity(id));
      EquipmentSlotMap::const_iterator iter = mEquipmentSlots.find(id);

      const int index = trailing_zeros(slot);
      dbg_assert(BITMASK_MATCH(available(id), slot));
      return iter->second.attached[index];
    }

    EntityList entities() const {
      EntityList res;
      for (const auto & entry : mEquipmentSlots) {
        res.push_back(entry.first);
      }
      return res;
    }

    void kill(EntityId id) {
      EquipmentSlotMap::iterator iter = mEquipmentSlots.begin();
      while(iter != mEquipmentSlots.end()) {
        if(iter->first == id) {
          mEquipmentSlots.erase(iter);
          return;
        } else {
          for(int i = 0; i < S; ++i) {
            if(iter->second.attached[i] == id) {
              iter->second.attached[i] = 0;
            }
          }
        }
        ++iter;
      }
    }

  private:
    DISABLE_COPY(GenericEquipmentSlots)
    DISABLE_DFLT_CTOR(GenericEquipmentSlots)

    struct EquipmentSlotData {
        uint32_t  available;
        EntityId  attached[S];

        EquipmentSlotData()
        : EquipmentSlotData(0)
        {}

        EquipmentSlotData(uint32_t l)
        : available(l)
        {
          for(int i = 0; i < S; ++i) {
            attached[i] = 0;
          }
        }
    };

    typedef std::map<EntityId, EquipmentSlotData> EquipmentSlotMap;
    EquipmentSlotMap mEquipmentSlots;
};

#ifdef TEST_BUILD

#include "./Tests/test_global.h"

enum TestEquipmentSlot {
  TestLoc_0 = (1 << 0),
  TestLoc_1 = (1 << 1),
  TestLoc_2 = (1 << 2),
  TestLoc_3 = (1 << 3),
  TestLoc_4 = (1 << 4),
  TestLoc_5 = (1 << 5),
  TestLoc_6 = (1 << 6),
  TestLoc_7 = (1 << 7)
};

static void GenericEquipmentSlots_add() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.add(1, TestLoc_5);
  s.add(1, TestLoc_7);
  s.add(1, TestLoc_6);
  dbg_assert(s.hasEntity(1));

  const uint32_t used = s.used(1);
  dbg_assert(BITMASK_MATCH(used, 0));

  const uint32_t available = s.available(1);
  dbg_assert(BITMASK_MATCH(available, TestLoc_5 | TestLoc_7 | TestLoc_6));
}

static void GenericEquipmentSlots_attach() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.add(1, TestLoc_5);
  s.add(1, TestLoc_7);
  s.attach(1, TestLoc_5, 2);
  s.attach(1, TestLoc_7, 3);

  dbg_assert(s.attached(1, TestLoc_5) == 2);
  dbg_assert(s.attached(1, TestLoc_7) == 3);
}

static void GenericEquipmentSlots_attach_invalid_id() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.attach(1, TestLoc_0, 3);
}

static void GenericEquipmentSlots_attached_invalid_id() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.attached(1, TestLoc_0);
}

static void GenericEquipmentSlots_attach_inv_EquipmentSlot() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.add(1, TestLoc_1);
  s.attach(1, TestLoc_0, 3);
}

static void GenericEquipmentSlots_attached_inv_EquipmentSlot() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.add(1, TestLoc_1);
  s.attached(1, TestLoc_0);
}

static void GenericEquipmentSlots_attach_used() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.add(1, TestLoc_1);
  s.attach(1, TestLoc_1, 2);
  s.attach(1, TestLoc_1, 3);
}

static void GenericEquipmentSlots_kill() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.add(1, TestLoc_0);
  s.add(2, TestLoc_0);
  s.attach(1, TestLoc_0, 3);

  s.kill(2);
  dbg_assert(s.hasEntity(1));
  dbg_assert(!s.hasEntity(2));

  s.kill(3);
  dbg_assert(s.attached(1, TestLoc_0) == 0);
}

static void GenericEquipmentSlots_kill_invalid() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.kill(1);
}

static void GenericEquipmentSlots_entities() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.add(1, TestLoc_0);
  s.add(2, TestLoc_1);
  s.add(3, TestLoc_2);
  EntityList list = s.entities();
  dbg_assert(list.size() == 3);

  dbg_assert(std::find(list.begin(), list.end(), 1) != list.end());
  dbg_assert(std::find(list.begin(), list.end(), 2) != list.end());
  dbg_assert(std::find(list.begin(), list.end(), 3) != list.end());
}

static void GenericEquipmentSlots_used() {
  GenericEquipmentSlots<TestEquipmentSlot, 8> s("Test");
  s.add(1, TestLoc_5);
  s.add(1, TestLoc_7);
  s.add(1, TestLoc_2);
  s.add(1, TestLoc_0);
  s.attach(1, TestLoc_5, 2);
  s.attach(1, TestLoc_7, 3);

  const uint32_t used = s.used(1);
  dbg_assert(BITMASK_MATCH(used, TestLoc_5 | TestLoc_7));
}

static void unitTestGenericEquipmentSlots() {
  DO_UNIT_TEST(GenericEquipmentSlots_add);
  DO_UNIT_TEST(GenericEquipmentSlots_attach);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericEquipmentSlots_attach_invalid_id);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericEquipmentSlots_attached_invalid_id);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericEquipmentSlots_attach_inv_EquipmentSlot);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericEquipmentSlots_attached_inv_EquipmentSlot);
  DO_UNIT_TEST_SHOULD_ASSERT(GenericEquipmentSlots_attach_used);
  DO_UNIT_TEST(GenericEquipmentSlots_kill);
  DO_UNIT_TEST(GenericEquipmentSlots_kill_invalid);
  DO_UNIT_TEST(GenericEquipmentSlots_entities);
  DO_UNIT_TEST(GenericEquipmentSlots_used);
}

#endif // TEST_BUILD

#endif // GENERICEQUIPMENTSLOTS_H
