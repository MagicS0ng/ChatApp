#include "signupdialog.h"
#include "ui_signupdialog.h"
#include "global.h"
#include "httpmgr.h"
signupDialog::signupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signupDialog),m_countdown(5)
{
    ui->setupUi(this);
    ui->passwd_box->setEchoMode(QLineEdit::Password);
    ui->repeatPasswd_box->setEchoMode(QLineEdit::Password);
    ui->err_label->setProperty("state", "normal");
    repolish(ui->err_label);
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish,this,&signupDialog::slot_reg_mod_finish);
    connect(ui->back_btn, &QPushButton::clicked, this, &signupDialog::backToLogin);
    initHttpHandlers();
    ui->err_label->clear();
    connect(ui->userName_box, &QLineEdit::editingFinished,this,[this]()
    {
        checkUserValid();
    });
    connect(ui->email_box, &QLineEdit::editingFinished,this,[this]()
            {
                checkEmailValid();
            });
    connect(ui->passwd_box, &QLineEdit::editingFinished,this,[this]()
            {
                checkPasswdValid();
            });
    connect(ui->repeatPasswd_box, &QLineEdit::editingFinished,this,[this]()
            {
                checkPasswdRepeatValid();
            });
    connect(ui->securityCode_box, &QLineEdit::editingFinished,this,[this]()
            {
                checkVarifyValid();
            });
    connect(ui->pass_visible, &ClickedLabel::clicked,this,[this]()
            {
        if(ui->pass_visible->GetCurState()==ClicklbState::Selected)
        {
            ui->passwd_box->setEchoMode(QLineEdit::Normal);
            ui->repeatPasswd_box->setEchoMode(QLineEdit::Normal);
            return ;
        }
            ui->passwd_box->setEchoMode(QLineEdit::Password);
            ui->repeatPasswd_box->setEchoMode(QLineEdit::Password);
        return ;
    });
    connect(ui->passre_visible, &ClickedLabel::clicked,this,[this]()
            {
                if(ui->passre_visible->GetCurState()==ClicklbState::Selected)
                {
                    ui->passwd_box->setEchoMode(QLineEdit::Normal);
                    ui->repeatPasswd_box->setEchoMode(QLineEdit::Normal);
                    return ;
                }
                ui->passwd_box->setEchoMode(QLineEdit::Password);
                ui->repeatPasswd_box->setEchoMode(QLineEdit::Password);
                return ;
            });
    ui->pass_visible->setCursor(Qt::PointingHandCursor);
    ui->passre_visible->setCursor(Qt::PointingHandCursor);

    ui->pass_visible->SetState("unvisible", "unvisible_hover", "", "visible","visible_hover","");
    ui->passre_visible->SetState("unvisible", "unvisible_hover", "", "visible","visible_hover","");
    m_countdown_timer = new QTimer(this);
    connect(m_countdown_timer, &QTimer::timeout, [this]()
            {
        if(m_countdown==0){
            m_countdown_timer->stop();
            emit sigSwitchLogin();
            return ;
        }
        m_countdown--;
        auto str = QString("Sign up successfully, will back to login window in %1 s ").arg(m_countdown);
        ui->tip_lb->setText(str);
    });
}

signupDialog::~signupDialog()
{
    qDebug() << "Destruct Signup Dlg";
    delete ui;
}
void signupDialog::showErr(QString &errMsg)
{
    ui->err_label->setText(errMsg);
    ui->err_label->setProperty("state", "error");
    repolish(ui->err_label);
}
void signupDialog::showErr(QString &&errMsg)
{
    ui->err_label->setText(errMsg);
    ui->err_label->setProperty("state", "error");
    repolish(ui->err_label);
}



void signupDialog::on_securityCode_btn_clicked()
{
    QString errMsg;
    auto email = ui->email_box->text();
    if(email.isEmpty())
    {
        errMsg = "Email is Null!";
        showErr(errMsg);
        return ;
    }
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    bool match = regex.match(email).hasMatch();
    if(!match)
    {
        errMsg = email + " is not valid";
        showErr(errMsg);
        ui->err_label->setProperty("state", "error");
        repolish(ui->err_label);
    }
    if(match)
    {
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpMgr::GetInstance()->PostHttpReq(QUrl("http://localhost:8080/get_security_code"), //get_security_code
                                                       json_obj,ReqId::ID_GET_VERIFY_CODE, Modules::REGISTERMOD);
        errMsg = "Send Successfully, check your email!";
        showErr(errMsg);
        ui->err_label->setProperty("state", "great");
        // qDebug() << HttpMgr::GetInstance().use_count() << "";
        // repolish(ui->err_label);
    }
}

void signupDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err !=ErrorCodes::SUCCESS)
    {
        showErr(tr("Request Failure"));
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
        showErr(tr(""));
            return ;
    }

    _handlers[id](jsonDoc.object());
    return ;
}

void signupDialog::initHttpHandlers()
{
    _handlers.insert(ReqId::ID_GET_VERIFY_CODE,[this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error!=ErrorCodes::SUCCESS)
            {
            showErr(tr("Parameter Mismatch"));
            return;
        }
        auto email= jsonObj["email"].toString();
        showErr(tr("Verify Code has sent to your email."));
        qDebug() << "Email is " << email;
    });
    _handlers.insert(ReqId::ID_REG_USER,[this](QJsonObject jsonObj)
                     {
        int error=jsonObj["error"].toInt();
        if(error!=ErrorCodes::SUCCESS)
            {
            showErr(tr("Wrong Parameters"));
            return ;
        }
        auto email = jsonObj["email"].toString();
        showErr(tr("Sign up Successfully"));
        qDebug() << "user uid is " << jsonObj["uid"].toInt();
        qDebug() << "EMail is " << email;
        ChangeTipPage();
    });
}


