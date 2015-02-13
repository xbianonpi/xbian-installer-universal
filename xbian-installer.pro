#-------------------------------------------------
#
# Project created by QtCreator 2013-03-14T18:13:26
#
#-------------------------------------------------

#This was replaced because it can generate some compiling errors:
#QT       += core gui xml network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui xml network


TARGET = XBian-installer
TEMPLATE = app

SOURCES += main.cpp\
    installer.cpp \
    version.cpp \
    dialog.cpp

HEADERS  += installer.h \
    diskwriter.h \
    version.h \
    dialog.h

win32 {
    SOURCES += diskwriter_windows.cpp
    HEADERS += diskwriter_windows.h
    CONFIG += rtti
    QMAKE_LFLAGS  = -static -static-libgcc
}
unix {
    SOURCES += diskwriter_unix.cpp
    HEADERS += diskwriter_unix.h
    LIBS += -lz
}

macx {
    HEADERS += zlib.h \
        zconf.h
    ICON = applet.icns
}

FORMS    += installer.ui \
    dialog.ui

OTHER_FILES += \
    app.rc

RESOURCES += \
    rsc.qrc

RC_FILE = app.rc
