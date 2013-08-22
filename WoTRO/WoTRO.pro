#-------------------------------------------------
#
# Project created by QtCreator 2013-07-08T20:27:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

Debug:DEFINES+=DEBUG

Release:DEFINES+=QT_NO_DEBUG_OUTPUT

TARGET = WoTRO
TEMPLATE = app


SOURCES += main.cpp\
    player.cpp \
    replayTableItem.cpp \
    replayTableWidget.cpp \
    settingsDialog.cpp \
    mainWindow.cpp \
    replay.cpp \
    replayLoadingThread.cpp \
    columns.cpp

HEADERS  += \
    player.h \
    constants.h \
    replayTableItem.h \
    replayTableWidget.h \
    settingsDialog.h \
    mainWindow.h \
    replayLoadingThread.h \
    replay.h \
    columns.h

FORMS    += \
    settingsDialog.ui \
    mainWindow.ui \

RESOURCES += \
    res.qrc

OTHER_FILES += \
    readme.txt \
    wotro_pl.ts

TRANSLATIONS = wotro_pl.ts
