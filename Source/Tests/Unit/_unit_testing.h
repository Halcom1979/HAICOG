#ifndef _UNIT_TESTING_H
#define _UNIT_TESTING_H

#include "./System/GenericSumUp.h"
#include "./System/GenericAmount.h"
#include "./System/GenericCollection.h"
#include "./System/GenericSingleComponent.h"
#include "./System/SystemHealthModOverTime.h"

void doUnitTests() {
  unitTestGenericSumUp();
  unitTestGenericAmmount();
  unitTestGenericCollection();
  unitTestGenericSingleComponent();
  unitTestSysHealthModOverTime();
}

#endif // _UNIT_TESTING_H
