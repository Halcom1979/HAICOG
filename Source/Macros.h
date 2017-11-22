#ifndef MACROS_H
#define MACROS_H

#define DISABLE_COPY(Class) \
  Class(const Class &) = delete;\
  Class & operator=(const Class &) = delete;

#define DISABLE_DFLT_CTOR(Class) \
  Class() = delete;

#define UNUSED(x) \
  (void)x;

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#endif // MACROS_H
