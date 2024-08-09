/****************************************************************************
** Meta object code from reading C++ file 'authenfriend.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../authenfriend.h"
#include <QtNetwork/QSslError>
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'authenfriend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSAuthenFriendENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSAuthenFriendENDCLASS = QtMocHelpers::stringData(
    "AuthenFriend",
    "ShowMoreLabel",
    "",
    "SlotLabelEnter",
    "SlotRemoveFriendLabel",
    "SlotChangeFriendLabelByTip",
    "ClicklbState",
    "SlotLabelTextChange",
    "text",
    "SlotLabelEditFinished",
    "SlotAddFirendLabelByClickTip",
    "SlotApplySure",
    "SlotApplyCancel"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSAuthenFriendENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x0a,    1 /* Public */,
       3,    0,   69,    2, 0x0a,    2 /* Public */,
       4,    1,   70,    2, 0x0a,    3 /* Public */,
       5,    2,   73,    2, 0x0a,    5 /* Public */,
       7,    1,   78,    2, 0x0a,    8 /* Public */,
       9,    0,   81,    2, 0x0a,   10 /* Public */,
      10,    1,   82,    2, 0x0a,   11 /* Public */,
      11,    0,   85,    2, 0x0a,   13 /* Public */,
      12,    0,   86,    2, 0x0a,   14 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 6,    2,    2,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject AuthenFriend::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSAuthenFriendENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSAuthenFriendENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSAuthenFriendENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AuthenFriend, std::true_type>,
        // method 'ShowMoreLabel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SlotLabelEnter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SlotRemoveFriendLabel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'SlotChangeFriendLabelByTip'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<ClicklbState, std::false_type>,
        // method 'SlotLabelTextChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'SlotLabelEditFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SlotAddFirendLabelByClickTip'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'SlotApplySure'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SlotApplyCancel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void AuthenFriend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AuthenFriend *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ShowMoreLabel(); break;
        case 1: _t->SlotLabelEnter(); break;
        case 2: _t->SlotRemoveFriendLabel((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->SlotChangeFriendLabelByTip((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<ClicklbState>>(_a[2]))); break;
        case 4: _t->SlotLabelTextChange((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->SlotLabelEditFinished(); break;
        case 6: _t->SlotAddFirendLabelByClickTip((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->SlotApplySure(); break;
        case 8: _t->SlotApplyCancel(); break;
        default: ;
        }
    }
}

const QMetaObject *AuthenFriend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuthenFriend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSAuthenFriendENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AuthenFriend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
