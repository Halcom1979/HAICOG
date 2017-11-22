#include "SystemMgr.h"

#include "../Debug.h"
#include "SysHealth.h"

SystemMgr::SystemMgr()
: mInventory(this)
, mHealth()
, mHealthMod(&mHealth)
, mUsable()
{

}

void SystemMgr::init(EntityFactory * factory)
{
  mUsable.init(factory);

  mSystems.push_back(&mHealth);
  mSystems.push_back(&mInventory);
  mSystems.push_back(&mUsable);
}

void SystemMgr::dbgEntity(EntityId id) const
{
  /*
  std::stringstream r;

  r << "Entity (" << std::to_string(id) << ") {" << std::endl;
  for(auto e : mSystems) {
    const std::string dbgstr = e->dbgEntity(id);
    if(!dbgstr.empty()) {
      r << dbgstr << std::endl;
    }
  }
  r << "}" << std::endl;

  print(r.str());
  */
}

void SystemMgr::clearSystems()
{
  for(auto e : mSystems) {
    e->clear();
  }
}

void SystemMgr::executeTurn(uint32_t deltaTime)
{
  for(uint32_t i = 0; i < deltaTime; ++i) {
    for(auto e : mSystems) {
      e->executeTurn();
    }
  }
}

void SystemMgr::kill(EntityId id)
{
  for(auto e : mSystems) {
    e->kill(id);
  }
}

SysHealth & SystemMgr::health()
{
  return mHealth;
}

SysHealthModOverTime &SystemMgr::healthModifierOverTime()
{
  return mHealthMod;
}

SysInventory & SystemMgr::inventory()
{
  return mInventory;
}

SysUsable & SystemMgr::usable()
{
  return mUsable;
}

