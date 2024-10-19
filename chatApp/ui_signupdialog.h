/********************************************************************************
** Form generated from reading UI file 'signupdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPDIALOG_H
#define UI_SIGNUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedlabel.h"
#include "timerbtn.h"

QT_BEGIN_NAMESPACE

class Ui_signupDialog
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QLabel *err_label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QLabel *userName_label;
    QLineEdit *userName_box;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *email_label;
    QLineEdit *email_box;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QLabel *passwd_label;
    QLineEdit *passwd_box;
    ClickedLabel *pass_visible;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_9;
    QLabel *repeatPasswd_label;
    QLineEdit *repeatPasswd_box;
    ClickedLabel *passre_visible;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_11;
    QLabel *securityCode_label;
    QLineEdit *securityCode_box;
    QSpacerItem *horizontalSpacer_19;
    TimerBtn *securityCode_btn;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *confirm_btn;
    QPushButton *cancel_btn;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *back_btn;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_3;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_15;
    QLabel *tip_lb;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_17;
    QPushButton *return_btn;
    QSpacerItem *horizontalSpacer_18;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QDialog *signupDialog)
    {
        if (signupDialog->objectName().isEmpty())
            signupDialog->setObjectName("signupDialog");
        signupDialog->resize(420, 500);
        signupDialog->setMinimumSize(QSize(380, 500));
        signupDialog->setMaximumSize(QSize(420, 500));
        verticalLayout = new QVBoxLayout(signupDialog);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        stackedWidget = new QStackedWidget(signupDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setMinimumSize(QSize(400, 480));
        stackedWidget->setMaximumSize(QSize(400, 480));
        page = new QWidget();
        page->setObjectName("page");
        page->setMinimumSize(QSize(400, 480));
        page->setMaximumSize(QSize(400, 480));
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_4);

        widget = new QWidget(page);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 30));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        err_label = new QLabel(widget);
        err_label->setObjectName("err_label");
        err_label->setMinimumSize(QSize(380, 30));
        err_label->setMaximumSize(QSize(380, 30));
        err_label->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(err_label);


        verticalLayout_3->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        userName_label = new QLabel(page);
        userName_label->setObjectName("userName_label");
        userName_label->setMinimumSize(QSize(50, 30));
        userName_label->setMaximumSize(QSize(50, 30));

        horizontalLayout->addWidget(userName_label);

        userName_box = new QLineEdit(page);
        userName_box->setObjectName("userName_box");
        userName_box->setMinimumSize(QSize(240, 30));
        userName_box->setMaximumSize(QSize(240, 30));
        userName_box->setMaxLength(180);

        horizontalLayout->addWidget(userName_box);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        email_label = new QLabel(page);
        email_label->setObjectName("email_label");
        email_label->setMinimumSize(QSize(50, 30));
        email_label->setMaximumSize(QSize(50, 30));

        horizontalLayout_2->addWidget(email_label);

        email_box = new QLineEdit(page);
        email_box->setObjectName("email_box");
        email_box->setMinimumSize(QSize(240, 30));
        email_box->setMaximumSize(QSize(240, 30));
        email_box->setMaxLength(180);

        horizontalLayout_2->addWidget(email_box);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        passwd_label = new QLabel(page);
        passwd_label->setObjectName("passwd_label");
        passwd_label->setMinimumSize(QSize(50, 30));
        passwd_label->setMaximumSize(QSize(50, 30));

        horizontalLayout_3->addWidget(passwd_label);

        passwd_box = new QLineEdit(page);
        passwd_box->setObjectName("passwd_box");
        passwd_box->setMinimumSize(QSize(240, 30));
        passwd_box->setMaximumSize(QSize(240, 30));
        passwd_box->setMaxLength(160);

        horizontalLayout_3->addWidget(passwd_box);

        pass_visible = new ClickedLabel(page);
        pass_visible->setObjectName("pass_visible");
        pass_visible->setMinimumSize(QSize(30, 30));
        pass_visible->setMaximumSize(QSize(30, 30));

        horizontalLayout_3->addWidget(pass_visible);

        horizontalSpacer_8 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_9 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        repeatPasswd_label = new QLabel(page);
        repeatPasswd_label->setObjectName("repeatPasswd_label");
        repeatPasswd_label->setMinimumSize(QSize(50, 30));
        repeatPasswd_label->setMaximumSize(QSize(50, 30));

        horizontalLayout_4->addWidget(repeatPasswd_label);

        repeatPasswd_box = new QLineEdit(page);
        repeatPasswd_box->setObjectName("repeatPasswd_box");
        repeatPasswd_box->setMinimumSize(QSize(240, 30));
        repeatPasswd_box->setMaximumSize(QSize(240, 30));
        repeatPasswd_box->setMaxLength(160);

        horizontalLayout_4->addWidget(repeatPasswd_box);

        passre_visible = new ClickedLabel(page);
        passre_visible->setObjectName("passre_visible");
        passre_visible->setMinimumSize(QSize(30, 30));
        passre_visible->setMaximumSize(QSize(30, 30));

        horizontalLayout_4->addWidget(passre_visible);

        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_11 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_11);

        securityCode_label = new QLabel(page);
        securityCode_label->setObjectName("securityCode_label");
        securityCode_label->setMinimumSize(QSize(85, 30));
        securityCode_label->setMaximumSize(QSize(85, 30));

        horizontalLayout_5->addWidget(securityCode_label);

        securityCode_box = new QLineEdit(page);
        securityCode_box->setObjectName("securityCode_box");
        securityCode_box->setMinimumSize(QSize(80, 30));
        securityCode_box->setMaximumSize(QSize(80, 30));

        horizontalLayout_5->addWidget(securityCode_box);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_19);

        securityCode_btn = new TimerBtn(page);
        securityCode_btn->setObjectName("securityCode_btn");
        securityCode_btn->setMinimumSize(QSize(60, 30));
        securityCode_btn->setMaximumSize(QSize(60, 30));

        horizontalLayout_5->addWidget(securityCode_btn);

        horizontalSpacer_12 = new QSpacerItem(60, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_12);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        confirm_btn = new QPushButton(page);
        confirm_btn->setObjectName("confirm_btn");
        confirm_btn->setMinimumSize(QSize(80, 30));
        confirm_btn->setMaximumSize(QSize(80, 30));

        horizontalLayout_6->addWidget(confirm_btn);

        cancel_btn = new QPushButton(page);
        cancel_btn->setObjectName("cancel_btn");
        cancel_btn->setMinimumSize(QSize(80, 30));
        cancel_btn->setMaximumSize(QSize(80, 30));

        horizontalLayout_6->addWidget(cancel_btn);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        back_btn = new QPushButton(page);
        back_btn->setObjectName("back_btn");
        back_btn->setMinimumSize(QSize(60, 60));
        back_btn->setMaximumSize(QSize(60, 60));

        horizontalLayout_7->addWidget(back_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        page_2->setMinimumSize(QSize(400, 0));
        page_2->setMaximumSize(QSize(400, 16777215));
        verticalLayout_5 = new QVBoxLayout(page_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_7);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_15);

        tip_lb = new QLabel(page_2);
        tip_lb->setObjectName("tip_lb");
        tip_lb->setMinimumSize(QSize(200, 30));
        tip_lb->setMaximumSize(QSize(200, 30));
        tip_lb->setAlignment(Qt::AlignCenter);
        tip_lb->setWordWrap(true);

        horizontalLayout_11->addWidget(tip_lb);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_16);


        verticalLayout_5->addLayout(horizontalLayout_11);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_13);

        label = new QLabel(page_2);
        label->setObjectName("label");
        label->setMinimumSize(QSize(130, 30));
        label->setMaximumSize(QSize(130, 30));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(label);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_14);


        verticalLayout_5->addLayout(horizontalLayout_10);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_17);

        return_btn = new QPushButton(page_2);
        return_btn->setObjectName("return_btn");
        return_btn->setMinimumSize(QSize(90, 30));
        return_btn->setMaximumSize(QSize(90, 30));

        horizontalLayout_8->addWidget(return_btn);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_18);


        verticalLayout_5->addLayout(horizontalLayout_8);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);

        stackedWidget->addWidget(page_2);

        verticalLayout_2->addWidget(stackedWidget);


        verticalLayout->addLayout(verticalLayout_2);


        retranslateUi(signupDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(signupDialog);
    } // setupUi

    void retranslateUi(QDialog *signupDialog)
    {
        signupDialog->setWindowTitle(QCoreApplication::translate("signupDialog", "Dialog", nullptr));
        err_label->setText(QCoreApplication::translate("signupDialog", "Error Message", nullptr));
        userName_label->setText(QCoreApplication::translate("signupDialog", "Name", nullptr));
        email_label->setText(QCoreApplication::translate("signupDialog", "Email", nullptr));
        passwd_label->setText(QCoreApplication::translate("signupDialog", "Password", nullptr));
        pass_visible->setText(QString());
        repeatPasswd_label->setText(QCoreApplication::translate("signupDialog", "Repeat", nullptr));
        passre_visible->setText(QString());
        securityCode_label->setText(QCoreApplication::translate("signupDialog", "Security Code", nullptr));
        securityCode_btn->setText(QCoreApplication::translate("signupDialog", "Send", nullptr));
        confirm_btn->setText(QCoreApplication::translate("signupDialog", "Confirm", nullptr));
        cancel_btn->setText(QCoreApplication::translate("signupDialog", "Cancel", nullptr));
        back_btn->setText(QCoreApplication::translate("signupDialog", "\342\206\220", nullptr));
        tip_lb->setText(QCoreApplication::translate("signupDialog", "Sign up successfully, will be back to login in window in 5s", nullptr));
        label->setText(QCoreApplication::translate("signupDialog", "Click to back to login in", nullptr));
        return_btn->setText(QCoreApplication::translate("signupDialog", "Back to login in", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signupDialog: public Ui_signupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPDIALOG_H
