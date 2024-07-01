#ifndef MSGCARDS_H
#define MSGCARDS_H

#include "listbaseitem.h"

namespace Ui {
class msgCards;
}

class msgCards : public ListBaseItem
{
    Q_OBJECT

public:
    explicit msgCards(QWidget *parent = nullptr);
    ~msgCards();
    QSize sizeHint() const override;
    void SetInfo(QString name, QString avatar, QString msg);
    void ShowRedPoint(bool bshow);
private:
    Ui::msgCards *ui;
    QString m_name;
    QString m_avatar;
    QString m_msg;
};

#endif // MSGCARDS_H
