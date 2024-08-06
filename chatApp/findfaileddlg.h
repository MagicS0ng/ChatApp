#ifndef FINDFAILEDDLG_H
#define FINDFAILEDDLG_H

#include <QDialog>

namespace Ui {
class FindFailedDlg;
}

class FindFailedDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FindFailedDlg(QWidget *parent = nullptr);
    ~FindFailedDlg();

private slots:
    void on_failed_sure_btn_clicked();
private:
    Ui::FindFailedDlg *ui;
};

#endif // FINDFAILEDDLG_H
