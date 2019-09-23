#-------------------------------------------------
#
# Project created by QtCreator 2019-09-03T00:59:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = PectiMazeGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        appsettings.cpp \
        client/client.cpp \
        client/clientinfo.cpp \
        client/clientsettings.cpp \
        client/clientwindow.cpp \
        client/hud.cpp \
        clientregwindow.cpp \
        engine/Objects/enemy.cpp \
        engine/Objects/exit.cpp \
        engine/Objects/floor.cpp \
        engine/Objects/fog.cpp \
        engine/Objects/lamp.cpp \
        engine/Objects/lightsource.cpp \
        engine/Objects/pectiarrow.cpp \
        engine/Objects/pectipatch.cpp \
        engine/Objects/player.cpp \
        engine/Objects/wall.cpp \
        engine/dynamicobject.cpp \
        engine/engine.cpp \
        engine/mazeobject.cpp \
        engine/stateobject.cpp \
        main.cpp \
        mainwindow.cpp \
        maze.cpp \
        parsing/parsingtools.cpp \
        server/server.cpp \
        server/serversettings.cpp \
        server/serverwindow.cpp \
        serverregwindow.cpp \
        settingswindow.cpp \
        windows/avatarselection.cpp \
        windows/eventwindow.cpp

HEADERS += \
        appsettings.h \
        client/client.h \
        client/clientinfo.h \
        client/clientsettings.h \
        client/clientwindow.h \
        client/hud.h \
        clientregwindow.h \
        engine/Objects/enemy.h \
        engine/Objects/exit.h \
        engine/Objects/floor.h \
        engine/Objects/fog.h \
        engine/Objects/lamp.h \
        engine/Objects/lightsource.h \
        engine/Objects/pectiarrow.h \
        engine/Objects/pectipatch.h \
        engine/Objects/player.h \
        engine/Objects/wall.h \
        engine/dynamicobject.h \
        engine/engine.h \
        engine/mazeobject.h \
        engine/stateobject.h \
        mainwindow.h \
        maze.h \
        parsing/parsingtools.h \
        server/server.h \
        server/serversettings.h \
        server/serverwindow.h \
        serverregwindow.h \
        settingswindow.h \
        windows/avatarselection.h \
        windows/eventwindow.h

FORMS += \
        client/clientwindow.ui \
        clientregwindow.ui \
        mainwindow.ui \
        server/serverwindow.ui \
        serverregwindow.ui \
        settingswindow.ui \
        windows/avatarselection.ui \
        windows/eventwindow.ui

QT += \
    network \
    widgets

LIBS += -lstdc++fs

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    avatars.qrc \
    image.qrc \
    texture.qrc
