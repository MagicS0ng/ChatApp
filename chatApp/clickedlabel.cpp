#include "clickedlabel.h"


ClickedLabel::ClickedLabel(QWidget *parent): QLabel(parent), m_curstate(ClicklbState::Normal)
{
    this->setCursor(Qt::PointingHandCursor);
}
void ClickedLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        if(m_curstate==ClicklbState::Normal)
        {
            qDebug()<<"clicked, change to selected hover: " << m_selected_hover;
            m_curstate = ClicklbState::Selected;
            setProperty("state", m_selected_hover);
            repolish(this);
            update();
        }else
        {
            qDebug()<<"clicked, change to normal hover: " << m_normal_hover;
            m_curstate = ClicklbState::Normal;
            setProperty("state", m_normal_hover);
            repolish(this);
            update();
        }
        emit clicked();
    }
    QLabel::mousePressEvent(ev);
}

void ClickedLabel::enterEvent(QEnterEvent *event)
{
    if(m_curstate==ClicklbState::Normal)
    {
        qDebug() << "enter, change to normal hover: " << m_normal_hover;
        setProperty("state", m_normal_hover);
        repolish(this);
        update();
    }
    else
    {
        qDebug() << "enter, change to selected hover: " << m_selected_hover;
        setProperty("state", m_selected_hover);
        repolish(this);
        update();
    }
    QLabel::enterEvent(event);
}

void ClickedLabel::leaveEvent(QEvent *event)
{
    if(m_curstate==ClicklbState::Normal)
    {
        qDebug() << "enter, change to normal hover: " << m_normal_hover;
        setProperty("state", m_normal);
        repolish(this);
        update();
    }
    else
    {
        qDebug() << "enter, change to selected hover: " << m_selected_hover;
        setProperty("state", m_selected);
        repolish(this);
        update();
    }
    QLabel::leaveEvent(event);
}
void ClickedLabel::SetState(QString normal, QString hover, QString press, QString select, QString select_hover, QString select_press)
{
    m_normal = normal;
    m_normal_hover = hover;
    m_normal_press = press;

    m_selected = select;
    m_selected_hover = select_hover;
    m_selected_press = select_press;

    setProperty("state", normal);
    repolish(this);
}

ClicklbState ClickedLabel::GetCurState()
{
    return m_curstate;
}
