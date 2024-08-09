/****************************************************************************
** Meta object code from reading C++ file 'chatdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../chatdialog.h"
#include <QtNetwork/QSslError>
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatdialog.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSchatDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSchatDialogENDCLASS = QtMocHelpers::stringData(
    "chatDialog",
    "SlotSideContact",
    "",
    "SlotSideChat",
    "slotLoadingChatFriends",
    "slotTextChanged",
    "str",
    "slot_loading_contact_user",
    "slot_apply_friend",
    "std::shared_ptr<AddFriendApply>",
    "apply",
    "slot_add_auth_friend",
    "std::shared_ptr<AuthInfo>",
    "auth_info",
    "slot_auth_rsp",
    "std::shared_ptr<AuthRsp>",
    "auth_rsp",
    "slot_jump_chat_item",
    "std::shared_ptr<SearchInfo>",
    "si",
    "slot_side_chat",
    "slot_friend_info_page",
    "std::shared_ptr<UserInfo>",
    "user_info",
    "slot_switch_apply_friend_page",
    "slot_jump_chat_item_from_info_page",
    "slot_item_clicked",
    "QListWidgetItem*",
    "item",
    "slot_append_send_chat_msg",
    "std::shared_ptr<TextChatData>",
    "msgdata",
    "slot_text_chat_msg",
    "std::shared_ptr<TextChatMsg>"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSchatDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  110,    2, 0x08,    1 /* Private */,
       3,    0,  111,    2, 0x08,    2 /* Private */,
       4,    0,  112,    2, 0x08,    3 /* Private */,
       5,    1,  113,    2, 0x08,    4 /* Private */,
       7,    0,  116,    2, 0x08,    6 /* Private */,
       8,    1,  117,    2, 0x0a,    7 /* Public */,
      11,    1,  120,    2, 0x0a,    9 /* Public */,
      14,    1,  123,    2, 0x0a,   11 /* Public */,
      17,    1,  126,    2, 0x0a,   13 /* Public */,
      20,    0,  129,    2, 0x0a,   15 /* Public */,
      21,    1,  130,    2, 0x0a,   16 /* Public */,
      24,    0,  133,    2, 0x0a,   18 /* Public */,
      25,    1,  134,    2, 0x0a,   19 /* Public */,
      26,    1,  137,    2, 0x0a,   21 /* Public */,
      29,    1,  140,    2, 0x0a,   23 /* Public */,
      32,    1,  143,    2, 0x0a,   25 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, 0x80000000 | 33,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject chatDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSchatDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSchatDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSchatDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<chatDialog, std::true_type>,
        // method 'SlotSideContact'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SlotSideChat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotLoadingChatFriends'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'slot_loading_contact_user'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_apply_friend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<AddFriendApply>, std::false_type>,
        // method 'slot_add_auth_friend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<AuthInfo>, std::false_type>,
        // method 'slot_auth_rsp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<AuthRsp>, std::false_type>,
        // method 'slot_jump_chat_item'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<SearchInfo>, std::false_type>,
        // method 'slot_side_chat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_friend_info_page'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<UserInfo>, std::false_type>,
        // method 'slot_switch_apply_friend_page'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_jump_chat_item_from_info_page'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<UserInfo>, std::false_type>,
        // method 'slot_item_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'slot_append_send_chat_msg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<TextChatData>, std::false_type>,
        // method 'slot_text_chat_msg'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<TextChatMsg>, std::false_type>
    >,
    nullptr
} };

void chatDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<chatDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SlotSideContact(); break;
        case 1: _t->SlotSideChat(); break;
        case 2: _t->slotLoadingChatFriends(); break;
        case 3: _t->slotTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->slot_loading_contact_user(); break;
        case 5: _t->slot_apply_friend((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<AddFriendApply>>>(_a[1]))); break;
        case 6: _t->slot_add_auth_friend((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<AuthInfo>>>(_a[1]))); break;
        case 7: _t->slot_auth_rsp((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<AuthRsp>>>(_a[1]))); break;
        case 8: _t->slot_jump_chat_item((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<SearchInfo>>>(_a[1]))); break;
        case 9: _t->slot_side_chat(); break;
        case 10: _t->slot_friend_info_page((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<UserInfo>>>(_a[1]))); break;
        case 11: _t->slot_switch_apply_friend_page(); break;
        case 12: _t->slot_jump_chat_item_from_info_page((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<UserInfo>>>(_a[1]))); break;
        case 13: _t->slot_item_clicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 14: _t->slot_append_send_chat_msg((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<TextChatData>>>(_a[1]))); break;
        case 15: _t->slot_text_chat_msg((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<TextChatMsg>>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *chatDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *chatDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSchatDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int chatDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
