#include "customizededit.h"

CustomizedEdit::CustomizedEdit(QWidget *parent):QLineEdit(parent),m_max_len(0)
{
    connect(this, &QLineEdit::textChanged, this, &CustomizedEdit::limitTextLength);
}

void CustomizedEdit::SetMaxLength(int maxLen)
{
    m_max_len = maxLen;
}

void CustomizedEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    emit sigFocusOut();
}

void CustomizedEdit::limitTextLength(QString text)
{
    if(m_max_len<=0)
    {
        return ;
    }
    QByteArray byteArray = text.toUtf8();
    if(byteArray.size() > m_max_len)
    {
        byteArray = byteArray.left(m_max_len);
        this->setText(QString::fromUtf8(byteArray));
    }
}
