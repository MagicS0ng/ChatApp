QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS= favicon.ico
DESTDIR = ./bin

SOURCES += \
    adduseritem.cpp \
    applyfriend.cpp \
    applyfrienditem.cpp \
    applyfriendlist.cpp \
    applyfriendpage.cpp \
    authenfriend.cpp \
    bubbleframe.cpp \
    chatdialog.cpp \
    chatitembase.cpp \
    chatpage.cpp \
    chattingfriendslist.cpp \
    chattingview.cpp \
    clickedbtn.cpp \
    clickedlabel.cpp \
    clickedoncelabel.cpp \
    contactuserlist.cpp \
    conuseritem.cpp \
    customizededit.cpp \
    findfaileddlg.cpp \
    findsuccessdlg.cpp \
    friendlabel.cpp \
    global.cpp \
    grouptipitem.cpp \
    httpmgr.cpp \
    listbaseitem.cpp \
    loadingdlg.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    messagetextedit.cpp \
    msgcards.cpp \
    picturebubble.cpp \
    resetdialog.cpp \
    searchlist.cpp \
    signupdialog.cpp \
    statewidget.cpp \
    tcpmgr.cpp \
    textbubble.cpp \
    timerbtn.cpp \
    userdata.cpp \
    usermgr.cpp

HEADERS += \
    adduseritem.h \
    applyfriend.h \
    applyfrienditem.h \
    applyfriendlist.h \
    applyfriendpage.h \
    authenfriend.h \
    bubbleframe.h \
    chatdialog.h \
    chatitembase.h \
    chatpage.h \
    chattingfriendslist.h \
    chattingview.h \
    clickedbtn.h \
    clickedlabel.h \
    clickedoncelabel.h \
    contactuserlist.h \
    conuseritem.h \
    customizededit.h \
    findfaileddlg.h \
    findsuccessdlg.h \
    friendlabel.h \
    global.h \
    grouptipitem.h \
    httpmgr.h \
    listbaseitem.h \
    loadingdlg.h \
    logindialog.h \
    mainwindow.h \
    messagetextedit.h \
    msgcards.h \
    picturebubble.h \
    resetdialog.h \
    searchlist.h \
    signupdialog.h \
    singleton.h \
    statewidget.h \
    tcpmgr.h \
    textbubble.h \
    timerbtn.h \
    userdata.h \
    usermgr.h

FORMS += \
    adduseritem.ui \
    applyfriend.ui \
    applyfrienditem.ui \
    applyfriendpage.ui \
    authenfriend.ui \
    chatdialog.ui \
    chatpage.ui \
    conuseritem.ui \
    findfaileddlg.ui \
    findsuccessdlg.ui \
    friendlabel.ui \
    grouptipitem.ui \
    loadingdlg.ui \
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
CONFIG(debug, debug| release)
{
    OutputDir = $${OUT_PWD}/$${DESTDIR}
    OutputDir = $$replace(OutputDir,/,\\)
    static_dir = $${PWD}/static
    static_dir = $$replace(static_dir,/,\\)
    QMAKE_POST_LINK += xcopy /Y /E /I  \"$$static_dir\" \"$$OutputDir\\static\\\"
}
win32-msvc*:QMAKE_CXXFLAGS += /wd"4819" /utf-8
