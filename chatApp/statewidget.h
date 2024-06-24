#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>
#include "global.h"
class StateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StateWidget(QWidget *parent = nullptr);
    void SetState(QString,QString,QString,QString,QString,QString);
    ClicklbState GetCurState();
    void ClearState();
    void SetSelected(bool);
    void AddRedPoint();
    void ShowRedPoint(bool show=true);
protected:
    void paintEvent(QPaintEvent * event) override;

    virtual void mousePressEvent(QMouseEvent *event)override;
    virtual void mouseReleaseEvent(QMouseEvent *event)override;
    virtual void enterEvent(QEnterEvent *event)override;
    virtual void leaveEvent(QEvent *event)override;
private:
    QString _normal;
    QString _normal_hover;
    QString _normal_press;
    QString _selected;
    QString _selected_hover;
    QString _selected_press;
    ClicklbState _curstate;
    QLabel * _red_point;

signals:
    void clicked(void);

};

#endif // STATEWIDGET_H
