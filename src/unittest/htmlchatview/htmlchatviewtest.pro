CONFIG -= app_bundle

MOC_DIR = ../../.moc
OBJECTS_DIR = ../../.obj
UI_DIR = ../../.ui

CONFIG += pep qtestlib
DEFINES += QT_STATICPLUGIN

include(../../../conf.pri)
include(../../src.pri)
include(../../../third-party/cppunit/cppunit.pri)

RESOURCES += htmlchatviewtest.qrc

INCLUDEPATH += $$PWD

HEADERS += \
	../../unittest/htmlchatview/htmlchatviewtest.h

SOURCES += \
	../../unittest/htmlchatview/htmlchatviewtest.cpp\
	../../unittest/htmlchatview/htmlchatviewtestrunner.cpp\

QMAKE_EXTRA_TARGETS = check
check.commands = \$(MAKE) && ./htmlchatviewtest

QMAKE_CLEAN += $(QMAKE_TARGET)

windows {
	include(../../../conf_windows.pri)
	LIBS += -lWSock32 -lUser32 -lShell32 -lGdi32 -lAdvAPI32
	DEFINES += QT_STATICPLUGIN
	INCLUDEPATH += . # otherwise MSVC will fail to find "common.h" when compiling options/* stuff
}
