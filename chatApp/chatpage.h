#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();
protected:
    void paintEvent(QPaintEvent * event);
private:
    Ui::ChatPage *ui;
};

#endif // CHATPAGE_H