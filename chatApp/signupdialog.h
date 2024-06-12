#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H
#include "global.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class signupDialog;
}

class signupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit signupDialog(QWidget *parent = nullptr);
    ~signupDialog();
private slots:
    void on_securityCode_btn_clicked();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void on_confirm_btn_clicked();

    void on_return_btn_clicked();

signals:
    void backToLogin();
    void sigSwitchLogin();
private:
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    void ChangeTipPage();
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPasswdValid();
    bool checkPasswdRepeatValid();
    bool checkVarifyValid();
    void showErr(QString & str);
    void showErr(QString && str);
    void initHttpHandlers();
private:
    Ui::signupDialog *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    QMap<TipErr, QString>  m_tips_errs;
    QTimer * m_countdown_timer;
    int m_countdown;
};
#endif // SIGNUPDIALOG_H
