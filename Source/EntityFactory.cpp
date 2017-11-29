#include "EntityFactory.h"

#include <QFile>

#include "Debug.h"
#include "system/SystemMgr.h"

EntityFactory::EntityFactory()
  : mSystemMgr(nullptr)
{
  QFile file("./Data/Blueprints.xml");
  Q_ASSERT(file.open(QIODevice::ReadOnly));

  QString       error;
  int           line = 0;
  int           column = 0;
  if(!mXMLDocument.setContent(&file, &error, &line, &column)) {
    std::stringstream r;
    r << "Could not load xml file. Error:";
    r << qPrintable(error) << ", at line: " << std::to_string(line);
    r << ", column: " << std::to_string(column) << "!" << std::endl;
    print(r.str());
  } else {
    mBlueprints = mXMLDocument.firstChildElement("blueprint");
    Q_ASSERT(!mBlueprints.isNull());
  }

  file.close();
}

void EntityFactory::init(SystemMgr * sysMgr)
{
  dbg_assert(sysMgr != nullptr);
  mSystemMgr = sysMgr;
}

EntityId EntityFactory::create(const std::string & blueprint)
{
  const EntityId id = createEmptyEntity();

  addBlueprintToId(id, blueprint);

  return id;
}

void EntityFactory::addBlueprintToId(EntityId id,
                                     const std::string & blueprint)
{
  dbg_assert(mSystemMgr != nullptr);

  QDomElement bp = findBlueprint(blueprint);

  if(bp.isNull()) {
    return;
  }

  QDomElement childBP = bp.firstChildElement("blueprint");
  while(!childBP.isNull()) {
    const QString name = childBP.attribute("name");

    dbg_assert(!name.isEmpty());
    if(!name.isEmpty()) {
      addBlueprintToId(id, name.toStdString());
    }

    childBP = childBP.nextSiblingElement("blueprint");
  }

  addToSysHealth(id, bp);
  addToSysHealthModOverTime(id, bp);
  addToSysInventory(id, bp);
  addToSysUsable(id, bp);
  addToSysEquipmentSlotsBody(id, bp);
}

EntityId EntityFactory::createEmptyEntity()
{
  return ++mNextId;
}

QDomElement EntityFactory::findBlueprint(const std::string & name) const
{
  QDomElement bp = mBlueprints.firstChildElement(QString::fromStdString(name));

  if(bp.isNull()) {
    print("Could not find blueprint!!!");
  }

  dbg_assert(!bp.isNull());
  return bp;
}

void EntityFactory::addToSysHealth(
    EntityId id,
    const QDomElement & bp) const
{
  const QString comName = QStringLiteral("health");
  QDomElement component = bp.firstChildElement(comName);
  while(!component.isNull()) {
    const int32_t total = component.attribute("total", 0).toInt();
    const int32_t current = component.attribute("current", 0).toInt();
    const int32_t diff = total - current;
    mSystemMgr->health().add(id, total);
    if(current != total) {
      mSystemMgr->healthModifierOverTime().add(id,
                                               ComHealthModOverTime(-diff, 0));
    }

    component = component.nextSiblingElement("health");
  }
}

void EntityFactory::addToSysHealthModOverTime(
    EntityId id,
    const QDomElement & bp) const
{
  const QString comName = QStringLiteral("healthmodovertime");
  QDomElement component = bp.firstChildElement(comName);
  while(!component.isNull()) {
    ComHealthModOverTime c;

    dbg_assert(component.hasAttribute("health"));\
    c.health = component.attribute("health", 0).toInt();

    dbg_assert(component.hasAttribute("rounds"));\
    c.rounds = component.attribute("rounds", 0).toInt();

    mSystemMgr->healthModifierOverTime().add(id, c);
    component = component.nextSiblingElement(comName);
  }
}

void EntityFactory::addToSysInventory(
    EntityId id,
    const QDomElement & bp) const
{

}

void EntityFactory::addToSysUsable(
    EntityId id,
    const QDomElement & bp) const
{
  const QString comName = QStringLiteral("usable");
  QDomElement component = bp.firstChildElement(comName);
  while(!component.isNull()) {
    ComUsable c;

    dbg_assert(component.hasAttribute("usages"));\
    c.usages = component.attribute("usages", 0).toInt();

    dbg_assert(component.hasAttribute("blueprint"));\
    c.blueprint = component.attribute("blueprint", 0).toStdString();

    mSystemMgr->usable().add(id, c);
    component = component.nextSiblingElement(comName);
  }
}