void signupDialog::on_confirm_btn_clicked()
{
    bool b_name = ui->userName_box->text().isEmpty();
    bool b_email = ui->email_box->text().isEmpty();
    bool b_passwd = ui->passwd_box->text().isEmpty();
    bool b_repeatpasswd = ui->repeatPasswd_box->text().isEmpty();
    bool b_code = ui->securityCode_box->text().isEmpty();
    if(b_name)
    {
        showErr(tr("Name can not be NULL!"));
        return ;
    }
    if(b_email)
    {
        showErr(tr("Email can not be NULL!"));
        return ;
    }
    if(b_passwd)
    {
        showErr(tr("Password can not be NULL!"));
        return ;
    }
    if(b_repeatpasswd)
    {
        showErr(tr("Please repeat your password again!"));
        return ;
    }
    if(ui->repeatPasswd_box->text()!=ui->passwd_box->text())
    {
        showErr(tr("Password Mismatch!"));
        return ;
    }
    if(b_code)
    {
        showErr(tr("Security Code Can not be NULL!"));
        return ;
    }
    QJsonObject json_obj;
    json_obj["user"] = ui->userName_box->text();
    qDebug() << ui->userName_box->text();
    json_obj["email"] = ui->email_box->text();
    qDebug() << ui->email_box->text();
    json_obj["passwd"] = xorString(ui->passwd_box->text());
    qDebug() << ui->passwd_box->text();
    json_obj["passwdrepeat"] = xorString(ui->repeatPasswd_box->text());
    json_obj["varifycode"] = ui->securityCode_box->text();
    HttpMgr::GetInstance()->PostHttpReq(QUrl("http://localhost:8080/user_register"),json_obj,ReqId::ID_REG_USER, Modules::REGISTERMOD);



    // showErr(tr("Sign Up Successfully!"));
}
void signupDialog::AddTipErr(TipErr te, QString tips)
{
    m_tips_errs[te] = tips;
    showErr(tips);
}
void signupDialog::DelTipErr(TipErr te)
{
    m_tips_errs.remove(te);
    if(m_tips_errs.empty())
    {
        ui->err_label->clear();
        return ;
    }
    showErr(m_tips_errs.first());
}

void signupDialog::ChangeTipPage()
{
    m_countdown_timer->stop();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    m_countdown_timer->start(1000);
}


bool signupDialog::checkUserValid()
{
    if(ui->userName_box->text()=="")
    {
        AddTipErr(TipErr::TIP_USER_ERR,tr("User name can not be NULL!"));
        return false;
    }
    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}
bool signupDialog::checkEmailValid()
{
    auto email = ui->email_box->text();
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    bool match = regex.match(email).hasMatch();
    if(!match)
    {
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("Email is invald!"));
        return false;
    }
    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}
bool signupDialog::checkPasswdValid()
{
    auto pass = ui->passwd_box->text();
    auto passre = ui->repeatPasswd_box->text();
    if(pass.length()<8||pass.length()>15)
    {
        AddTipErr(TipErr::TIP_PWD_ERR,tr("password should be set with length within 8~15!"));
        return false;
    }
    QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,}$");
    bool match =regex.match(pass).hasMatch();
    if(!match)
    {
        AddTipErr(TipErr::TIP_PWD_ERR,tr("Should contain a lowercase Char, a uppercase Char, a number, a sign like '@' '$'"));
        return false;
    }
    DelTipErr(TipErr::TIP_PWD_ERR);
    if(pass!=passre)
    {
        AddTipErr(TipErr::TIP_PWDRE_ERR, tr("Password Mismatch!"));
        return false;
    }else{
        DelTipErr(TipErr::TIP_PWDRE_ERR);}
    return true;
}
bool signupDialog::checkPasswdRepeatValid()
{
    auto pass = ui->passwd_box->text();
    auto passre = ui->repeatPasswd_box->text();
    if(pass.length()<8||pass.length()>15)
    {
        AddTipErr(TipErr::TIP_PWD_ERR,tr("password should be set with length within 8~15!"));
        return false;
    }
    QRegularExpression regex("^(?=.*[0-9])(?=.*[a-zA-Z])(?=.*[!@#$%^&*])[a-zA-Z0-9!@#$%^&*]{8,15}$");
    bool match =regex.match(pass).hasMatch();
    if(!match)
    {
        AddTipErr(TipErr::TIP_PWD_ERR,tr("Contains illeagal characters!"));
        return false;
    }
    DelTipErr(TipErr::TIP_PWD_ERR);
    if(pass!=passre)
    {
        AddTipErr(TipErr::TIP_PWDRE_ERR, tr("Password Mismatch!"));
        return false;
    }else{
        DelTipErr(TipErr::TIP_PWDRE_ERR);}
    return true;
}
bool signupDialog::checkVarifyValid()
{
    auto securify_code = ui->securityCode_box->text();
    if(securify_code.isEmpty())
    {
        AddTipErr(TipErr::TIP_VARIFY_ERR, tr("Varify code can not be NULL!"));
        return false;
    }
    DelTipErr(TipErr::TIP_VARIFY_ERR);
    return true;
}

void signupDialog::on_return_btn_clicked()
{
    m_countdown_timer->stop();
    emit sigSwitchLogin();
}

