#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <sstream>
#include <list>

typedef uint64_t EntityId;
typedef std::list<EntityId> EntityList;

static std::string toString(EntityId id) {
  std::stringstream res;
  res << "EntityId: " << std::to_string(id);
  return res.str();
}

#endif // ENTITY_H
