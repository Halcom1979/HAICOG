#ifndef COMDAMAGEOVERTIME_H
#define COMDAMAGEOVERTIME_H

#include <stdint.h>
#include <string>
#include <sstream>

struct ComDmgOverTime
{
  uint16_t ammount;
  uint16_t time;

  ComDmgOverTime()
  : ComDmgOverTime(0,0)
  {}

  ComDmgOverTime(int16_t v)
  : ComDmgOverTime(v,0)
  {}

  ComDmgOverTime(uint16_t v, uint16_t t)
  : ammount(v)
  , time(t)
  {}
};

static std::string toString(const ComDmgOverTime & com) {
  std::ostringstream res;

  res << "ComDmgOverTime: {";
  res << "dmg: " << std::to_string(com.ammount);
  res << ", ";
  res << "time: " << std::to_string(com.time);
  res << "}";

  return res.str();
}

#endif // COMDAMAGEOVERTIME_H
