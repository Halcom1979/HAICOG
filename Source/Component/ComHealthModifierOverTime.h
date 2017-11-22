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

  explicit ComHealthModOverTime(int16_t v)
  : ComHealthModOverTime(v,0)
  {}

  explicit ComHealthModOverTime(int16_t v, uint16_t t)
  : health(v)
  , rounds(t)
  {}
};

#endif // COMHEALTHMODIFIEROVERTIME_H
