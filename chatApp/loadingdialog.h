#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>
#include <QMovie>

namespace Ui {
class loadingDialog;
}

class loadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loadingDialog(QWidget *parent = nullptr);
    ~loadingDialog();

private:
    Ui::loadingDialog *ui;
};

#endif // LOADINGDIALOG_H
