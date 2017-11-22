#ifndef _UNIT_TESTING_H
#define _UNIT_TESTING_H

#include "./System/GenericSumUp.h"
#include "./System/GenericAmount.h"
#include "./System/GenericCollection.h"
#include "./System/GenericSingleComponent.h"

void doUnitTests() {
  unitTestGenericSumUp();
  unitTestGenericAmmount();
  unitTestGenericCollection();
  unitTestGenericSingleComponent();
}

#endif // _UNIT_TESTING_H
