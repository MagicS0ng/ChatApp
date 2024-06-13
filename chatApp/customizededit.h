#ifndef CUSTOMIZEDEDIT_H
#define CUSTOMIZEDEDIT_H
#include <QLineEdit>
#include <QDebug>
class CustomizedEdit: public QLineEdit
{
    Q_OBJECT
public:
    CustomizedEdit(QWidget *parent =nullptr);
    void SetMaxLength(int maxLen);
protected:
    void focusOutEvent(QFocusEvent *event) override;
private:
    void limitTextLength(QString text);
private:
    int m_max_len;
signals:
    void sigFocusOut();
};

#endif // CUSTOMIZEDEDIT_H
