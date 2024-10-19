/********************************************************************************
** Form generated from reading UI file 'msgcards.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGCARDS_H
#define UI_MSGCARDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_msgCards
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *icon_widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *icon_lb;
    QWidget *friend_info_widget;
    QVBoxLayout *verticalLayout;
    QLabel *friend_id;
    QLabel *friend_msg;
    QWidget *time_widget;
    QLabel *time_lb;

    void setupUi(QWidget *msgCards)
    {
        if (msgCards->objectName().isEmpty())
            msgCards->setObjectName("msgCards");
        msgCards->resize(240, 70);
        msgCards->setMinimumSize(QSize(0, 70));
        msgCards->setMaximumSize(QSize(16777215, 70));
        horizontalLayout = new QHBoxLayout(msgCards);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 6, 2, 6);
        icon_widget = new QWidget(msgCards);
        icon_widget->setObjectName("icon_widget");
        icon_widget->setMinimumSize(QSize(50, 50));
        icon_widget->setMaximumSize(QSize(50, 50));
        horizontalLayout_2 = new QHBoxLayout(icon_widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        icon_lb = new QLabel(icon_widget);
        icon_lb->setObjectName("icon_lb");
        icon_lb->setMinimumSize(QSize(45, 45));
        icon_lb->setMaximumSize(QSize(45, 45));

        horizontalLayout_2->addWidget(icon_lb);


        horizontalLayout->addWidget(icon_widget);

        friend_info_widget = new QWidget(msgCards);
        friend_info_widget->setObjectName("friend_info_widget");
        verticalLayout = new QVBoxLayout(friend_info_widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        friend_id = new QLabel(friend_info_widget);
        friend_id->setObjectName("friend_id");

        verticalLayout->addWidget(friend_id);

        friend_msg = new QLabel(friend_info_widget);
        friend_msg->setObjectName("friend_msg");

        verticalLayout->addWidget(friend_msg);


        horizontalLayout->addWidget(friend_info_widget);

        time_widget = new QWidget(msgCards);
        time_widget->setObjectName("time_widget");
        time_widget->setMinimumSize(QSize(50, 50));
        time_widget->setMaximumSize(QSize(50, 50));
        time_lb = new QLabel(time_widget);
        time_lb->setObjectName("time_lb");
        time_lb->setGeometry(QRect(10, 20, 49, 16));
        time_lb->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(time_widget);


        retranslateUi(msgCards);

        QMetaObject::connectSlotsByName(msgCards);
    } // setupUi

    void retranslateUi(QWidget *msgCards)
    {
        msgCards->setWindowTitle(QCoreApplication::translate("msgCards", "Form", nullptr));
        icon_lb->setText(QCoreApplication::translate("msgCards", "TextLabel", nullptr));
        friend_id->setText(QCoreApplication::translate("msgCards", "C++", nullptr));
        friend_msg->setText(QCoreApplication::translate("msgCards", "Hello World!", nullptr));
        time_lb->setText(QCoreApplication::translate("msgCards", "10:55 pm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class msgCards: public Ui_msgCards {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGCARDS_H
