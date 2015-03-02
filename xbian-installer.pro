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
# Name of the application signing certificate
    APPCERT = "3rd Party Mac Developer Application: <name/company>"

    # Name of the installer signing certificate
    INSTALLERCERT = "3rd Party Mac Developer Installer: <name/company>"

    # Bundle identifier for your application
    BUNDLEID = <com.company.YourApp>

    # Name of the entitlements file
    ENTITLEMENTS = Entitlements.plist

    # Path to Qt
    QTPATH = ~/Qt/5.4/clang_64

    # Frameworks Location
    FWLOC = $${QTPATH}/lib

    QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_OBJECTIVE_CFLAGS_RELEASE =  $$QMAKE_OBJECTIVE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

    codesign.depends  += all
    codesign.commands += $${QTPATH}/bin/macdeployqt $${TARGET}.app -verbose=3;

    # Copy plist files to correct locations for signing
    # Add a line for each framework included in your app
    codesign.commands += cp $${FWLOC}/QtCore.framework/Contents/Info.plist $${TARGET}.app/Contents/Frameworks/QtCore.framework/Resources/Info.plist;

    # Sign frameworks (change to suit your application)
    # Add a line for each framework in application
    codesign.commands += codesign -f -s \'$${APPCERT}\' -i $${BUNDLEID} $${TARGET}.app/Contents/Frameworks/QtCore.framework;

    # Sign plugins (change to suit your application)
    # Add a line for each plugin in application
    codesign.commands += codesign -f -s \'$${APPCERT}\' -i $${BUNDLEID} $${TARGET}.app/Contents/PlugIns/accessible/libqtaccessiblewidgets.dylib;

    # Sign the application bundle, using the provided entitlements
    codesign.commands += codesign -f -s \'$${APPCERT}\' -v --entitlements $${ENTITLEMENTS} $${TARGET}.app;

    product.depends += all

    # Build the product package
    product.commands += productbuild --component $${TARGET}.app /Applications --sign \'$${INSTALLERCERT}\' $${TARGET}.pkg;

    QMAKE_EXTRA_TARGETS += codesign product copyfiles
}

FORMS    += installer.ui \
    dialog.ui

OTHER_FILES += \
    app.rc

RESOURCES += \
    rsc.qrc

RC_FILE = app.rc
