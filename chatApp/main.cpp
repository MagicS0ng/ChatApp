// @file    main.cpp
// @brief   主窗口
// @date    2024/05/25
#include "mainwindow.h"
#include <QStyleFactory>
#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/styles/stylesheet.qss");
    if(qss.open(QFile::ReadOnly))
    {
        qDebug("Open Successed");
        QTextStream ts(&qss);
        QString style = ts.readAll();
        a.setStyleSheet(style);
        qss.close();
    }else {
        qDebug("Open Failed!");
    }

    a.setStyle(QStyleFactory::create("Macintosh"));
    MainWindow w;
    w.show();
    return a.exec();
}
