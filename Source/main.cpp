#include "Debug.h"

#include "System/SystemMgr.h"
#include "EntityFactory.h"
#include "Event/EventMgr.h"

int main(int argc, char *argv[])
{
  UNUSED(argc)
  UNUSED(argv)

  SystemMgr sysMgr;
  EntityFactory factory(&sysMgr);

  const EntityId player = factory.create(std::string("PlayerPoisoned"));

  dbgEntity(player);

  print(sysMgr.health().dbgList());

  sysMgr.apply(5);

  print(sysMgr.health().dbgList());

  return 0;
}
