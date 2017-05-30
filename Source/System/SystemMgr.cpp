#include "SystemMgr.h"

#include "../Debug.h"
#include "SysHealth.h"

SystemMgr::SystemMgr()
{
  mSystems.push_back(&mHealth);
  mSystems.push_back(&mInventory);
}

void SystemMgr::dbgEntity(EntityId id) const
{
  std::stringstream r;

  r << "Entity (" << std::to_string(id) << ") {";
  for(auto e : mSystems) {
    r << std::endl << e->dbgEntity(id) ;
  }
  r << std::endl << "}" << std::endl;

  print(r.str());
}

void SystemMgr::clearSystems()
{
  for(auto e : mSystems) {
    e->clear();
  }
}

void SystemMgr::apply(uint32_t deltaTime)
{
  std::stringstream r;
  r << "SystemMgr::apply(" << std::to_string(deltaTime) << ")" << std::endl;
  print(r.str());

  for(auto e : mSystems) {
    e->apply(deltaTime);
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
