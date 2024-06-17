#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include "QStyle"
#include <QRegularExpression>
#include <memory>
#include <mutex>
#include <QByteArray>
#include <QNetworkReply>
// refresh qss
extern std::function<void(QWidget*)> repolish;
extern std::function<QString(QString)> xorString;
enum ReqId{
    ID_GET_VERIFY_CODE = 1001,
    ID_REG_USER= 1002,
    ID_RESET_PWD=1003,
    ID_LOGIN_USER=1004,
    ID_CHAT_LOGIN=1005,
    ID_CHAT_LOGIN_RSP=1006,
};
enum Modules{
    REGISTERMOD=0,
    RESETMOD=1,
    LOGINMOD=2,
};
enum ErrorCodes{
    SUCCESS=0,
    ERR_JSON=1,
    ERR_NETWORK=2,
};
struct ServerInfo
{
    QString Host;
    QString Port ;
    QString Token;
        int Uid;
};
enum class ChatRole
{
    Self,
    Other,
};
enum TipErr
{
    TIP_SUCCESS=0,
    TIP_EMAIL_ERR=1,
    TIP_PWD_ERR=2,
    TIP_CONFIGM_ERR=3,
    TIP_PWDRE_ERR=4,
    TIP_VARIFY_ERR=5,
    TIP_USER_ERR=6
};
enum ChatUIMode
{
    SearchMode,
    ChatMode,
    ContactMode,
};
enum ListItemType
{
    CHAT_FRIEND_ITEM,
    CONTACT_FRIEND_ITEM,
    SEARCH_USER_ITEM,
    ADD_USER_ITEM,
    INVALID_ITEM,
    GROUP_TIP_ITEM,
};

enum ClicklbState
{
    Normal=0,
    Selected=1
};
struct MsgInfo
{
    QString msgFlag;
    QString contents;
    QPixmap pixMap;
};
extern QString gate_url_prefix ;
#endif // GLOBAL_H
