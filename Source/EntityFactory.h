#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <QDomDocument>

#include "Entity.h"

#include <string>

class SystemMgr;

class EntityFactory
{
  public:
    EntityFactory();

    void init(SystemMgr * sysMgr);

    EntityId createEmptyEntity();

    EntityId create(const std::string & blueprint);

    void addBlueprintToId(EntityId id, const std::string & blueprint) const;

  private:

    SystemMgr *           mSystemMgr;
    EntityId              mNextId = 0;
    QDomDocument          mXMLDocument;
    QDomElement           mBlueprints;

    QDomElement findBlueprint(const std::string & name) const;
};

#endif // ENTITYFACTORY_H
