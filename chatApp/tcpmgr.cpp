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

void TcpMgr::slotSendData(ReqId reqId, QString data)
{
    uint16_t id = reqId;
    // QByteArray dataBytes = data.toUtf8();
    quint16 len = static_cast<quint16>(data.size());
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::BigEndian);
    out << id << len;
    block.append(data.toUtf8());
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
        UserMgr::GetInstance()->SetName(jsonObj["name"].toString());
        UserMgr::GetInstance()->SetName(jsonObj["token"].toString());
        UserMgr::GetInstance()->SetUid(jsonObj["uid"].toInt());
        qDebug() << jsonObj["name"].toString();
        qDebug() << jsonObj["token"].toString();
        qDebug() << jsonObj["uid"].toString();
        emit sigSwitchChatDlg();
    });
}

void TcpMgr::handleMsg(ReqId id, int len, QByteArray data)
{
    auto find_iter = _handlers.find(id);
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
