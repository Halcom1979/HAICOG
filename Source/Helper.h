#ifndef HELPER_H
#define HELPER_H

#include "Entity.h"
#include "Debug.h"

template<typename T>
static void removeFromEntityList(EntityId id, T & list) {
  T::iterator iter = list.begin();
  while(iter != list.end()) {
    if(iter->first == id) {
      iter = list.erase(iter);
    } else {
      ++iter;
    }
  }
}

template<typename T>
static void removeFromEntityMap(EntityId id, T & m) {
  m.erase(id);
}

#endif // HELPER_H
