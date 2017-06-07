#ifndef COMUSABLE_H
#define COMUSABLE_H

#include <string>
#include <sstream>

struct ComUsable
{
  std::string blueprint;
  uint16_t    usages;

  ComUsable()
  {}

  ComUsable(const std::string & b)
  : ComUsable(b, 1)
  {}

  ComUsable(const std::string & b, uint16_t a)
  : blueprint(b)
  , usages(a)
  {}
};

static std::string toString(const ComUsable & com) {
  std::ostringstream res;

  res << "ComUsable: {";
  res << "usages: " << std::to_string(com.usages);
  res << ", blueprint: " << com.blueprint;
  res << "}";

  return res.str();
}

#endif // COMUSABLE_H
