#ifndef COMHEALTH_H
#define COMHEALTH_H

#include <stdint.h>
#include <string>
#include <sstream>

struct ComHealth
{
  int16_t current;
  int16_t total;

  ComHealth()
  : ComHealth(0,0)
  {}

  ComHealth(int16_t cur, int16_t tot)
  : current(cur)
  , total(tot)
  {}
};

static std::string toString(const ComHealth & com) {
  std::ostringstream res;

  res << "ComHealth: {";
  res << "current: " << std::to_string(com.current);
  res << ", total: " << std::to_string(com.total);
  res << "}";

  return res.str();
}

#endif // COMHEALTH_H
