/********************************************************************************
** Form generated from reading UI file 'chatpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATPAGE_H
#define UI_CHATPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <chattingview.h>
#include <clickedbtn.h>
#include <clickedlabel.h>
#include <messagetextedit.h>

QT_BEGIN_NAMESPACE

class Ui_ChatPage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *chat_window_widget;
    QVBoxLayout *verticalLayout_4;
    QWidget *title_widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *title_lb;
    QWidget *widget_2;
    ChattingView *chat_msg_list;
    QWidget *tool_widget;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    ClickedLabel *emoji_lb;
    QSpacerItem *horizontalSpacer_3;
    ClickedLabel *file_lb;
    QSpacerItem *horizontalSpacer_4;
    ClickedLabel *video_call_lb;
    QSpacerItem *horizontalSpacer;
    QWidget *msg_area_widget;
    QHBoxLayout *horizontalLayout_6;
    MessageTextEdit *chat_msg_box;
    QWidget *send_widget;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    ClickedBtn *recv_btn;
    QSpacerItem *horizontalSpacer_7;
    ClickedBtn *send_btn;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *ChatPage)
    {
        if (ChatPage->objectName().isEmpty())
            ChatPage->setObjectName("ChatPage");
        ChatPage->resize(795, 700);
        ChatPage->setMaximumSize(QSize(16777215, 700));
        verticalLayout = new QVBoxLayout(ChatPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        chat_window_widget = new QWidget(ChatPage);
        chat_window_widget->setObjectName("chat_window_widget");
        chat_window_widget->setMinimumSize(QSize(25, 25));
        chat_window_widget->setMaximumSize(QSize(16777215, 700));
        verticalLayout_4 = new QVBoxLayout(chat_window_widget);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        title_widget = new QWidget(chat_window_widget);
        title_widget->setObjectName("title_widget");
        title_widget->setMinimumSize(QSize(25, 25));
        title_widget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_3 = new QHBoxLayout(title_widget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(20, 0, 0, 0);
        title_lb = new QLabel(title_widget);
        title_lb->setObjectName("title_lb");
        title_lb->setMinimumSize(QSize(25, 25));

        horizontalLayout_3->addWidget(title_lb);

        widget_2 = new QWidget(title_widget);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(25, 25));

        horizontalLayout_3->addWidget(widget_2);


        verticalLayout_4->addWidget(title_widget);

        chat_msg_list = new ChattingView(chat_window_widget);
        chat_msg_list->setObjectName("chat_msg_list");
        chat_msg_list->setMinimumSize(QSize(25, 25));
        chat_msg_list->setMaximumSize(QSize(16777215, 300));

        verticalLayout_4->addWidget(chat_msg_list);

        tool_widget = new QWidget(chat_window_widget);
        tool_widget->setObjectName("tool_widget");
        tool_widget->setMinimumSize(QSize(25, 25));
        tool_widget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_4 = new QHBoxLayout(tool_widget);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        emoji_lb = new ClickedLabel(tool_widget);
        emoji_lb->setObjectName("emoji_lb");
        emoji_lb->setMinimumSize(QSize(25, 25));
        emoji_lb->setMaximumSize(QSize(25, 25));

        horizontalLayout_4->addWidget(emoji_lb);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        file_lb = new ClickedLabel(tool_widget);
        file_lb->setObjectName("file_lb");
        file_lb->setMinimumSize(QSize(25, 25));
        file_lb->setMaximumSize(QSize(25, 25));

        horizontalLayout_4->addWidget(file_lb);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        video_call_lb = new ClickedLabel(tool_widget);
        video_call_lb->setObjectName("video_call_lb");
        video_call_lb->setMinimumSize(QSize(25, 25));
        video_call_lb->setMaximumSize(QSize(25, 25));

        horizontalLayout_4->addWidget(video_call_lb);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_4->addWidget(tool_widget);

        msg_area_widget = new QWidget(chat_window_widget);
        msg_area_widget->setObjectName("msg_area_widget");
        msg_area_widget->setMinimumSize(QSize(25, 25));
        msg_area_widget->setMaximumSize(QSize(16777215, 240));
        horizontalLayout_6 = new QHBoxLayout(msg_area_widget);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        chat_msg_box = new MessageTextEdit(msg_area_widget);
        chat_msg_box->setObjectName("chat_msg_box");
        chat_msg_box->setMinimumSize(QSize(25, 25));
        chat_msg_box->setMaximumSize(QSize(16777215, 400));

        horizontalLayout_6->addWidget(chat_msg_box);


        verticalLayout_4->addWidget(msg_area_widget);

        send_widget = new QWidget(chat_window_widget);
        send_widget->setObjectName("send_widget");
        send_widget->setMinimumSize(QSize(25, 25));
        send_widget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_5 = new QHBoxLayout(send_widget);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        recv_btn = new ClickedBtn(send_widget);
        recv_btn->setObjectName("recv_btn");
        recv_btn->setMinimumSize(QSize(25, 25));
        recv_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout_5->addWidget(recv_btn);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        send_btn = new ClickedBtn(send_widget);
        send_btn->setObjectName("send_btn");
        send_btn->setMinimumSize(QSize(25, 25));
        send_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout_5->addWidget(send_btn);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout_4->addWidget(send_widget);


        verticalLayout->addWidget(chat_window_widget);


        retranslateUi(ChatPage);

        QMetaObject::connectSlotsByName(ChatPage);
    } // setupUi

    void retranslateUi(QWidget *ChatPage)
    {
        ChatPage->setWindowTitle(QCoreApplication::translate("ChatPage", "Form", nullptr));
        title_lb->setText(QCoreApplication::translate("ChatPage", "Today", nullptr));
        emoji_lb->setText(QString());
        file_lb->setText(QString());
        video_call_lb->setText(QString());
        recv_btn->setText(QCoreApplication::translate("ChatPage", "Receive", nullptr));
        send_btn->setText(QCoreApplication::translate("ChatPage", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatPage: public Ui_ChatPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATPAGE_H
