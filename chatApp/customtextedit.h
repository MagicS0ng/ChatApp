#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H
#include <QTextEdit>

class CustomTextEdit: public QTextEdit
{
    Q_OBJECT
public:
    CustomTextEdit(QWidget * parent=nullptr);
protected:
    void focusOutEvent(QFocusEvent *event) override
        ;

signals:
    void SigFoucusOut();
};

#endif // CUSTOMTEXTEDIT_H
