/****************************************************************************
** Meta object code from reading C++ file 'htmlChatView.h'
**
** Created: Thu Jun 26 01:25:13 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.1-snapshot-20080423)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "htmlChatView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'htmlChatView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.1-snapshot-20080423. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HTMLChatView[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      27,   14,   13,   13, 0x0a,
      47,   13,   13,   13, 0x0a,
      71,   13,   13,   13, 0x0a,
      83,   79,   13,   13, 0x0a,
     128,  122,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HTMLChatView[] = {
    "HTMLChatView\0\0scriptSource\0"
    "evaluateJS(QString)\0importJSChatFunctions()\0"
    "clear()\0msg\0appendMessage(const MessageChatEvent*)\0"
    "event\0appendEvent(const ChatEvent*)\0"
};

const QMetaObject HTMLChatView::staticMetaObject = {
    { &ChatView::staticMetaObject, qt_meta_stringdata_HTMLChatView,
      qt_meta_data_HTMLChatView, 0 }
};

const QMetaObject *HTMLChatView::metaObject() const
{
    return &staticMetaObject;
}

void *HTMLChatView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HTMLChatView))
        return static_cast<void*>(const_cast< HTMLChatView*>(this));
    return ChatView::qt_metacast(_clname);
}

int HTMLChatView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ChatView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: evaluateJS((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: importJSChatFunctions(); break;
        case 2: clear(); break;
        case 3: appendMessage((*reinterpret_cast< const MessageChatEvent*(*)>(_a[1]))); break;
        case 4: appendEvent((*reinterpret_cast< const ChatEvent*(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
