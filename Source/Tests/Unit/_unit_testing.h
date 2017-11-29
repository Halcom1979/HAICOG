#ifndef _UNIT_TESTING_H
#define _UNIT_TESTING_H

#include "./System/GenericSumUp.h"
#include "./System/GenericAmount.h"
#include "./System/GenericCollection.h"
#include "./System/GenericSingleComponent.h"
#include "./System/GenericEquipmentSlots.h"
#include "./System/SysHealthModOverTime.h"
#include "./System/SysHealth.h"

void doUnitTests() {
  unitTestGenericSumUp();
  unitTestGenericAmmount();
  unitTestGenericCollection();
  unitTestGenericSingleComponent();
  unitTestGenericEquipmentSlots();
  unitTestSysHealthModOverTime();
  unitTestSysHealth();
}

#endif // _UNIT_TESTING_H
