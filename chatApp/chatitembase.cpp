#include "chatitembase.h"

ChatItemBase::ChatItemBase(ChatRole role, QWidget * parent ):QWidget(parent), m_role(role)
{
    m_pNameLb = new QLabel();
    m_pNameLb->setObjectName("chat_user_name");
    QFont font("Microsoft YaHei");
    font.setPointSize(9);
    m_pNameLb->setFont(font);
    m_pNameLb->setFixedHeight(20);

    m_pIconLb = new QLabel();
    m_pIconLb->setScaledContents(true);
    m_pIconLb->setFixedSize(42,42);

    m_pBubble = new QWidget();
    QGridLayout *pGLayout = new QGridLayout();
    pGLayout->setVerticalSpacing(3);
    pGLayout->setHorizontalSpacing(3);
    pGLayout->setContentsMargins(3,3,3,3);
    QSpacerItem *pSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    if(m_role==ChatRole::Self)
    {
        m_pNameLb->setContentsMargins(0,0,8,0);
        m_pNameLb->setAlignment(Qt::AlignRight);
        pGLayout->addWidget(m_pNameLb,0,1,1,1);
        pGLayout->addWidget(m_pIconLb,0,2,2,2,Qt::AlignTop);
        pGLayout->addItem(pSpacer, 1,0,1,1);
        pGLayout->addWidget(m_pBubble,1,1,1,1);
        pGLayout->setColumnStretch(0, 2);
        pGLayout->setColumnStretch(1, 3);
    }else
    {
        m_pNameLb->setContentsMargins(8,0,0,0);
        m_pNameLb->setAlignment(Qt::AlignLeft);
        pGLayout->addWidget(m_pIconLb,0,0,2,1,Qt::AlignTop);
        pGLayout->addWidget(m_pNameLb,0,1,1,1);
        pGLayout->addWidget(m_pBubble,1,1,1,1);
        pGLayout->addItem(pSpacer,2,2,1,1);
        pGLayout->setColumnStretch(1,3);
        pGLayout->setColumnStretch(2,2);
    }
    this->setLayout(pGLayout);
}
void ChatItemBase::setUserName(const QString &name)
{
    m_pNameLb->setText(name);
}
void ChatItemBase::setUserIcon(const QPixmap &icon)
{
    m_pIconLb->setPixmap(icon);
}
void ChatItemBase::setWidget(QWidget *w)
{
    QGridLayout * pGLayout = (qobject_cast<QGridLayout *>)(this->layout());
    pGLayout->replaceWidget(m_pBubble, w);
    delete m_pBubble;
    m_pBubble = w;
}
