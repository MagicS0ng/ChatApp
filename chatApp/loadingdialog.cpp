#include "loadingdialog.h"
#include "ui_loadingdialog.h"

loadingDialog::loadingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loadingDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint|Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(parent->size());
    QMovie *movie  = new QMovie(":/resourse/loading.gif");
    ui->loading_lb->setMovie(movie);
    movie->start();

}

loadingDialog::~loadingDialog()
{
    delete ui;
}
