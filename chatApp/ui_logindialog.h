/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "clickedlabel.h"

QT_BEGIN_NAMESPACE

class Ui_loginDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *avatar_label;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *username_layout;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *email_box;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *passwd_layout;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *passwd_box;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QLabel *err_label;
    QHBoxLayout *login_layout;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *signin_btn;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *resetPasswd_layout;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *signup_btn;
    QSpacerItem *horizontalSpacer_11;
    ClickedLabel *resetPasswd_label;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *loginDialog)
    {
        if (loginDialog->objectName().isEmpty())
            loginDialog->setObjectName("loginDialog");
        loginDialog->resize(380, 550);
        loginDialog->setMinimumSize(QSize(380, 550));
        loginDialog->setMaximumSize(QSize(380, 550));
        loginDialog->setSizeGripEnabled(false);
        verticalLayout_2 = new QVBoxLayout(loginDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        avatar_label = new QLabel(loginDialog);
        avatar_label->setObjectName("avatar_label");
        avatar_label->setMinimumSize(QSize(128, 128));
        avatar_label->setMaximumSize(QSize(128, 128));
        avatar_label->setScaledContents(true);

        horizontalLayout->addWidget(avatar_label);

        horizontalSpacer_2 = new QSpacerItem(150, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        username_layout = new QHBoxLayout();
        username_layout->setObjectName("username_layout");
        username_layout->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer_3 = new QSpacerItem(60, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        username_layout->addItem(horizontalSpacer_3);

        email_box = new QLineEdit(loginDialog);
        email_box->setObjectName("email_box");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(email_box->sizePolicy().hasHeightForWidth());
        email_box->setSizePolicy(sizePolicy);
        email_box->setMinimumSize(QSize(240, 30));
        email_box->setMaximumSize(QSize(240, 30));
        email_box->setMaxLength(200);
        email_box->setAlignment(Qt::AlignCenter);

        username_layout->addWidget(email_box);

        horizontalSpacer_4 = new QSpacerItem(60, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        username_layout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(username_layout);

        verticalSpacer_5 = new QSpacerItem(10, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        passwd_layout = new QHBoxLayout();
        passwd_layout->setObjectName("passwd_layout");
        horizontalSpacer_6 = new QSpacerItem(60, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        passwd_layout->addItem(horizontalSpacer_6);

        passwd_box = new QLineEdit(loginDialog);
        passwd_box->setObjectName("passwd_box");
        sizePolicy.setHeightForWidth(passwd_box->sizePolicy().hasHeightForWidth());
        passwd_box->setSizePolicy(sizePolicy);
        passwd_box->setMinimumSize(QSize(240, 30));
        passwd_box->setMaximumSize(QSize(240, 30));
        passwd_box->setAlignment(Qt::AlignCenter);

        passwd_layout->addWidget(passwd_box, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        horizontalSpacer_5 = new QSpacerItem(60, 10, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        passwd_layout->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(passwd_layout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(verticalSpacer_4);

        err_label = new QLabel(loginDialog);
        err_label->setObjectName("err_label");
        err_label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(err_label);

        login_layout = new QHBoxLayout();
        login_layout->setObjectName("login_layout");
        login_layout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        login_layout->addItem(horizontalSpacer_7);

        signin_btn = new QPushButton(loginDialog);
        signin_btn->setObjectName("signin_btn");
        signin_btn->setMinimumSize(QSize(60, 60));
        signin_btn->setMaximumSize(QSize(60, 60));
        signin_btn->setStyleSheet(QString::fromUtf8("border-color: red;\n"
"border-radius: 30px;"));

        login_layout->addWidget(signin_btn);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        login_layout->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(login_layout);

        resetPasswd_layout = new QHBoxLayout();
        resetPasswd_layout->setObjectName("resetPasswd_layout");
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        resetPasswd_layout->addItem(horizontalSpacer_8);

        signup_btn = new QPushButton(loginDialog);
        signup_btn->setObjectName("signup_btn");
        sizePolicy.setHeightForWidth(signup_btn->sizePolicy().hasHeightForWidth());
        signup_btn->setSizePolicy(sizePolicy);
        signup_btn->setMinimumSize(QSize(80, 30));
        signup_btn->setMaximumSize(QSize(80, 30));

        resetPasswd_layout->addWidget(signup_btn);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        resetPasswd_layout->addItem(horizontalSpacer_11);

        resetPasswd_label = new ClickedLabel(loginDialog);
        resetPasswd_label->setObjectName("resetPasswd_label");
        sizePolicy.setHeightForWidth(resetPasswd_label->sizePolicy().hasHeightForWidth());
        resetPasswd_label->setSizePolicy(sizePolicy);
        resetPasswd_label->setMinimumSize(QSize(80, 30));
        resetPasswd_label->setMaximumSize(QSize(80, 30));
        resetPasswd_label->setAlignment(Qt::AlignCenter);

        resetPasswd_layout->addWidget(resetPasswd_label);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        resetPasswd_layout->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(resetPasswd_layout);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_2);

        QWidget::setTabOrder(email_box, passwd_box);
        QWidget::setTabOrder(passwd_box, signin_btn);
        QWidget::setTabOrder(signin_btn, signup_btn);

        retranslateUi(loginDialog);

        QMetaObject::connectSlotsByName(loginDialog);
    } // setupUi

    void retranslateUi(QDialog *loginDialog)
    {
        loginDialog->setWindowTitle(QCoreApplication::translate("loginDialog", "Dialog", nullptr));
        avatar_label->setText(QString());
        email_box->setText(QString());
        email_box->setPlaceholderText(QCoreApplication::translate("loginDialog", "Email", nullptr));
        passwd_box->setPlaceholderText(QCoreApplication::translate("loginDialog", "Password", nullptr));
        err_label->setText(QString());
        signin_btn->setText(QCoreApplication::translate("loginDialog", "Sign in", nullptr));
        signup_btn->setText(QCoreApplication::translate("loginDialog", "Sign up", nullptr));
        resetPasswd_label->setText(QCoreApplication::translate("loginDialog", "Reset password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginDialog: public Ui_loginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
