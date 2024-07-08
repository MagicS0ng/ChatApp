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
            qDebug()<<"clicked, change to selected press: " << m_selected_hover;
            m_curstate = ClicklbState::Selected;
            setProperty("state", m_selected_press);
            repolish(this);
            update();
        }else
        {
            qDebug()<<"clicked, change to normal press: " << m_normal_hover;
            m_curstate = ClicklbState::Normal;
            setProperty("state", m_normal_press);
            repolish(this);
            update();
        }

        return ;
    }
    QLabel::mousePressEvent(ev);
}

void ClickedLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        if(m_curstate==ClicklbState::Normal)
        {
            qDebug() << "released, change to normal hover";
            setProperty("state",m_normal_hover);
            repolish(this);
            update();
        }else
        {
            qDebug() << "released,change to select hover";
            setProperty("state",m_selected_hover);
            repolish(this);
            update();
        }
        emit clicked(this->text(),m_curstate);
        return ;
    }
    QLabel::mouseReleaseEvent(ev);
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

bool ClickedLabel::SetCurState(ClicklbState state)
{
    m_curstate = state;
    if(m_curstate==ClicklbState::Normal)
    {
        setProperty("state", m_normal);
        repolish(this);
    }else if(m_curstate==ClicklbState::Selected)
    {
        setProperty("state", m_selected);
    }
    return true;
}

void ClickedLabel::ResetNormalState()
{
    m_curstate = ClicklbState::Normal;
    setProperty("state", m_normal);
    repolish(this);
}
