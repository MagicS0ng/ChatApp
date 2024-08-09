#ifndef TCPMGR_H
#define TCPMGR_H

#include <QTcpSocket>
#include <QAbstractSocket>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "UserMgr.h"
#include "userdata.h"
class TcpMgr: public QObject, public Singleton<TcpMgr>, public std::enable_shared_from_this<TcpMgr>
{
    Q_OBJECT
public:
    ~TcpMgr();
private:
    friend class Singleton<TcpMgr>;
    void initHandlers();
    void handleMsg(ReqId id, int len, QByteArray data);
    QTcpSocket m_socket;
    QString m_host;
    uint16_t m_port;
    QByteArray m_buffer; //包的数据
    bool m_recv_pending; // tcp 包 超过maxlength会截断, 判断数据是否传输完整
    quint16 m_message_id; // 包的id
    quint16 m_message_len; // 包的length
    QMap<ReqId, std::function<void(ReqId id, int len, QByteArray data)>> _handlers;
    TcpMgr();
public slots:
    void slotSendData(ReqId reqId, QByteArray data);
    void slotTcpConnect(ServerInfo);
signals:
    void sigConSuccess(bool isSuccess); // 连接成功，发送给其他窗口信号
    void sigSendData(ReqId reqId,QByteArray data);
    void sigSwitchChatDlg();
    void sigLoginFailed(int);
    void sigUserSearch(std::shared_ptr<SearchInfo>);
    void sig_friend_apply(std::shared_ptr<AddFriendApply>);
    void sig_add_auth_friend(std::shared_ptr<AuthInfo>);
    void sig_auth_rsp(std::shared_ptr<AuthRsp>);
    void sig_text_chat_msg(std::shared_ptr<TextChatMsg>);
};

#endif // TCPMGR_H
