QT += core xml
QT -= gui

CONFIG += c++11

DESTDIR = $$PWD/Bin

TARGET = HAICOG
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

DEFINES += _DEBUG
DEFINES += TEST_BUILD

SOURCES += \
    Source/EntityFactory.cpp \
    Source/main.cpp \
    Source/System/SystemMgr.cpp \
    Source/System/SysHealth.cpp \
    Source/System/SystemBase.cpp \
    Source/System/SysInventory.cpp \
    Source/System/SysUsable.cpp \
    Source/System/SysHealthModOverTime.cpp \
    Source/EventProvider.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version
# of Qt.
# disables all the APIs deprecated before Qt 6.0.0
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

HEADERS += \
    Source/Debug.h \
    Source/EntityFactory.h \
    Source/Entity.h \
    Source/System/SystemMgr.h \
    Source/System/SysHealth.h \
    Source/Component/ComHealth.h \
    Source/System/SystemBase.h \
    Source/System/SystemIF.h \
    Source/Macros.h \
    Source/Tests/tests.h \
    Source/System/SysInventory.h \
    Source/Component/ComInventory.h \
    Source/Tests/test_global.h \
    Source/Component/ComHealthModifierOverTime.h \
    Source/System/SysUsable.h \
    Source/Component/ComUsable.h \
    Source/System/GenericSumUp.h \
    Source/System/GenericAmount.h \
    Source/Tests/Unit/_unit_testing.h \
    Source/Tests/Integration/_integration_testing.h \
    Source/Test.h \
    Source/System/GenericCollection.h \
    Source/Tests/Integration/TestInt_SystemHealthModOverTime.h \
    Source/Tests/Integration/TestInt_SysInventory.h \
    Source/Tests/Integration/TestInt_Usable.h \
    Source/System/GenericSingleComponent.h \
    Source/Tests/Integration/TestInt_EntityFactory.h \
    Source/System/SysHealthModOverTime.h \
    Source/EventProvider.h \
    Source/EventObserver.h \
    Source/Tests/TestEventObserver.h

RESOURCES +=

DISTFILES += \
    Bin/Data/Blueprints.xml

INCLUDEPATH += ./Source
