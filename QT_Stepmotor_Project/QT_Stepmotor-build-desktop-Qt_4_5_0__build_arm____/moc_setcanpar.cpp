/****************************************************************************
** Meta object code from reading C++ file 'setcanpar.h'
**
** Created: Tue Apr 19 11:06:42 2016
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QT_Stepmotor/setcanpar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setcanpar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SetCANPar[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   10,   10,   10, 0x08,
      49,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SetCANPar[] = {
    "SetCANPar\0\0stateChanged()\0"
    "on_pB_Cancel_clicked()\0on_pB_Comfirm_clicked()\0"
};

const QMetaObject SetCANPar::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SetCANPar,
      qt_meta_data_SetCANPar, 0 }
};

const QMetaObject *SetCANPar::metaObject() const
{
    return &staticMetaObject;
}

void *SetCANPar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SetCANPar))
        return static_cast<void*>(const_cast< SetCANPar*>(this));
    return QDialog::qt_metacast(_clname);
}

int SetCANPar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: stateChanged(); break;
        case 1: on_pB_Cancel_clicked(); break;
        case 2: on_pB_Comfirm_clicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SetCANPar::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
