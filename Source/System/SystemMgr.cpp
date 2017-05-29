#include "SystemMgr.h"

#include "../Debug.h"
#include "SysHealth.h"

SystemMgr::SystemMgr()
{

}

void SystemMgr::clearSystems()
{
  health().clear();
  inventory().clear();
}

void SystemMgr::apply(uint32_t deltaTime)
{
  std::stringstream r;
  r << "SystemMgr::apply(" << std::to_string(deltaTime) << ")" << std::endl;
  print(r.str());

  mHealth.apply(deltaTime);
  mInventory.apply(deltaTime);
}

SysHealth & SystemMgr::health()
{
  return mHealth;
}

SysInventory &SystemMgr::inventory()
{
  return mInventory;
}
