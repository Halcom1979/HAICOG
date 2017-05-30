#include "SysHealth.h"

#include "../Debug.h"
#include <sstream>
#include <algorithm>

SysHealth::SysHealth()
: SystemBase("SysHealth")
{

}

void SysHealth::clear()
{
  mComHealthList.clear();
  mComHealingList.clear();
  mComDmgOverTimeList.clear();
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

  s = fromEntityListToString(id, mComHealingList);
  if(!s.empty()) {
    if(linebreak) {
      r << std::endl;
    }

    r << s;
    linebreak = true;
  }

  s = fromEntityListToString(id, mComDmgOverTimeList);
  if(!s.empty()) {
    if(linebreak) {
      r << std::endl;
    }

    r << s;
  }

  return r.str();
}

void SysHealth::apply(uint32_t deltaTime)
{
  for(uint32_t i = 0; i < deltaTime; ++i) {
    for(auto e : mComHealingList) {
      const EntityId id = e.first;
      uint16_t inc = e.second.ammount;

      ComHealthList::iterator iter = mComHealthList.find(id);
      dbg_assert(iter != mComHealthList.end());

      if(iter->second.current > inc) {
        iter->second.current -= inc;
      } else {
        print("Dead");
      }
    }
  }
}

void SysHealth::addComponent(EntityId id, const ComHealth & c)
{
  mComHealthList[id] = c;
}

void SysHealth::addComponent(EntityId id, const ComDmgOverTime & c)
{
  dbg_assert(c.ammount != 0);

  if(c.time == 0) {
    modifyHealth(id, -c.ammount);
  } else {
    mComDmgOverTimeList.push_back(std::make_pair(id,c));
  }
}

void SysHealth::removeEntity(EntityId id)
{

}

void SysHealth::addComponent(EntityId id, const ComHealing & c)
{
  dbg_assert(c.ammount != 0);

  if(c.time == 0) {
    modifyHealth(id, c.ammount);
  } else {
    mComHealingList.push_back(std::make_pair(id,c));
  }
}

std::string SysHealth::dbgList() const
{
  std::stringstream r;
  r << entityListToString<ComHealthList>("SysHealth", mComHealthList);
  r << entityListToString<ComHealingList>("SysHealth", mComHealingList);
  r << entityListToString<ComDmgOverTimeList>("SysHealth", mComDmgOverTimeList);
  return r.str();
}

void SysHealth::health(EntityId id, uint32_t & current, uint32_t & total)
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

void SysHealth::healing(EntityId id, uint32_t & inc)
{
  inc = 0;
  for(auto e : mComHealingList) {
    if(e.first == id) {
      inc += e.second.ammount;
    }
  }
}

void SysHealth::applyDamageOverTime()
{
  ComDmgOverTimeList::iterator iter = mComDmgOverTimeList.begin();
  while(iter != mComDmgOverTimeList.end()) {
    const EntityId id = (*iter).first;
    const uint16_t ammount = (*iter).second.ammount;

    if(iter->second.time > 1) {
      iter->second.time -= 1;
      ++iter;
    } else {
      iter = mComDmgOverTimeList.erase(iter);
    }

    modifyHealth(id, -ammount);
  }
}

void SysHealth::applyHealing()
{
  ComHealingList::iterator iter = mComHealingList.begin();
  while(iter != mComHealingList.end()) {
    const EntityId id = (*iter).first;
    const uint16_t ammount = (*iter).second.ammount;

    if(iter->second.time > 1) {
      iter->second.time -= 1;
      ++iter;
    } else {
      iter = mComHealingList.erase(iter);
    }

    modifyHealth(id, ammount);
  }
}

void SysHealth::modifyHealth(EntityId id, int16_t v)
{
  ComHealthList::iterator iter = mComHealthList.find(id);
  dbg_assert(iter != mComHealthList.end());

  iter->second.current += v;
}
