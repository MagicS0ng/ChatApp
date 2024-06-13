#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H
#include "global.h"
#include <QLabel>
#include <QMouseEvent>

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget *parent=nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void SetState(QString normal="", QString hover="", QString press="", QString select="", QString select_hover = "", QString select_press="");
    ClicklbState GetCurState();
private:
    QString m_normal;
    QString m_normal_hover;
    QString m_normal_press;
    QString m_selected;
    QString m_selected_hover;
    QString m_selected_press;
    ClicklbState m_curstate;
signals:
    void  clicked(void);

};

#endif // CLICKEDLABEL_H
