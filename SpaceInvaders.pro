#-------------------------------------------------
#
# Project created by QtCreator 2017-03-31T21:26:27
#
#-------------------------------------------------

QT       += core gui multimedia\
            gui\
            testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceInvaders
TEMPLATE = app

QMAKE_CXXFLAGS += -Wall

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    base.cpp \
    ship.cpp \
    gamedialog.cpp \
    bullet.cpp \
    config.cpp \
    bulletbuilder.cpp \
    alien.cpp \
    swarminfo.cpp \
    swarm.cpp \
    diagonalbullet.cpp \
    alienbuilder.cpp \
    hunter.cpp \
    menu.cpp \
    cursor.cpp \
    background.cpp \
    fighterstate.cpp \
    normalstate.cpp \
    explosion.cpp \
    barrierblock.cpp \
    penstate.cpp \
    unittestspaceinvader.cpp \
    statusbar.cpp \
    gamemenu.cpp \
    powerup.cpp \
    commandgamestart.cpp \
    commandgamepause.cpp \
    commonrestartstage.cpp \
    stagemaker.cpp \
    makerstate.cpp \
    commandclearstage.cpp \
    instructionirequest.cpp \
    leaderboardnamerequest.cpp \
    commandgotogamemode.cpp \
    commandgotostagemakermode.cpp \
    commandgotoleaderboardmode.cpp \
    commandgototitlescreenmode.cpp \
    leaderboard.cpp \
    qtsoundplayer.cpp

HEADERS  += \
    base.h \
    ship.h \
    gamedialog.h \
    bullet.h \
    config.h \
    bulletbuilderinterface.h \
    bulletbuilder.h \
    alien.h \
    swarminfo.h \
    swarm.h \
    diagonalbullet.h \
    alienbuilder.h \
    hunter.h \
    menu.h \
    alienbase.h \
    cursor.h \
    background.h \
    cursorstate.h \
    fighterstate.h \
    normalstate.h \
    explosion.h \
    barrierblock.h \
    penstate.h \
    unittestspaceinvader.h \
    command.h \
    statusbar.h \
    gamemenu.h \
    powerup.h \
    commandgamestart.h \
    commandgamepause.h \
    commonrestartstage.h \
    stagemaker.h \
    makerstate.h \
    commandclearstage.h \
    instructionirequest.h \
    leaderboardnamerequest.h \
    commandgotogamemode.h \
    commandgotostagemakermode.h \
    commandgotoleaderboardmode.h \
    commandgototitlescreenmode.h \
    leaderboard.h \
    qtsoundplayer.h

FORMS    += \
    gamemenu.ui \
    instructionrequest.ui \
    leaderboardnamerequest.ui

RESOURCES += \
    resources.qrc
