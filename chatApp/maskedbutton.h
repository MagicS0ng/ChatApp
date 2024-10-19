#ifndef MASKEDBUTTON_H
#define MASKEDBUTTON_H

#include <QPushButton>

class MaskedButton : public QPushButton
{
    Q_OBJECT
public:
    MaskedButton(QWidget * parent=nullptr);
    void SetIcon(const QString &);


};

#endif // MASKEDBUTTON_H
