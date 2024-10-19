/********************************************************************************
** Form generated from reading UI file 'findfaileddlg.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDFAILEDDLG_H
#define UI_FINDFAILEDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedbtn.h>

QT_BEGIN_NAMESPACE

class Ui_FindFailedDlg
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *failed_tip;
    QLabel *tailed_tip2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    ClickedBtn *failed_sure_btn;

    void setupUi(QDialog *FindFailedDlg)
    {
        if (FindFailedDlg->objectName().isEmpty())
            FindFailedDlg->setObjectName("FindFailedDlg");
        FindFailedDlg->resize(260, 163);
        FindFailedDlg->setMinimumSize(QSize(260, 163));
        FindFailedDlg->setMaximumSize(QSize(260, 163));
        verticalLayout = new QVBoxLayout(FindFailedDlg);
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        failed_tip = new QLabel(FindFailedDlg);
        failed_tip->setObjectName("failed_tip");
        failed_tip->setMinimumSize(QSize(0, 25));
        failed_tip->setMaximumSize(QSize(16777215, 25));

        verticalLayout->addWidget(failed_tip);

        tailed_tip2 = new QLabel(FindFailedDlg);
        tailed_tip2->setObjectName("tailed_tip2");
        tailed_tip2->setMinimumSize(QSize(0, 25));
        tailed_tip2->setMaximumSize(QSize(16777215, 25));

        verticalLayout->addWidget(tailed_tip2);

        widget = new QWidget(FindFailedDlg);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        failed_sure_btn = new ClickedBtn(widget);
        failed_sure_btn->setObjectName("failed_sure_btn");
        failed_sure_btn->setMinimumSize(QSize(100, 30));
        failed_sure_btn->setMaximumSize(QSize(100, 30));

        horizontalLayout->addWidget(failed_sure_btn);


        verticalLayout->addWidget(widget);


        retranslateUi(FindFailedDlg);

        QMetaObject::connectSlotsByName(FindFailedDlg);
    } // setupUi

    void retranslateUi(QDialog *FindFailedDlg)
    {
        FindFailedDlg->setWindowTitle(QCoreApplication::translate("FindFailedDlg", "Dialog", nullptr));
        failed_tip->setText(QCoreApplication::translate("FindFailedDlg", "\346\227\240\346\263\225\346\211\276\345\210\260\350\257\245\347\224\250\346\210\267", nullptr));
        tailed_tip2->setText(QCoreApplication::translate("FindFailedDlg", "\350\257\267\347\241\256\350\256\244\344\277\241\346\201\257\346\255\243\347\241\256", nullptr));
        failed_sure_btn->setText(QCoreApplication::translate("FindFailedDlg", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindFailedDlg: public Ui_FindFailedDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDFAILEDDLG_H
