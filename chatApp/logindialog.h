#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QPainterPath>
#include <QJsonObject>
#include "httpmgr.h"
#include "global.h"
#include "tcpmgr.h"
namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();
    QString buttontype;
private:
    void initHttpHandler();
    void initAvatar();
    bool checkUserValid();
    void showErr(QString &errMsg);
    void showErr(QString &&errMsg);
    bool checkPwdValid();
    bool enableBtn(bool);
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
private:
    Ui::loginDialog *ui;
    QMap<TipErr, QString> m_tips_errs;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    int m_uid;
    QString m_token;

signals:
    void switchToSignup();
    void switchToReset();
    void sig_connect_tcp(ServerInfo);
private slots:
    void on_signin_btn_clicked();
    void slotResetPwd();
    void slotLoginModFinish(ReqId id, QString res, ErrorCodes err);
    void slotLoginFailed(int);
    void slotTcpConFinished(bool isSuccess);
};

#endif // LOGINDIALOG_H
