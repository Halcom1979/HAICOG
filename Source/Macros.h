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

#define BITMASK_SET(x,y)    ((x) |=   (y))
#define BITMASK_UNSET(x,y)  ((x) &= (~(y)))
#define BITMASK_MATCH(x,y)  ( ((x) & (y)) == (y) )
#define BITMASK_HAS_MATCH_BIT(x,y)  ( ((x) & (y)) != 0 )

#define RIGHTMOST_BIT(n) (n ^ (n & (n - 1)))

#endif // MACROS_H
