QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS= favicon.ico
DESTDIR = ./bin

SOURCES += \
    chatdialog.cpp \
    chattingfriendslist.cpp \
    clickedbtn.cpp \
    clickedlabel.cpp \
    customizededit.cpp \
    global.cpp \
    httpmgr.cpp \
    listbaseitem.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    msgcards.cpp \
    resetdialog.cpp \
    signupdialog.cpp \
    tcpmgr.cpp \
    timerbtn.cpp \
    usermgr.cpp

HEADERS += \
    chatdialog.h \
    chattingfriendslist.h \
    clickedbtn.h \
    clickedlabel.h \
    customizededit.h \
    global.h \
    httpmgr.h \
    listbaseitem.h \
    logindialog.h \
    mainwindow.h \
    msgcards.h \
    resetdialog.h \
    signupdialog.h \
    singleton.h \
    tcpmgr.h \
    timerbtn.h \
    usermgr.h

FORMS += \
    chatdialog.ui \
    logindialog.ui \
    mainwindow.ui \
    msgcards.ui \
    resetdialog.ui \
    signupdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    userIcon.qrc

DISTFILES += \
    resourse/pass_invisibility.png \
    resourse/pass_visibility.png \
    resourse/unvisible.png \
    resourse/unvisible_hover.png \
    resourse/visible.png \
    resourse/visible_hover.png