void EntityFactory::addToSysEquipmentSlotsBody(
    EntityId id,
    const QDomElement & bp)
{
  const QString comName = QStringLiteral("equipmentslotsbody");
  const QString slotName = QStringLiteral("slot");
  const QString attachedName = QStringLiteral("attached");

  QDomElement component = bp.firstChildElement(comName);
  while(!component.isNull()) {
    QDomElement slot = component.firstChildElement(slotName);
    while(!slot.isNull()) {
      const QString name = slot.attribute("name", QString());

      if(name == "sead"){
        mSystemMgr->equipmentSlotsBody().add(id, Head);
      } else if(name =="body"){
        mSystemMgr->equipmentSlotsBody().add(id, Body);
      } else if(name =="leftleg"){
        mSystemMgr->equipmentSlotsBody().add(id, LeftLeg);
      } else if(name =="rightleg"){
        mSystemMgr->equipmentSlotsBody().add(id, RightLeg);
      } else if(name =="leftarm"){
        mSystemMgr->equipmentSlotsBody().add(id, LeftArm);
      } else if(name =="rightarm"){
        mSystemMgr->equipmentSlotsBody().add(id, RightArm);
      } else if(name =="lefthand"){
        mSystemMgr->equipmentSlotsBody().add(id, LeftHand);
      } else if(name =="righthand"){
        mSystemMgr->equipmentSlotsBody().add(id, RightHand);
      } else if(name =="shoes"){
        mSystemMgr->equipmentSlotsBody().add(id, BodyAll);
      } else if(name =="hands"){
        mSystemMgr->equipmentSlotsBody().add(id, Hands);
      } else if(name =="arms"){
        mSystemMgr->equipmentSlotsBody().add(id, Arms);
      } else if(name =="legs"){
        mSystemMgr->equipmentSlotsBody().add(id, Legs);
      } else if(name =="bodyall"){
        mSystemMgr->equipmentSlotsBody().add(id, BodyAll);
      } else {
        print("Invalid Equipment slot body location!!!");
        dbg_assert(false);
      }

      slot = slot.nextSiblingElement(slotName);
    }

    QDomElement attached = component.firstChildElement(attachedName);
    while(!attached.isNull()) {
      const QString blueprint = attached.attribute("blueprint", QString());
      const EntityId eqpId = create(blueprint.toStdString());

      const QString name = attached.attribute("name", QString());

      if(name == "head"){
        mSystemMgr->equipmentSlotsBody().attach(id, Head, eqpId);
      } else if(name =="body"){
        mSystemMgr->equipmentSlotsBody().attach(id, Body, eqpId);
      } else if(name =="leftleg"){
        mSystemMgr->equipmentSlotsBody().attach(id, LeftLeg, eqpId);
      } else if(name =="rightleg"){
        mSystemMgr->equipmentSlotsBody().attach(id, RightLeg, eqpId);
      } else if(name =="leftarm"){
        mSystemMgr->equipmentSlotsBody().attach(id, LeftArm, eqpId);
      } else if(name =="rightarm"){
        mSystemMgr->equipmentSlotsBody().attach(id, RightArm, eqpId);
      } else if(name =="lefthand"){
        mSystemMgr->equipmentSlotsBody().attach(id, LeftHand, eqpId);
      } else if(name =="righthand"){
        mSystemMgr->equipmentSlotsBody().attach(id, RightHand, eqpId);
      } else if(name =="shoes"){
        mSystemMgr->equipmentSlotsBody().attach(id, BodyAll, eqpId);
      } else if(name =="hands"){
        mSystemMgr->equipmentSlotsBody().attach(id, Hands, eqpId);
      } else if(name =="arms"){
        mSystemMgr->equipmentSlotsBody().attach(id, Arms, eqpId);
      } else if(name =="legs"){
        mSystemMgr->equipmentSlotsBody().attach(id, Legs, eqpId);
      } else if(name =="bodyall"){
        mSystemMgr->equipmentSlotsBody().attach(id, BodyAll, eqpId);
      } else {
        print("Invalid Equipment slot body location!!!");
        dbg_assert(false);
      }

      attached = slot.nextSiblingElement(attachedName);
    }

    component = component.nextSiblingElement(comName);
  }
}
