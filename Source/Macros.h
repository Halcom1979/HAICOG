#ifndef MACROS_H
#define MACROS_H

#define DISABLE_COPY(Class) \
  Class(const Class &) = delete;\
  Class & operator=(const Class &) = delete;

#define DISABLE_DFLT_CTOR(Class) \
  Class() = delete;

#define UNUSED(x) \
  (void)x;

#endif // MACROS_H
