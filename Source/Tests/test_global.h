#ifndef TEST_GLOBAL_H
#define TEST_GLOBAL_H

#include "Debug.h"
#include "Macros.h"

#include <cstdint>
#include <assert.h>
#include <sstream>

static uint32_t sTestsOK = 0;
static uint32_t sTestsFailed = 0;

#define ENDL "\r\n"

static void printTestResults() {
  std::stringstream ss;
  ss << std::endl << "Tests Finished!!!" << std::endl;
  ss << "=================" << std::endl;
  ss << "Tests OK:     " << sTestsOK << std::endl;
  ss << "Tests FAILED: " << sTestsFailed << std::endl;
  std::cout << ss.str() << std::endl;
}

#define DO_UNIT_TEST(method) \
{\
  bool done = false;\
  try {\
    method();\
    done = true;\
  } catch(...) {}\
  if(done) {\
    /*print(#method " OK");*/\
    sTestsOK += 1;\
  } else {\
    print(#method " Failed!!!");\
    sTestsFailed += 1;\
  }\
}

#define DO_UNIT_TEST_SHOULD_ASSERT(method) \
{\
  bool done = false;\
  try {\
    method();\
    done = true;\
  } catch(...) {}\
  if(done) {\
    print(#method " Failed!!!");\
    sTestsFailed += 1;\
  } else {\
    /*print(#method " OK");*/\
    sTestsOK += 1;\
  }\
}

#define INIT_INTEGRATION_TEST\
  SystemMgr sysMgr;\
  EntityFactory entityFactory;\
  sysMgr.init(&entityFactory);\
  entityFactory.init(&sysMgr);

#define DO_INTEGRATION_TEST(method) \
{\
  bool done = false;\
  try {\
    method();\
    done = true;\
  } catch( const std::runtime_error & ex ) {\
    print(#method " Failed!!!");\
    print(ex.what());\
  }\
  if(done) {\
    print(#method " OK");\
    sTestsOK += 1;\
  } else {\
    sTestsFailed += 1;\
  }\
}

#endif // TEST_GLOBAL_H
