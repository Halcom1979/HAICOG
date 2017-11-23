#ifndef COMHEALTHMODIFIEROVERTIME_H
#define COMHEALTHMODIFIEROVERTIME_H

#include <stdint.h>
#include <string>
#include <sstream>

struct ComHealthModOverTime
{
  int16_t   health;
  uint16_t  rounds;

  ComHealthModOverTime()
  : ComHealthModOverTime(0,0)
  {}

  explicit ComHealthModOverTime(int16_t h)
  : ComHealthModOverTime(h,0)
  {}

  explicit ComHealthModOverTime(int16_t h, uint16_t r)
  : health(h)
  , rounds(r)
  {}
};

#endif // COMHEALTHMODIFIEROVERTIME_H
