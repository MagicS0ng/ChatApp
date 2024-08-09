#include "tcpmgr.h"


TcpMgr::TcpMgr():m_host(""), m_port(0), m_recv_pending(false), m_message_id(0), m_message_len(0)
{
    QObject::connect(&m_socket, &QTcpSocket::connected,[&]()
                     {
        qDebug() << "Connected to Server!";
        emit sigConSuccess(true);
    });//发出连接成功的信号


    QObject::connect(&m_socket, &QTcpSocket::readyRead,[&]()
                     {
        m_buffer.append(m_socket.readAll());
        QDataStream stream(&m_buffer, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_0);
        forever{
            if(!m_recv_pending)
            {// 说明之前接收的数据是完整的，或者第一次接收数据
                //当前buffer的长度小于 id，len字节长度，直接返回。数据不够
                if(m_buffer.size() < static_cast<int>(sizeof(quint16)*2)){
                    return ;
                }
                stream >> m_message_id >> m_message_len;
                m_buffer  = m_buffer.mid(sizeof(quint16)*2);
                qDebug() << "Message ID: " << m_message_id << ", length: " << m_message_len;
            }
            if(m_buffer.size()< m_message_len)
            {
                m_recv_pending = true;
                return  ;
            }
            m_recv_pending =false;
            QByteArray messageBody = m_buffer.mid(0, m_message_len);
            qDebug() << "receive body msg is " << messageBody;

            m_buffer = m_buffer.mid(m_message_len);
            qDebug() << "m_message_id " << m_message_id;
            handleMsg(ReqId(m_message_id), m_message_len, messageBody);
        }
    });
    QObject::connect(&m_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),[&](QAbstractSocket::SocketError socketErr)
    {
        Q_UNUSED(socketErr)
        {
            qDebug() << "Error: " << m_socket.errorString();
        }
    });
    QObject::connect(&m_socket, &QTcpSocket::disconnected,[&]()
                     {
        qDebug() << "Disconnected from server";
    });
    QObject::connect(this, &TcpMgr::sigSendData,this, &TcpMgr::slotSendData);
    initHandlers();
}

void TcpMgr::slotSendData(ReqId reqId, QByteArray data)
{
    uint16_t id = reqId;
    // QByteArray dataBytes = data.toUtf8();
    quint16 len = static_cast<quint16>(data.size());
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::BigEndian);
    out << id << len;
    block.append(data);
    m_socket.write(block);
}

TcpMgr::~TcpMgr()
{

}

