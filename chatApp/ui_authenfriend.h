/********************************************************************************
** Form generated from reading UI file 'authenfriend.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHENFRIEND_H
#define UI_AUTHENFRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedbtn.h>
#include <clickedoncelabel.h>
#include <customizededit.h>

QT_BEGIN_NAMESPACE

class Ui_AuthenFriend
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollContent;
    QVBoxLayout *verticalLayout_2;
    QLabel *apply_lb;
    QFrame *line;
    QWidget *apply_wid;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLineEdit *back_ed;
    QLabel *label_3;
    QWidget *lb_group;
    QVBoxLayout *verticalLayout_4;
    QWidget *gridWidget;
    CustomizedEdit *lb_ed;
    QWidget *input_tip_wid;
    QVBoxLayout *verticalLayout_5;
    ClickedOnceLabel *tip_lb;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *lb_list;
    QWidget *more_lb_wid;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_4;
    ClickedOnceLabel *more_lb;
    QSpacerItem *verticalSpacer_3;
    QFrame *line_2;
    QSpacerItem *verticalSpacer;
    QWidget *apply_sure_wid;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    ClickedBtn *sure_btn;
    QSpacerItem *horizontalSpacer;
    ClickedBtn *cancel_btn;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *AuthenFriend)
    {
        if (AuthenFriend->objectName().isEmpty())
            AuthenFriend->setObjectName("AuthenFriend");
        AuthenFriend->resize(361, 621);
        AuthenFriend->setMinimumSize(QSize(361, 621));
        AuthenFriend->setMaximumSize(QSize(361, 621));
        verticalLayout = new QVBoxLayout(AuthenFriend);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(AuthenFriend);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setMinimumSize(QSize(0, 500));
        scrollArea->setWidgetResizable(true);
        scrollContent = new QWidget();
        scrollContent->setObjectName("scrollContent");
        scrollContent->setGeometry(QRect(0, 0, 359, 498));
        verticalLayout_2 = new QVBoxLayout(scrollContent);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 11, 0, 11);
        apply_lb = new QLabel(scrollContent);
        apply_lb->setObjectName("apply_lb");
        apply_lb->setMinimumSize(QSize(0, 25));
        apply_lb->setMaximumSize(QSize(16777215, 25));
        apply_lb->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(apply_lb);

        line = new QFrame(scrollContent);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line);

        apply_wid = new QWidget(scrollContent);
        apply_wid->setObjectName("apply_wid");
        verticalLayout_3 = new QVBoxLayout(apply_wid);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(apply_wid);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 25));
        label_2->setMaximumSize(QSize(16777215, 25));

        verticalLayout_3->addWidget(label_2);

        back_ed = new QLineEdit(apply_wid);
        back_ed->setObjectName("back_ed");
        back_ed->setMinimumSize(QSize(0, 35));

        verticalLayout_3->addWidget(back_ed);

        label_3 = new QLabel(apply_wid);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(0, 25));
        label_3->setMaximumSize(QSize(16777215, 25));

        verticalLayout_3->addWidget(label_3);

        lb_group = new QWidget(apply_wid);
        lb_group->setObjectName("lb_group");
        lb_group->setMinimumSize(QSize(0, 50));
        verticalLayout_4 = new QVBoxLayout(lb_group);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        gridWidget = new QWidget(lb_group);
        gridWidget->setObjectName("gridWidget");
        gridWidget->setMinimumSize(QSize(0, 40));
        gridWidget->setMaximumSize(QSize(16777215, 40));
        lb_ed = new CustomizedEdit(gridWidget);
        lb_ed->setObjectName("lb_ed");
        lb_ed->setGeometry(QRect(2, 2, 108, 35));
        lb_ed->setMaximumSize(QSize(16777215, 35));

        verticalLayout_4->addWidget(gridWidget);

        input_tip_wid = new QWidget(lb_group);
        input_tip_wid->setObjectName("input_tip_wid");
        input_tip_wid->setMinimumSize(QSize(0, 35));
        input_tip_wid->setMaximumSize(QSize(16777215, 35));
        verticalLayout_5 = new QVBoxLayout(input_tip_wid);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        tip_lb = new ClickedOnceLabel(input_tip_wid);
        tip_lb->setObjectName("tip_lb");

        verticalLayout_5->addWidget(tip_lb);


        verticalLayout_4->addWidget(input_tip_wid);


        verticalLayout_3->addWidget(lb_group);

        widget = new QWidget(apply_wid);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 60));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(7);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lb_list = new QWidget(widget);
        lb_list->setObjectName("lb_list");
        lb_list->setMinimumSize(QSize(287, 50));
        lb_list->setMaximumSize(QSize(287, 16777215));

        horizontalLayout_2->addWidget(lb_list);

        more_lb_wid = new QWidget(widget);
        more_lb_wid->setObjectName("more_lb_wid");
        verticalLayout_6 = new QVBoxLayout(more_lb_wid);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);

        more_lb = new ClickedOnceLabel(more_lb_wid);
        more_lb->setObjectName("more_lb");
        more_lb->setMinimumSize(QSize(25, 25));
        more_lb->setMaximumSize(QSize(25, 25));

        verticalLayout_6->addWidget(more_lb);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);


        horizontalLayout_2->addWidget(more_lb_wid);


        verticalLayout_3->addWidget(widget);

        line_2 = new QFrame(apply_wid);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_2);


        verticalLayout_2->addWidget(apply_wid);

        scrollArea->setWidget(scrollContent);

        verticalLayout->addWidget(scrollArea);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        apply_sure_wid = new QWidget(AuthenFriend);
        apply_sure_wid->setObjectName("apply_sure_wid");
        apply_sure_wid->setMinimumSize(QSize(0, 50));
        horizontalLayout = new QHBoxLayout(apply_sure_wid);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        sure_btn = new ClickedBtn(apply_sure_wid);
        sure_btn->setObjectName("sure_btn");
        sure_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout->addWidget(sure_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancel_btn = new ClickedBtn(apply_sure_wid);
        cancel_btn->setObjectName("cancel_btn");
        cancel_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout->addWidget(cancel_btn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(apply_sure_wid);

        verticalSpacer_2 = new QSpacerItem(20, 55, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(AuthenFriend);

        QMetaObject::connectSlotsByName(AuthenFriend);
    } // setupUi

    void retranslateUi(QDialog *AuthenFriend)
    {
        AuthenFriend->setWindowTitle(QCoreApplication::translate("AuthenFriend", "Dialog", nullptr));
        apply_lb->setText(QCoreApplication::translate("AuthenFriend", "New Friends", nullptr));
        label_2->setText(QCoreApplication::translate("AuthenFriend", "alias:", nullptr));
        label_3->setText(QCoreApplication::translate("AuthenFriend", "tags", nullptr));
        tip_lb->setText(QCoreApplication::translate("AuthenFriend", "TextLabel", nullptr));
        more_lb->setText(QString());
        sure_btn->setText(QCoreApplication::translate("AuthenFriend", "Confirm", nullptr));
        cancel_btn->setText(QCoreApplication::translate("AuthenFriend", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthenFriend: public Ui_AuthenFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHENFRIEND_H
