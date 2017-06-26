#include "SysHealth.h"

#include "../Debug.h"
#include "Helper.h"

#include <sstream>
#include <algorithm>

SysHealth::SysHealth()
: SystemBase("SysHealth")
{

}

void SysHealth::clear()
{
  mComHealthList.clear();
  mComHealthModOverTimeList.clear();
}

std::string SysHealth::dbgEntity(EntityId id) const
{
  std::string s;
  std::stringstream r;
  bool linebreak = false;;

  s = fromEntityListToString(id, mComHealthList);
  if(!s.empty()) {
    r << s;
    linebreak = true;
  }

  s = fromEntityListToString(id, mComHealthModOverTimeList);
  if(!s.empty()) {
    if(linebreak) {
      r << std::endl;
    }

    r << s;
    linebreak = true;
  }

  return r.str();
}

void SysHealth::executeTurn()
{
  std::map<EntityId, int32_t> mods;

  {
    ComModifierOverTimeList::iterator iter = mComHealthModOverTimeList.begin();
    while(iter != mComHealthModOverTimeList.end()) {
      const EntityId id = iter->first;
      const int16_t amount = iter->second.amount;

      mods[id] += amount;

      if(iter->second.time > 1) {
        iter->second.time -= 1;
        ++iter;
      } else {
        iter = mComHealthModOverTimeList.erase(iter);
      }
    }
  }

  {
    std::map<EntityId, int32_t>::const_iterator iter = mods.begin();
    while(iter != mods.end()) {
      modifyHealth(iter->first, iter->second);
      ++iter;
    }
  }
}

void SysHealth::addComponent(EntityId id, const ComHealth & c)
{
  mComHealthList[id] = c;
}

void SysHealth::addComponent(EntityId id, const ComHealthModifierOverTime & c)
{
  dbg_assert(c.amount != 0);

  if(c.time == 0) {
    modifyHealth(id, c.amount);
  } else {
    mComHealthModOverTimeList.push_back(std::make_pair(id,c));
  }
}

bool SysHealth::hasComponentHealth(EntityId id) const
{
  for(auto e : mComHealthList) {
    if(e.first == id) {
      return true;
    }
  }

  return false;
}

bool SysHealth::hasComponentHealthModifierOverTime(EntityId id) const
{
  for(auto e : mComHealthModOverTimeList) {
    if(e.first == id) {
      return true;
    }
  }

  return false;
}

void SysHealth::removeEntity(EntityId id)
{
  removeFromEntityList(id, mComHealthList);
  removeFromEntityList(id, mComHealthModOverTimeList);
}

std::string SysHealth::dbgList() const
{
  std::stringstream r;

  r << entityListToString<ComHealthList>("SysHealth",
                                         mComHealthList);

  r << entityListToString<ComModifierOverTimeList>("SysHealth",
                                                   mComHealthModOverTimeList);

  return r.str();
}

void SysHealth::health(EntityId id, uint32_t & current, uint32_t & total) const
{
  current = 0;
  total = 0;
  for(auto e : mComHealthList) {
    if(e.first == id) {
      current += e.second.current;
      total += e.second.total;
    }
  }
}

void SysHealth::modifier(EntityId id, int32_t & inc)
{
  inc = 0;
  for(auto e : mComHealthModOverTimeList) {
    if(e.first == id) {
      inc += e.second.amount;
    }
  }
}

void SysHealth::modifyHealth(EntityId id, int16_t v)
{
  ComHealthList::iterator iter = mComHealthList.find(id);
  dbg_assert(iter != mComHealthList.end());

  const uint16_t cur = iter->second.current;
  const uint16_t tot = iter->second.total;
  const int calc = cur + v;

  if(calc <= 0) {
    print("Dead");
    mComHealthList.erase(iter);
  } else {
    const uint16_t newValue = std::min((uint16_t)calc, tot);
    iter->second.current = newValue;
  }
}
