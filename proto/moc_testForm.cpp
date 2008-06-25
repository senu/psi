/****************************************************************************
** Meta object code from reading C++ file 'testForm.h'
**
** Created: Thu Jun 26 01:25:14 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1-snapshot-20080423)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "testForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1-snapshot-20080423. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestForm[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      50,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,    9,    9,    9, 0x08,
     110,    9,    9,    9, 0x08,
     132,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TestForm[] = {
    "TestForm\0\0messageCreated(const MessageChatEvent*)\0"
    "eventCreated(const ChatEvent*)\0"
    "onConsecutiveButtonClicked()\0"
    "onNextButtonClicked()\0onEventButtonClicked()\0"
};

const QMetaObject TestForm::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_TestForm,
      qt_meta_data_TestForm, 0 }
};

const QMetaObject *TestForm::metaObject() const
{
    return &staticMetaObject;
}

void *TestForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestForm))
        return static_cast<void*>(const_cast< TestForm*>(this));
    return QFrame::qt_metacast(_clname);
}

int TestForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: messageCreated((*reinterpret_cast< const MessageChatEvent*(*)>(_a[1]))); break;
        case 1: eventCreated((*reinterpret_cast< const ChatEvent*(*)>(_a[1]))); break;
        case 2: onConsecutiveButtonClicked(); break;
        case 3: onNextButtonClicked(); break;
        case 4: onEventButtonClicked(); break;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TestForm::messageCreated(const MessageChatEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TestForm::eventCreated(const ChatEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
