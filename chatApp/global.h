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
    ID_SEARCH_USER_REQ=1007,
    ID_ADD_FRIEND_REQ=1008
};
enum Modules{
    REGISTERMOD=0,
    RESETMOD=1,
    LOGINMOD=2,
    CHATMOD=3,
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
    ADD_USER_TIP_ITEM,
    INVALID_ITEM,
    GROUP_TIP_ITEM,
    LINE_ITEM,
    APPLY_FRIEND_ITEM
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
constexpr int MIN_APPLY_LABEL_ED_LEN = 40;
const QString add_prefix= "add tags";
constexpr int tip_offset = 5;
extern QString gate_url_prefix ;
const std::vector<QString>  strs ={"hello world !",
                                   "nice to meet u",
                                   "New year，new life",
                                   "You have to love yourself",
                                   "My love is written in the wind ever since the whole world is you"};

const std::vector<QString> heads = {
    ":/resourse/head_1.jpg",
    ":/resourse/head_2.jpg",
    ":/resourse/head_3.jpg",
    ":/resourse/head_4.jpg",
    ":/resourse/head_5.jpg"
};

const std::vector<QString> names = {
    "HanMeiMei",
    "Lily",
    "Ben",
    "Androw",
    "Max",
    "Summer",
    "Candy",
    "Hunter"
};


#endif // GLOBAL_H
