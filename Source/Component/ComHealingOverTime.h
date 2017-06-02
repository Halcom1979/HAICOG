#ifndef COMHEALING_H
#define COMHEALING_H

#include <stdint.h>
#include <string>
#include <sstream>

struct ComHealingOverTime
{
  uint16_t ammount;
  uint16_t time;

  ComHealingOverTime()
  : ComHealingOverTime(0,0)
  {}

  ComHealingOverTime(uint16_t v)
  : ComHealingOverTime(v,0)
  {}

  ComHealingOverTime(uint16_t v, uint16_t t)
  : ammount(v)
  , time(t)
  {}
};

static std::string toString(const ComHealingOverTime & com) {
  std::ostringstream res;

  res << "ComHealing: {";
  res << "ammount: " << std::to_string(com.ammount);
  res << ", ";
  res << "time: " << std::to_string(com.time);
  res << "}";

  return res.str();
}

#endif // COMHEALING_H
