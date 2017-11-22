#ifndef TESTS_H
#define TESTS_H

#ifdef TEST_BUILD

#include "Debug.h"

#include "Integration/_integration_testing.h"
#include "Unit/_unit_testing.h"

void doTests()
{
  doUnitTests();
  doIntegrationTest();

  printTestResults();
}

#endif

#endif // TESTS_H
