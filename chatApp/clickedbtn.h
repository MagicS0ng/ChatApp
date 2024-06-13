#ifndef CLICKEDBTN_H
#define CLICKEDBTN_H
#include "global.h"
#include <QPushButton>
class ClickedBtn: public QPushButton
{
    Q_OBJECT
public:
    ClickedBtn(QWidget * parent = nullptr);
    ~ClickedBtn();
    void SetState(QString normal, QString hover, QString press);
protected:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
private:
    QString m_normal;
    QString m_hover;
    QString m_press;

};

#endif // CLICKEDBTN_H
