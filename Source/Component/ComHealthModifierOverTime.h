#ifndef COMHEALTHMODIFIEROVERTIME_H
#define COMHEALTHMODIFIEROVERTIME_H

#include <stdint.h>
#include <string>
#include <sstream>

struct ComHealthModifierOverTime
{
  int16_t   amount;
  uint16_t  time;

  ComHealthModifierOverTime()
  : ComHealthModifierOverTime(0,0)
  {}

  ComHealthModifierOverTime(int16_t v)
  : ComHealthModifierOverTime(v,0)
  {}

  ComHealthModifierOverTime(uint16_t v, uint16_t t)
  : amount(v)
  , time(t)
  {}
};

static std::string toString(const ComHealthModifierOverTime & com) {
  std::ostringstream res;

  res << "ComHealthModifierOverTime: {";
  res << "modifier: " << std::to_string(com.amount);
  res << ", ";
  res << "time: " << std::to_string(com.time);
  res << "}";

  return res.str();
}

#endif // COMHEALTHMODIFIEROVERTIME_H
