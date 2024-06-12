#include "httpmgr.h"
#include "global.h"
HttpMgr::~HttpMgr()
{
}

HttpMgr::HttpMgr() {
    connect(this, &HttpMgr::sig_http_finish,this, &HttpMgr::slot_http_finish);

}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data =QJsonDocument(json).toJson(); // load json file into bytes
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    auto self = shared_from_this();
    // Sends the contents of the data byte array to the destination specified by request.
    QNetworkReply * reply = _manager.post(request, data);


    //QNetworkReply::finished void signal
    QObject::connect(reply, &QNetworkReply::finished,[self, reply, req_id, mod](){
        if(reply->error()!=QNetworkReply::NoError)
        {
            qDebug() << reply->errorString();
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return ;
        }
        QString res = reply->readAll();
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return ;
    });
}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if(mod==Modules::REGISTERMOD)
    {
        emit sig_reg_mod_finish(id, res, err, mod);
    }
    if(mod==Modules::RESETMOD)
    {
        emit sig_reset_mod_finish(id, res,err);
    }
    if(mod==Modules::LOGINMOD)
    {
        emit sig_login_mod_finish(id, res,err);
    }
}
