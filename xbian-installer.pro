#-------------------------------------------------
#
# Project created by QtCreator 2013-03-14T18:13:26
#
#-------------------------------------------------

QT       += core gui xml network widgets

TARGET = XBian-installer
TEMPLATE = app

SOURCES += main.cpp\
    installer.cpp \
    version.cpp

HEADERS  += installer.h \
    diskwriter.h \
    version.h

win32 {
    SOURCES += diskwriter_windows.cpp
    HEADERS += diskwriter_windows.h
    CONFIG += rtti static
}
unix {
    SOURCES += diskwriter_unix.cpp
    HEADERS += diskwriter_unix.h \
        zlib.h \
        zconf.h
    LIBS += -lz
}

FORMS    += installer.ui

OTHER_FILES += \
    app.rc

RESOURCES += \
    rsc.qrc

RC_FILE = app.rc
