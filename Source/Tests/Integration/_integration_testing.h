#ifndef _INTEGRATION_TESTING_H
#define _INTEGRATION_TESTING_H

#ifdef TEST_BUILD

#include "Tests/test_global.h"
#include "Tests/Integration/TestInt_SystemHealthModOverTime.h"
#include "Tests/Integration/TestInt_SysInventory.h"
#include "Tests/Integration/TestInt_Usable.h"
#include "Tests/Integration/TestInt_EntityFactory.h"

void doIntegrationTest()
{
  DO_INTEGRATION_TEST(testInt_SystHealthModOverTime);
  DO_INTEGRATION_TEST(testInt_SysInventory);
  DO_INTEGRATION_TEST(testInt_SysUsable);
  DO_INTEGRATION_TEST(testInt_EntityFactory);
}

#endif // TEST_BUILD

#endif // _INTEGRATION_TESTING_H
