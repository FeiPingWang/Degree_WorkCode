/****************************************************************************
** Meta object code from reading C++ file 'Threadrec.h'
**
** Created: Tue Nov 10 15:23:20 2015
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Threadrec.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Threadrec.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ThreadRec[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ThreadRec[] = {
    "ThreadRec\0\0mesRecv(QString)\0stop()\0"
};

const QMetaObject ThreadRec::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ThreadRec,
      qt_meta_data_ThreadRec, 0 }
};

const QMetaObject *ThreadRec::metaObject() const
{
    return &staticMetaObject;
}

void *ThreadRec::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadRec))
        return static_cast<void*>(const_cast< ThreadRec*>(this));
    return QThread::qt_metacast(_clname);
}

int ThreadRec::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mesRecv((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: stop(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ThreadRec::mesRecv(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
