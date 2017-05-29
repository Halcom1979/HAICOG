#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <sstream>

typedef uint64_t EntityId;

static std::string toString(EntityId id) {
  std::stringstream res;
  res << "EntityId: " << std::to_string(id);
  return res.str();
}

#endif // ENTITY_H
