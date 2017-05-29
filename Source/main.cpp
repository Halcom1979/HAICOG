#include "Debug.h"

#include "System/SystemMgr.h"
#include "EntityFactory.h"
#include "Event/EventMgr.h"

#include "Tests/tests.h"

int main(int argc, char *argv[])
{
  UNUSED(argc)
  UNUSED(argv)

  SystemMgr sysMgr;
  EntityFactory factory(&sysMgr);

  doTests(sysMgr, factory);

  return 0;
}
