#ifndef STATELABEL_H
#define STATELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include "global.h"
class StateLabel : public QLabel
{
    Q_OBJECT
public:
    StateLabel(QWidget *parent=nullptr);
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent* event) override;
    void SetState(QString, QString, QString, QString, QString, QString);
    ClicklbState GetCurState();
    void ClearState();
    void SetSelected(bool bselected);
private:
    QString _normal;
    QString _normal_hover;
    QString _normal_press;

    QString _selected;
    QString _selected_hover;
    QString _selected_press;
    ClicklbState _curstate;
signals:
    void clicked(void);
};

#endif // STATELABEL_H
