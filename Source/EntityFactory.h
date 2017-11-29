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

    void addBlueprintToId(EntityId id, const std::string & blueprint);

  private:

    SystemMgr *           mSystemMgr;
    EntityId              mNextId = 0;
    QDomDocument          mXMLDocument;
    QDomElement           mBlueprints;

    QDomElement findBlueprint(const std::string & name) const;

    void addToSysHealth(EntityId id, const QDomElement & bp) const;
    void addToSysHealthModOverTime(EntityId id, const QDomElement & bp) const;
    void addToSysInventory(EntityId id, const QDomElement & bp) const;
    void addToSysUsable(EntityId id, const QDomElement & bp) const;
    void addToSysEquipmentSlotsBody(EntityId id, const QDomElement & bp);
};

#endif // ENTITYFACTORY_H
