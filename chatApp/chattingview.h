#ifndef CHATTINGVIEW_H
#define CHATTINGVIEW_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <QTimer>
#include <QScrollBar>
#include <QEvent>
#include <QStyleOption>
#include <QPainter>
class ChattingView: public QWidget
{
    Q_OBJECT
public:
    ChattingView(QWidget * parent=Q_NULLPTR);
    void appendMsgBubble(QWidget *bubble);
    void prependMsgBubble(QWidget *bubble);
    void insertMsgBubble(QWidget* pre, QWidget* re );
    void removeAllItem();
protected:
    bool eventFilter(QObject *o, QEvent * e) override;
    void paintEvent(QPaintEvent *event) override;
private slots:
    void OnVScrollBarMoved(int, int);
private:
    void initStyleSheet();
private:
    QVBoxLayout *m_pVl;
    QScrollArea *m_pScrollArea;
    bool isAppended;

};

#endif // CHATTINGVIEW_H
