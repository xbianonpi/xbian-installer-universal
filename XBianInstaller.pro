#-------------------------------------------------
#
# Project created by QtCreator 2013-01-24T00:31:52
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XBianInstaller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    win_functions.cpp \
    mac_functions.cpp \
    mac_disk.cpp \
    version.cpp

HEADERS  += mainwindow.h \
    win_functions.h \
    mac_functions.h \
    mac_disk.h \
    version.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    logo.png
