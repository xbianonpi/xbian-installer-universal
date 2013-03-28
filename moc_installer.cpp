/****************************************************************************
** Meta object code from reading C++ file 'installer.h'
**
** Created: Wed Mar 27 12:43:48 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "installer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'installer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Installer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      20,   10,   10,   10, 0x08,
      34,   10,   10,   10, 0x08,
      60,   54,   10,   10, 0x08,
      90,   54,   10,   10, 0x08,
     120,   10,   10,   10, 0x08,
     147,   10,   10,   10, 0x08,
     168,   10,   10,   10, 0x08,
     181,  179,   10,   10, 0x08,
     206,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Installer[] = {
    "Installer\0\0cancel()\0updateLinks()\0"
    "refreshDeviceList()\0reply\0"
    "downloadImage(QNetworkReply*)\0"
    "fileListReply(QNetworkReply*)\0"
    "getImageFileNameFromUser()\0"
    "writeImageToDevice()\0updateUI()\0i\0"
    "updateWriteProgress(int)\0showAboutDialog()\0"
};

void Installer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
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
        case 8: _t->updateWriteProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->showAboutDialog(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Installer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Installer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Installer,
      qt_meta_data_Installer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Installer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Installer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Installer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Installer))
        return static_cast<void*>(const_cast< Installer*>(this));
    return QDialog::qt_metacast(_clname);
}

int Installer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
