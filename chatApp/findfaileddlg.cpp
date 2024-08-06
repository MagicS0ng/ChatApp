#include "findfaileddlg.h"
#include "ui_findfaileddlg.h"

FindFailedDlg::FindFailedDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindFailedDlg)
{
    ui->setupUi(this);
    setWindowTitle("添加");
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setObjectName("FindFailedDlg");
    ui->failed_sure_btn->SetState("normal", "hover", "press");
    this->setModal(true);
}

FindFailedDlg::~FindFailedDlg()
{
    qDebug() << "FindFailedDlg destruct";
    delete ui;
}

void FindFailedDlg::on_failed_sure_btn_clicked()
{
    this->hide();
    this->deleteLater();
}
