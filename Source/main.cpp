#include "Debug.h"

#include "System/SystemMgr.h"
#include "EntityFactory.h"

#include "Tests/tests.h"

int main(int argc, char *argv[])
{
  UNUSED(argc)
  UNUSED(argv)

  #ifdef TEST_BUILD
    doTests();
  #endif

  return 0;
}
