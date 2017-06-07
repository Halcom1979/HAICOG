#include "EntityFactory.h"

#include <QFile>

#include "Debug.h"
#include "System/SystemMgr.h"

#define START_COMP(comName) \
{\
  QDomElement component = bp.firstChildElement(#comName);\
  while(!component.isNull()) {\
    comName c;

#define END_COMP(comName, system) \
    system.addComponent(id, c);\
    component = component.nextSiblingElement(#comName);\
  }\
}

#define ATTR_STR(name, init) \
  dbg_assert(component.hasAttribute(#name));\
  c.name = component.attribute(#name, init).toStdString();

#define ATTR_INT(name, init) \
  dbg_assert(component.hasAttribute(#name));\
  c.name = component.attribute(#name, init).toInt();

#define ATTR_F32(name, init) \
  dbg_assert(component.hasAttribute(#name));\
  c.name = component.attribute(#name, init).toFloat();

#define ATTR_F64(name, init) \
  dbg_assert(component.hasAttribute(#name));\
  c.name = component.attribute(#name, init).toFloat();

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
    mBlueprints = mXMLDocument.firstChildElement("Blueprints");
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
                                     const std::string & blueprint) const
{
  dbg_assert(mSystemMgr != nullptr);

  QDomElement bp = findBlueprint(blueprint);

  if(bp.isNull()) {
    return;
  }

  START_COMP(ComHealth)
    ATTR_INT(current, 0)
    ATTR_INT(total, 0)
  END_COMP(ComHealth, mSystemMgr->health())

  START_COMP(ComHealthModifierOverTime)
    ATTR_INT(amount, 0)
    ATTR_INT(time, 0)
  END_COMP(ComHealthModifierOverTime, mSystemMgr->health())

  START_COMP(ComInventory)
  END_COMP(ComInventory, mSystemMgr->inventory())

  START_COMP(ComUsable)
    ATTR_INT(usages, 0)
    ATTR_STR(blueprint, QString())
  END_COMP(ComUsable, mSystemMgr->usable())

  QDomElement childBP = bp.firstChildElement("Blueprints");
  while(!childBP.isNull()) {
    const QString name = childBP.attribute("name");

    dbg_assert(!name.isEmpty());
    if(!name.isEmpty()) {
      addBlueprintToId(id, name.toStdString());
    }

    childBP = childBP.nextSiblingElement("Blueprints");
  }
}

EntityId EntityFactory::createEmptyEntity()
{
  return ++mNextId;
}

QDomElement EntityFactory::findBlueprint(const std::string & name) const
{
  QDomElement bp = mBlueprints.firstChildElement(QString::fromStdString(name));

  dbg_assert(!bp.isNull());
  return bp;
}
