#ifndef MESSAGETEXTEDIT_H
#define MESSAGETEXTEDIT_H
#include <QTextEdit>
#include <QObject>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QMimeType>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QPainter>
#include <QVector>
#include "global.h"
#include <QMessageBox>



class MessageTextEdit: public QTextEdit
{
    Q_OBJECT
public:
    explicit MessageTextEdit(QWidget *parent = nullptr);
    ~MessageTextEdit();
public:
    QVector<MsgInfo> getMsgList();
    void insertFileFromUrl(const QStringList &urls);

protected:
    void dragEnterEvent(QDragEnterEvent *ev) override;
    void dropEvent(QDropEvent *ev) override;
    void keyPressEvent(QKeyEvent *e) override;
private:
    void insertImages(const QString &url);
    void insertTextFile(const QString &url);
    bool canInsertFromMimeData(const QMimeData *source) const override;
    void insertFromMimeData(const QMimeData * source) override;
private:
    bool isImage(QString url);
    void insertMsgList(QVector<MsgInfo> &list, QString flag, QString text, QPixmap pix);

    QStringList getUrl(QString text);
    QPixmap getFileIconPixmap(const QString &url);
    QString getFileSize(qint64 size);
private slots:
    void textEditChanged();
signals:
    void send();
private:
    QVector<MsgInfo> m_msgList;
    QVector<MsgInfo> m_getMsgList;

};

#endif // MESSAGETEXTEDIT_H
