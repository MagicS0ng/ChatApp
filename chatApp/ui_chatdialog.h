/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <applyfriendpage.h>
#include <chatpage.h>
#include <chattingfriendslist.h>
#include <clickedbtn.h>
#include <contactuserlist.h>
#include <customizededit.h>
#include <searchlist.h>
#include <statewidget.h>

QT_BEGIN_NAMESPACE

class Ui_chatDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *sidebar_widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *side_avat_lb;
    StateWidget *side_chat_wd;
    StateWidget *side_contact_wd;
    QSpacerItem *verticalSpacer;
    QWidget *chat_list_widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *search_widget;
    QHBoxLayout *horizontalLayout_2;
    CustomizedEdit *search_box;
    QSpacerItem *horizontalSpacer;
    ClickedBtn *add_btn;
    SearchList *search_candidates_list;
    ChattingFriendsList *chatting_friends_list;
    ContactUserList *contacts_list;
    QStackedWidget *stackedWidget;
    ChatPage *chat_page;
    ApplyFriendPage *friend_apply_page;

    void setupUi(QDialog *chatDialog)
    {
        if (chatDialog->objectName().isEmpty())
            chatDialog->setObjectName("chatDialog");
        chatDialog->resize(800, 700);
        chatDialog->setMinimumSize(QSize(800, 700));
        chatDialog->setMaximumSize(QSize(16777215, 700));
        horizontalLayout = new QHBoxLayout(chatDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sidebar_widget = new QWidget(chatDialog);
        sidebar_widget->setObjectName("sidebar_widget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sidebar_widget->sizePolicy().hasHeightForWidth());
        sidebar_widget->setSizePolicy(sizePolicy);
        sidebar_widget->setMinimumSize(QSize(56, 0));
        sidebar_widget->setMaximumSize(QSize(56, 700));
        verticalLayout = new QVBoxLayout(sidebar_widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 30, 0, 0);
        widget = new QWidget(sidebar_widget);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(16777215, 150));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(30);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 20, 0, 0);
        side_avat_lb = new QLabel(widget);
        side_avat_lb->setObjectName("side_avat_lb");
        side_avat_lb->setMinimumSize(QSize(35, 35));
        side_avat_lb->setMaximumSize(QSize(35, 35));

        verticalLayout_3->addWidget(side_avat_lb);

        side_chat_wd = new StateWidget(widget);
        side_chat_wd->setObjectName("side_chat_wd");
        side_chat_wd->setMinimumSize(QSize(30, 30));
        side_chat_wd->setMaximumSize(QSize(30, 30));

        verticalLayout_3->addWidget(side_chat_wd);

        side_contact_wd = new StateWidget(widget);
        side_contact_wd->setObjectName("side_contact_wd");
        side_contact_wd->setMinimumSize(QSize(30, 30));
        side_contact_wd->setMaximumSize(QSize(30, 30));

        verticalLayout_3->addWidget(side_contact_wd);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(sidebar_widget);

        chat_list_widget = new QWidget(chatDialog);
        chat_list_widget->setObjectName("chat_list_widget");
        chat_list_widget->setMinimumSize(QSize(240, 0));
        chat_list_widget->setMaximumSize(QSize(240, 700));
        verticalLayout_2 = new QVBoxLayout(chat_list_widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        search_widget = new QWidget(chat_list_widget);
        search_widget->setObjectName("search_widget");
        search_widget->setMinimumSize(QSize(0, 60));
        search_widget->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_2 = new QHBoxLayout(search_widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        search_box = new CustomizedEdit(search_widget);
        search_box->setObjectName("search_box");
        search_box->setMinimumSize(QSize(0, 20));
        search_box->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(search_box);

        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        add_btn = new ClickedBtn(search_widget);
        add_btn->setObjectName("add_btn");
        add_btn->setMinimumSize(QSize(20, 20));
        add_btn->setMaximumSize(QSize(20, 20));

        horizontalLayout_2->addWidget(add_btn);


        verticalLayout_2->addWidget(search_widget);

        search_candidates_list = new SearchList(chat_list_widget);
        search_candidates_list->setObjectName("search_candidates_list");
        search_candidates_list->setMaximumSize(QSize(16777215, 660));

        verticalLayout_2->addWidget(search_candidates_list);

        chatting_friends_list = new ChattingFriendsList(chat_list_widget);
        chatting_friends_list->setObjectName("chatting_friends_list");
        chatting_friends_list->setMaximumSize(QSize(16777215, 660));

        verticalLayout_2->addWidget(chatting_friends_list);

        contacts_list = new ContactUserList(chat_list_widget);
        contacts_list->setObjectName("contacts_list");
        contacts_list->setMaximumSize(QSize(16777215, 660));

        verticalLayout_2->addWidget(contacts_list);


        horizontalLayout->addWidget(chat_list_widget);

        stackedWidget = new QStackedWidget(chatDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setMaximumSize(QSize(16777215, 700));
        chat_page = new ChatPage();
        chat_page->setObjectName("chat_page");
        stackedWidget->addWidget(chat_page);
        friend_apply_page = new ApplyFriendPage();
        friend_apply_page->setObjectName("friend_apply_page");
        stackedWidget->addWidget(friend_apply_page);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(chatDialog);

        QMetaObject::connectSlotsByName(chatDialog);
    } // setupUi

    void retranslateUi(QDialog *chatDialog)
    {
        chatDialog->setWindowTitle(QCoreApplication::translate("chatDialog", "Dialog", nullptr));
        side_avat_lb->setText(QString());
        add_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class chatDialog: public Ui_chatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
