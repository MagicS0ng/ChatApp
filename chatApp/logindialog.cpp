#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    connect(ui->signup_btn, &QPushButton::clicked, this, &loginDialog::switchToSignup);
    ui->resetPasswd_label->SetState("normal", "hover","","selected", "selected_hover");
    ui->resetPasswd_label->setCursor(Qt::PointingHandCursor);
    connect(ui->resetPasswd_label,&ClickedLabel::clicked, this, &loginDialog::slotResetPwd);
    ui->passwd_box->setEchoMode(QLineEdit::Password);
    initAvatar();
    initHttpHandler();
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish, this,
            &loginDialog::slotLoginModFinish);
    connect(this, &loginDialog::sig_connect_tcp, TcpMgr::GetInstance().get(), &TcpMgr::slotTcpConnect);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sigConSuccess, this, &loginDialog::slotTcpConFinished);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sigLoginFailed, this, &loginDialog::slotLoginFailed);
}

loginDialog::~loginDialog()
{
    qDebug() << "Destruct Login Dlg";
    delete ui;
}

void loginDialog::initHttpHandler()
{
    _handlers.insert(ReqId::ID_LOGIN_USER, [this](QJsonObject jsonObj){
        int err = jsonObj["error"].toInt();
        if(err!=ErrorCodes::SUCCESS)
        {
            showErr(tr("Wrong Parameters!"));
            enableBtn(true);
            return ;
        }
        auto email = jsonObj["email"].toString();
        ServerInfo si;
        si.Uid = jsonObj["uid"].toInt();
        si.Host = jsonObj["host"].toString();
        si.Port = jsonObj["port"].toString();
        si.Token = jsonObj["token"].toString();

        m_uid = si.Uid;
        m_token = si.Token;
        qDebug() << "while logining in, email is: " << email << " uid is: " << si.Uid << ", host is " <<
            si.Host << " port is: " << si.Port << " Token is: " << si.Token;
        emit sig_connect_tcp(si);

    });
}

void loginDialog::initAvatar()
{
    QPixmap defaultPixmap(":/duckduckgo-logo-png-19.png");
    qDebug() << defaultPixmap.size() << ui->avatar_label->size();
    defaultPixmap = defaultPixmap.scaled(ui->avatar_label->size(),
                                         Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap roundedPixmap(defaultPixmap.size());
    roundedPixmap.fill(Qt::transparent);
    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addRoundedRect(0,0,defaultPixmap.width(), defaultPixmap.height(),10,10);
    painter.setClipPath(path);
    painter.drawPixmap(0,0,defaultPixmap);
    ui->avatar_label->setPixmap(roundedPixmap);

}
void loginDialog::showErr(QString &errMsg)
{
    ui->err_label->setText(errMsg);
    ui->err_label->setProperty("state", "error");
    repolish(ui->err_label);
}
void loginDialog::showErr(QString &&errMsg)
{
    ui->err_label->setText(errMsg);
    ui->err_label->setProperty("state", "error");
    repolish(ui->err_label);
}

bool loginDialog::checkPwdValid()
{
    auto pass = ui->passwd_box->text();

    if(pass.length()<8||pass.length()>15)
    {
        AddTipErr(TipErr::TIP_PWD_ERR,tr("password should be set with length within 8~15!"));
        return false;
    }
    QRegularExpression regex("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match =regex.match(pass).hasMatch();
    if(!match)
    {
        AddTipErr(TipErr::TIP_PWD_ERR,tr("Should contain a lowercase Char, a uppercase Char, a number, a sign like '@' '$'"));
        return false;
    }
    DelTipErr(TipErr::TIP_PWD_ERR);

    return true;
}

bool loginDialog::enableBtn(bool enabled)
{
    ui->signin_btn->setEnabled(enabled);
    ui->signup_btn->setEnabled(enabled);
    return true;
}
void loginDialog::AddTipErr(TipErr te, QString tips)
{
    m_tips_errs[te] = tips;
    showErr(tips);
}
void loginDialog::DelTipErr(TipErr te)
{
    m_tips_errs.remove(te);
    if(m_tips_errs.empty())
    {
        ui->err_label->clear();
        return ;
    }
    showErr(m_tips_errs.first());
}
bool loginDialog::checkUserValid()
{
    auto email = ui->email_box->text();
    if(email.isEmpty())
    {
        qDebug() << "email empty";
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("Email can not be NULL"));
        return false;
    }
    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

void loginDialog::slotResetPwd()
{
    qDebug() << "slot reset pwd";
    emit switchToReset();
}

void loginDialog::slotLoginModFinish(ReqId id, QString res, ErrorCodes err)
{
    if(err!=ErrorCodes::SUCCESS)
    {
        showErr(tr("Request Failed"));
        return ;
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull())
    {
        showErr(tr("Parse Json Failed"));
        return ;
    }
    if(!jsonDoc.isObject())
    {
        showErr(tr("Parse Json Failed"));
        return ;
    }
    _handlers[id](jsonDoc.object());
    return ;
}

void loginDialog::slotLoginFailed(int err)
{
    QString result = QString("login failed, err is %1").arg(err);
    showErr(result);
    enableBtn(true);
}

void loginDialog::slotTcpConFinished(bool isSuccess)
{
    qDebug() << "slotTcpConFinished";
    if(isSuccess)
    {
        showErr(tr("login in in progress"));
        QJsonObject jsonObj;
        jsonObj["uid"] = m_uid;
        jsonObj["token"] = m_token;
        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
        emit TcpMgr::GetInstance()->sigSendData(ReqId::ID_CHAT_LOGIN, jsonString.toUtf8());
    }else
    {
        showErr(tr("Network Err"));
        enableBtn(true);
    }

}

void loginDialog::on_signin_btn_clicked()
{
    qDebug() << "login btn clicked";
    // if(!checkUserValid())
    //     return ;
    // if(!checkPwdValid())
    //     return ;
    enableBtn(false);
    auto email = ui->email_box->text();
    auto pwd = ui->passwd_box->text();
    QJsonObject jsonObj;
    jsonObj["email"] = email;
    jsonObj["passwd"] = xorString(pwd);
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_login"),
                                        jsonObj, ReqId::ID_LOGIN_USER,Modules::LOGINMOD
                                        );
}

