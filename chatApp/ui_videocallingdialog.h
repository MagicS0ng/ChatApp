/********************************************************************************
** Form generated from reading UI file 'videocallingdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOCALLINGDIALOG_H
#define UI_VIDEOCALLINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <maskedbutton.h>

QT_BEGIN_NAMESPACE

class Ui_VideoCallingDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *video_widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *local_video;
    QLabel *local_avatar;
    QSpacerItem *horizontalSpacer_3;
    QWidget *remote_video;
    QHBoxLayout *horizontalLayout_3;
    QLabel *remote_avatar;
    QSpacerItem *horizontalSpacer_2;
    QWidget *button_widget;
    QHBoxLayout *horizontalLayout_2;
    MaskedButton *toggle_audio_btn;
    MaskedButton *hang_up;
    MaskedButton *toggle_video_btn;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *VideoCallingDialog)
    {
        if (VideoCallingDialog->objectName().isEmpty())
            VideoCallingDialog->setObjectName("VideoCallingDialog");
        VideoCallingDialog->resize(796, 649);
        VideoCallingDialog->setMinimumSize(QSize(398, 649));
        VideoCallingDialog->setMaximumSize(QSize(796, 649));
        verticalLayout = new QVBoxLayout(VideoCallingDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 10);
        video_widget = new QWidget(VideoCallingDialog);
        video_widget->setObjectName("video_widget");
        horizontalLayout = new QHBoxLayout(video_widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(20, 10, 20, 0);
        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        local_video = new QWidget(video_widget);
        local_video->setObjectName("local_video");
        local_avatar = new QLabel(local_video);
        local_avatar->setObjectName("local_avatar");
        local_avatar->setGeometry(QRect(120, 220, 100, 100));
        local_avatar->setMinimumSize(QSize(100, 100));
        local_avatar->setMaximumSize(QSize(100, 100));

        horizontalLayout->addWidget(local_video);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        remote_video = new QWidget(video_widget);
        remote_video->setObjectName("remote_video");
        horizontalLayout_3 = new QHBoxLayout(remote_video);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        remote_avatar = new QLabel(remote_video);
        remote_avatar->setObjectName("remote_avatar");
        remote_avatar->setMinimumSize(QSize(100, 100));
        remote_avatar->setMaximumSize(QSize(100, 100));

        horizontalLayout_3->addWidget(remote_avatar);


        horizontalLayout->addWidget(remote_video);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(video_widget);

        button_widget = new QWidget(VideoCallingDialog);
        button_widget->setObjectName("button_widget");
        button_widget->setMinimumSize(QSize(0, 80));
        button_widget->setMaximumSize(QSize(16777215, 120));
        horizontalLayout_2 = new QHBoxLayout(button_widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        toggle_audio_btn = new MaskedButton(button_widget);
        toggle_audio_btn->setObjectName("toggle_audio_btn");
        toggle_audio_btn->setMinimumSize(QSize(80, 80));
        toggle_audio_btn->setMaximumSize(QSize(80, 80));

        horizontalLayout_2->addWidget(toggle_audio_btn);

        hang_up = new MaskedButton(button_widget);
        hang_up->setObjectName("hang_up");
        hang_up->setMinimumSize(QSize(80, 80));
        hang_up->setMaximumSize(QSize(80, 80));

        horizontalLayout_2->addWidget(hang_up);

        toggle_video_btn = new MaskedButton(button_widget);
        toggle_video_btn->setObjectName("toggle_video_btn");
        toggle_video_btn->setMinimumSize(QSize(80, 80));
        toggle_video_btn->setMaximumSize(QSize(80, 80));

        horizontalLayout_2->addWidget(toggle_video_btn);


        verticalLayout->addWidget(button_widget);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(VideoCallingDialog);

        QMetaObject::connectSlotsByName(VideoCallingDialog);
    } // setupUi

    void retranslateUi(QDialog *VideoCallingDialog)
    {
        VideoCallingDialog->setWindowTitle(QCoreApplication::translate("VideoCallingDialog", "Dialog", nullptr));
        local_avatar->setText(QString());
        remote_avatar->setText(QString());
        toggle_audio_btn->setText(QString());
        hang_up->setText(QString());
        toggle_video_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VideoCallingDialog: public Ui_VideoCallingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOCALLINGDIALOG_H
