#include "SystemMgr.h"

#include "../Debug.h"
#include "SysHealth.h"

SystemMgr::SystemMgr()
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

SysHealth & SystemMgr::health()
{
  return mHealth;
}

SysInventory & SystemMgr::inventory()
{
  return mInventory;
}

SysUsable & SystemMgr::usable()
{
  return mUsable;
}
