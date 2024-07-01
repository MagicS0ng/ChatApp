#include "customtextedit.h"

CustomTextEdit::CustomTextEdit(QWidget * parent):QTextEdit(parent)
{

}

void CustomTextEdit::focusOutEvent(QFocusEvent *event)
{
        // 执行失去焦点时的处理逻辑
        //qDebug() << "CustomizeEdit focusout";
        // 调用基类的focusOutEvent()方法，保证基类的行为得到执行
        QTextEdit::focusOutEvent(event);
        //发送失去焦点得信号
        emit SigFoucusOut();
}

