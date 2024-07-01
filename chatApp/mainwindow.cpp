#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "signupdialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),stackedWidget(new QStackedWidget(this))
{
    ui->setupUi(this);
    _login_dlg = new loginDialog(this);
    // _signup_dlg = new signupDialog(this);
    stackedWidget -> addWidget(_login_dlg);
    // stackedWidget -> addWidget(_signup_dlg);
    setCentralWidget(stackedWidget);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(_login_dlg, &loginDialog::switchToSignup, this, &MainWindow::SlotSwitchToSignup);
    stackedWidget->setCurrentWidget(_login_dlg);
    connect(_login_dlg, &loginDialog::switchToReset,this, &MainWindow::SlotSwitchToReset);
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sigSwitchChatDlg, this, &MainWindow::SlotSwitchToChat);
    emit TcpMgr::GetInstance()->sigSwitchChatDlg();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::SlotSwitchToSignup()
{
    _signup_dlg = new signupDialog(this);
    _signup_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    stackedWidget->addWidget(_signup_dlg);
    stackedWidget->setCurrentWidget(_signup_dlg);
    connect(_signup_dlg, &signupDialog::backToLogin, this, &MainWindow::SlotBackToLogin);
    // connect(_signup_dlg, &signupDialog::sigSwitchLogin, this, &MainWindow::SlotBackToLogin);
}
void MainWindow::SlotBackToLogin()
{
    stackedWidget->setCurrentWidget(_login_dlg);
}

void MainWindow::SlotSwitchToReset()
{
    _reset_dlg = new ResetDialog(this);
    _reset_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    stackedWidget->addWidget(_reset_dlg);
    // setCentralWidget(stackedWidget);
    // _login_dlg->hide();
    // _reset_dlg->show();
    stackedWidget->setCurrentWidget(_reset_dlg);
    connect(_reset_dlg, &ResetDialog::switchLogin, this, &MainWindow::SlotResetToLoginin);
}

void MainWindow::SlotResetToLoginin()
{
    stackedWidget->setCurrentWidget(_login_dlg);
}

void MainWindow::SlotSwitchToChat()
{
    _chat_dlg = new chatDialog(this);
    _chat_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    stackedWidget->addWidget(_chat_dlg);
    stackedWidget->setCurrentWidget(_chat_dlg);
    this->setMinimumSize(QSize(900,700));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}



