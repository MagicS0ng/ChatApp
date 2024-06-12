#ifndef TIMERBTN_H
#define TIMERBTN_H
#include <QPushButton>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>

class TimerBtn: public QPushButton
{
public:
    TimerBtn(QWidget *parent = nullptr);
    ~TimerBtn();
    void mouseReleaseEvent(QMouseEvent *e) override;
private:
    QTimer * m_timer;
    int m_counter;
};

#endif // TIMERBTN_H
