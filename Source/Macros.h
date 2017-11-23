#ifndef MACROS_H
#define MACROS_H

#include <algorithm>

#define DISABLE_COPY(Class) \
  Class(const Class &) = delete;\
  Class & operator=(const Class &) = delete;

#define DISABLE_DFLT_CTOR(Class) \
  Class() = delete;

#define UNUSED(x) \
  (void)x;

#define BOUND(low, val, high)\
  (std::max(low, std::min(val, high)))

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#endif // MACROS_H
