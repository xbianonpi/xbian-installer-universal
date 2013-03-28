/****************************************************************************
** Meta object code from reading C++ file 'diskwriter_unix.h'
**
** Created: Wed Mar 27 12:43:49 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "diskwriter_unix.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'diskwriter_unix.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DiskWriter_unix[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_DiskWriter_unix[] = {
    "DiskWriter_unix\0"
};

void DiskWriter_unix::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DiskWriter_unix::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DiskWriter_unix::staticMetaObject = {
    { &DiskWriter::staticMetaObject, qt_meta_stringdata_DiskWriter_unix,
      qt_meta_data_DiskWriter_unix, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DiskWriter_unix::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DiskWriter_unix::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DiskWriter_unix::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DiskWriter_unix))
        return static_cast<void*>(const_cast< DiskWriter_unix*>(this));
    return DiskWriter::qt_metacast(_clname);
}

int DiskWriter_unix::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DiskWriter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
