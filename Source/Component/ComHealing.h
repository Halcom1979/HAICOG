#ifndef COMHEALING_H
#define COMHEALING_H

#include <stdint.h>
#include <string>
#include <sstream>

struct ComHealing
{
  uint16_t ammount;
  uint16_t time;

  ComHealing()
  : ComHealing(0,0)
  {}

  ComHealing(uint16_t v)
  : ComHealing(v,0)
  {}

  ComHealing(uint16_t v, uint16_t t)
  : ammount(v)
  , time(t)
  {}
};

static std::string toString(const ComHealing & com) {
  std::ostringstream res;

  res << "ComHealing: {";
  res << "ammount: " << std::to_string(com.ammount);
  res << ", ";
  res << "time: " << std::to_string(com.time);
  res << "}";

  return res.str();
}

#endif // COMHEALING_H
