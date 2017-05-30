#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <QDomDocument>

#include "Macros.h"
#include "Entity.h"
#include "System/SystemMgr.h"

#include <string>

class EntityFactory
{
  public:
    EntityFactory(SystemMgr * sysMgr);

    EntityId createEmptyEntity();

    EntityId create(const std::string & blueprint);

    void addBlueprintToId(EntityId id, const std::string & blueprint);

  private:
    DISABLE_DFLT_CTOR(EntityFactory)

    SystemMgr *   mSystemMgr;
    EntityId      mNextId = 0;
    QDomDocument  mXMLDocument;
    QDomElement   mBlueprints;

    QDomElement findBlueprint(const std::string & name);
};

#endif // ENTITYFACTORY_H
