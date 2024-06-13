#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "logindialog.h"
#include "signupdialog.h"
#include "resetdialog.h"
#include "chatdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SlotSwitchToSignup();
    void SlotBackToLogin();
    void SlotSwitchToReset();
    void SlotResetToLoginin();
    void SlotSwitchToChat();
private:
    Ui::MainWindow *ui;
    loginDialog * _login_dlg;
    signupDialog * _signup_dlg;
    chatDialog * _chat_dlg;
    ResetDialog * _reset_dlg;
    QStackedWidget *stackedWidget;
};
#endif // MAINWINDOW_H