void TcpMgr::initHandlers()
{
    _handlers.insert(ReqId::ID_CHAT_LOGIN_RSP, [this](ReqId id, int len, QByteArray data)
    {
        qDebug()  << "inside handlers";
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if(jsonDoc.isNull())
        {
            qDebug() << "Failed to create JsonDoc";
            return ;
        }

        QJsonObject jsonObj = jsonDoc.object();
        if(!jsonObj.contains("error"))
            {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Login Failed, Parse Json file Failed! " << err;
            emit sigLoginFailed(err);
            return ;
        }
        int err = jsonObj["error"].toInt();
        if(err!=ErrorCodes::SUCCESS)
            {
            qDebug() << "Login Failed,";
            emit sigLoginFailed(err);
            return ;
        }
        auto uid = jsonObj["uid"].toInt();
        auto name = jsonObj["name"].toString();
        auto nick = jsonObj["nick"].toString();
        auto icon = jsonObj["icon"].toString();
        auto sex = jsonObj["sex"].toInt();
        qDebug() << "while login: uid: " << uid << ", name: " << name
                 << ", nick: " << nick << ", icon: " << icon << ", sex: " << sex;
        auto user_info = std::make_shared<UserInfo>(uid, name, nick, icon, sex);
        UserMgr::GetInstance()->SetUserInfo(user_info);
        UserMgr::GetInstance()->SetToken(jsonObj["token"].toString());
        if(jsonObj.contains("apply_list"))
            {
            UserMgr::GetInstance()->AppendApplyList(jsonObj["apply_list"].toArray());
        }

        // 加载好友列表
        if(jsonObj.contains("friend_list"))
        {
            UserMgr::GetInstance()->AppendFriendList(jsonObj["friend_list"].toArray());
        }
        qDebug() << jsonObj["name"].toString();
        qDebug() << jsonObj["token"].toString();
        qDebug() << jsonObj["uid"].toString();
        emit sigSwitchChatDlg();
    });
    _handlers.insert(ReqId::ID_SEARCH_USER_RSP, [this](ReqId id, int len, QByteArray data)
     {
        qDebug()  << "inside handlers";
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if(jsonDoc.isNull())
        {
            qDebug() << "Failed to create JsonDoc";
            return ;
        }

        QJsonObject jsonObj = jsonDoc.object();
        if(!jsonObj.contains("error"))
        {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "ID_SEARCH_USER_RSP Failed, Parse Json file Failed! " << err;
            emit sigUserSearch(nullptr);
            return ;
        }
        int err = jsonObj["error"].toInt();
        if(err!=ErrorCodes::SUCCESS)
        {
            qDebug() << "ID_SEARCH_USER_RSP Failed,";
            emit sigUserSearch(nullptr);
            return ;
        }
        auto search_info = std::make_shared<SearchInfo>(jsonObj["uid"].toInt(),
                                                        jsonObj["name"].toString(),
                                                        jsonObj["nick"].toString(),
                                                        jsonObj["desc"].toString(),
                                                        jsonObj["sex"].toInt(),
                                                        jsonObj["icon"].toString()
                                                        );
        emit sigUserSearch(search_info);
     });
    _handlers.insert(ReqId::ID_ADD_FRIEND_RSP, [this](ReqId id, int len, QByteArray data)
    {
        qDebug()  << "inside handlers";
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if(jsonDoc.isNull())
        {
            qDebug() << "Failed to create JsonDoc";
            return ;
        }

        QJsonObject jsonObj = jsonDoc.object();
        if(!jsonObj.contains("error"))
        {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "ID_ADD_FRIEND_RSP Failed, Parse Json file Failed! " << err;
            return ;
        }
        int err = jsonObj["error"].toInt();
        if(err!=ErrorCodes::SUCCESS)
        {
            qDebug() << "ID_ADD_FRIEND_RSP Failed,";
            return ;
        }
        qDebug() << "Add friend req success";
    });
    _handlers.insert(ReqId::ID_NOTIFY_ADD_FRIEND_REQ, [this](ReqId id, int len, QByteArray data)
    {
        qDebug()  << "inside handlers";
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if(jsonDoc.isNull())
        {
            qDebug() << "Failed to create JsonDoc";
            return ;
        }

        QJsonObject jsonObj = jsonDoc.object();
        if(!jsonObj.contains("error"))
        {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "ID_NOTIFY_ADD_FRIEND_REQ Failed, Parse Json file Failed! " << err;
            return ;
        }
        int err = jsonObj["error"].toInt();
        if(err!=ErrorCodes::SUCCESS)
        {
            qDebug() << "ID_NOTIFY_ADD_FRIEND_REQ Failed,";
            return ;
        }
        int from_uid = jsonObj["applyuid"].toInt();
        QString name = jsonObj["name"].toString();
        QString desc = jsonObj["desc"].toString();
        QString icon = jsonObj["icon"].toString();
        QString nick = jsonObj["nick"].toString();
        int sex = jsonObj["sex"].toInt();
        auto apply_info = std::make_shared<AddFriendApply>(from_uid, name,desc,icon,nick,sex);
        qDebug() << "ID_NOTIFY_ADD_FRIEND_REQ success" << "from uid: " << from_uid << " name: " << name
                 <<" desc: " << desc <<" icon: " <<icon << " nick: " << nick;
        emit sig_friend_apply(apply_info);
    });
    _handlers.insert(ReqId::ID_NOTIFY_AUTH_FRIEND_REQ, [this](ReqId id, int len, QByteArray data)
    {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();
        if (!jsonObj.contains("error")) {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Auth Friend Failed, err is " << err;
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != ErrorCodes::SUCCESS) {
            qDebug() << "Auth Friend Failed, err is " << err;
            return;
        }

        int from_uid = jsonObj["fromuid"].toInt();
        QString name = jsonObj["name"].toString();
        QString nick = jsonObj["nick"].toString();
        QString icon = jsonObj["icon"].toString();
        int sex = jsonObj["sex"].toInt();

        auto auth_info = std::make_shared<AuthInfo>(from_uid,name,
                                                    nick, icon, sex);

        emit sig_add_auth_friend(auth_info);
    });
    _handlers.insert(ID_AUTH_FRIEND_RSP, [this](ReqId id, int len, QByteArray data) {
        Q_UNUSED(len);
        qDebug() << "handle id is " << id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to create QJsonDocument.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("error")) {
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "Auth Friend Failed, err is Json Parse Err" << err;
            return;
        }

        int err = jsonObj["error"].toInt();
        if (err != ErrorCodes::SUCCESS) {
            qDebug() << "Auth Friend Failed, err is " << err;
            return;
        }

        auto name = jsonObj["name"].toString();
        auto nick = jsonObj["nick"].toString();
        auto icon = jsonObj["icon"].toString();
        auto sex = jsonObj["sex"].toInt();
        auto uid = jsonObj["uid"].toInt();
        auto rsp = std::make_shared<AuthRsp>(uid, name, nick, icon, sex);
        emit sig_auth_rsp(rsp);

        qDebug() << "Auth Friend Success " ;
    });
}

void TcpMgr::handleMsg(ReqId id, int len, QByteArray data)
{
    auto find_iter = _handlers.find(id);
    qDebug() << "hanldeMsg() id: " << id;
    if(find_iter == _handlers.end())
    {
        qDebug() << "not found id[" << id << "]";
        return ;
    }
    find_iter.value()(id, len, data);
}

void TcpMgr::slotTcpConnect(ServerInfo si)
{
    qDebug() << "receive tcp connect signal" ;
    qDebug() << "Connecting to server..." ;
    m_host = si.Host;
    m_port = static_cast<uint16_t>(si.Port.toUInt());
    m_socket.connectToHost(si.Host,m_port);

}
