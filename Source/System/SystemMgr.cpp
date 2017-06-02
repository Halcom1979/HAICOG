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
