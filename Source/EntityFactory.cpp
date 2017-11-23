#include "EntityFactory.h"

#include <QFile>

#include "Debug.h"
#include "System/SystemMgr.h"


#define START_COMP(comName) \
{\
  QDomElement component = bp.firstChildElement(#comName);\
  while(!component.isNull()) {\
    comName c;

#define END_WITHOUT_ADD_COMP(comName) \
    component = component.nextSiblingElement(#comName);\
  }\
}

#define END_COMP(comName, system) \
    system.add(id, c);\
    component = component.nextSiblingElement(#comName);\
  }\
}

#define ATTR_STR(name, init) \
  dbg_assert(component.hasAttribute(#name));\
  c.name = component.attribute(#name, init).toStdString();

#define ATTR_INT32(name, init)\
  dbg_assert(component.hasAttribute(#name));\
  c.name = component.attribute(#name, init).toInt();

#define ASSIGN_INT32(name, init)\
  dbg_assert(component.hasAttribute(#name));\
  c = component.attribute(#name, init).toInt();

#define ATTR_UINT32(name, init)\
  dbg_assert(component.hasAttribute(#name));\
  c.name = component.attribute(#name, init).toUInt();

#define ASSIGN_UINT32(name, init)\
  dbg_assert(component.hasAttribute(#name));\
  c = component.attribute(#name, init).toUInt();

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
    const int32_t total = component.attribute("total", 0).toInt();
    const int32_t current = component.attribute("current", 0).toInt();
    const int32_t diff = total - current;
    mSystemMgr->health().add(id, total);
    if(current != total) {
      mSystemMgr->healthModifierOverTime().add(id,
                                               ComHealthModOverTime(-diff, 0));
    }
  END_WITHOUT_ADD_COMP(ComHealth)

  START_COMP(ComHealthModOverTime)
    ATTR_INT32(health, 0)
    ATTR_INT32(rounds, 0)
  END_COMP(ComHealthModOverTime, mSystemMgr->healthModifierOverTime())

  START_COMP(ComInventory)
  END_COMP(ComInventory, mSystemMgr->inventory())

  START_COMP(ComUsable)
    ATTR_INT32(usages, 0)
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
