#include "statewidget.h"

StateWidget::StateWidget(QWidget *parent)
    : QWidget{parent}
{
    setCursor(Qt::PointingHandCursor);
    AddRedPoint();
}

void StateWidget::SetState(QString normal, QString hover, QString press, QString select, QString select_hover, QString select_press)
{
    _normal = normal;
    _normal_hover = hover;
    _normal_press = press;

    _selected = select;
    _selected_hover = select_hover;
    _selected_press = select_press;
    setProperty("state", normal);
    repolish(this);
}

ClicklbState StateWidget::GetCurState()
{
    return _curstate;
}

void StateWidget::ClearState()
{
    _curstate = ClicklbState::Normal;
    setProperty("state", _normal);
    repolish(this);
    update();
}

void StateWidget::SetSelected(bool is_selected)
{
    if(is_selected)
    {
        _curstate = ClicklbState::Selected;
        setProperty("state", _selected);
        repolish(this);
        update();
        return ;
    }
    _curstate = ClicklbState::Normal;
    setProperty("state", _normal);
    repolish(this);
    update();
    return ;
}

void StateWidget::AddRedPoint()
{
    _red_point = new QLabel();
    _red_point->setObjectName("red_point");
    QVBoxLayout * layout2 = new QVBoxLayout;
    _red_point->setAlignment(Qt::AlignCenter);
    layout2->addWidget(_red_point);
    layout2->setContentsMargins(0,0,0,0);
    this->setLayout(layout2);
    _red_point->setVisible(false);
}

void StateWidget::ShowRedPoint(bool show)
{
    _red_point->setVisible(show);
}

void StateWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    return ;
}

void StateWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(_curstate==ClicklbState::Selected)
        {
            qDebug() << "PressEvent, already to selected press: " << _selected_press;
            QWidget::mousePressEvent(event);
            return ;
        }
        if(_curstate==ClicklbState::Normal)
        {
            qDebug() << "PressEvent, change to selected press: " << _selected_press;
            _curstate = ClicklbState::Selected;
            setProperty("state", _selected_press);
            repolish(this);
            update();
        }
        return ;
    }
    QWidget::mousePressEvent(event);
}

void StateWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(_curstate==ClicklbState::Normal)
        {
            setProperty("state", _normal_hover);
            repolish(this);
            update();
        }
        else
        {
            setProperty("state", _selected_hover);
            repolish(this);
            update();
        }
        emit clicked();
        return ;
    }
    QWidget::mouseReleaseEvent(event);
}

void StateWidget::enterEvent(QEnterEvent *event)
{

    if(_curstate==ClicklbState::Normal)
    {
        setProperty("state", _normal_hover);
        repolish(this);
        update();
    }
    else
    {
        setProperty("state", _selected_hover);
        repolish(this);
        update();
    }
    QWidget::enterEvent(event);
}

void StateWidget::leaveEvent(QEvent *event)
{
    if(_curstate==ClicklbState::Normal)
    {
        setProperty("state", _normal);
        repolish(this);
        update();
    }
    else
    {
        setProperty("state", _selected);
        repolish(this);
        update();
    }
    QWidget::leaveEvent(event);
}
