/****************************************************************************
** Meta object code from reading C++ file 'installer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../rasplex-installer/installer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'installer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Installer_t {
    QByteArrayData data[12];
    char stringdata[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Installer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Installer_t qt_meta_stringdata_Installer = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 6),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 11),
QT_MOC_LITERAL(4, 30, 17),
QT_MOC_LITERAL(5, 48, 13),
QT_MOC_LITERAL(6, 62, 14),
QT_MOC_LITERAL(7, 77, 5),
QT_MOC_LITERAL(8, 83, 13),
QT_MOC_LITERAL(9, 97, 24),
QT_MOC_LITERAL(10, 122, 18),
QT_MOC_LITERAL(11, 141, 8)
    },
    "Installer\0cancel\0\0updateLinks\0"
    "refreshDeviceList\0downloadImage\0"
    "QNetworkReply*\0reply\0fileListReply\0"
    "getImageFileNameFromUser\0writeImageToDevice\0"
    "updateUI\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Installer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08,
       3,    0,   55,    2, 0x08,
       4,    0,   56,    2, 0x08,
       5,    1,   57,    2, 0x08,
       8,    1,   60,    2, 0x08,
       9,    0,   63,    2, 0x08,
      10,    0,   64,    2, 0x08,
      11,    0,   65,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Installer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Installer *_t = static_cast<Installer *>(_o);
        switch (_id) {
        case 0: _t->cancel(); break;
        case 1: _t->updateLinks(); break;
        case 2: _t->refreshDeviceList(); break;
        case 3: _t->downloadImage((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->fileListReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->getImageFileNameFromUser(); break;
        case 6: _t->writeImageToDevice(); break;
        case 7: _t->updateUI(); break;
        default: ;
        }
    }
}

const QMetaObject Installer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Installer.data,
      qt_meta_data_Installer,  qt_static_metacall, 0, 0}
};


const QMetaObject *Installer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Installer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Installer.stringdata))
        return static_cast<void*>(const_cast< Installer*>(this));
    return QDialog::qt_metacast(_clname);
}

int Installer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
