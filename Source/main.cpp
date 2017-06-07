#include "Debug.h"

#include "System/SystemMgr.h"
#include "EntityFactory.h"

#include "Tests/tests.h"

int main(int argc, char *argv[])
{
  UNUSED(argc)
  UNUSED(argv)

  SystemMgr sysMgr;
  EntityFactory entityFactory;

  sysMgr.init(&entityFactory);
  entityFactory.init(&sysMgr);

  doTests(sysMgr, entityFactory);

  return 0;
}
