#include "maskedbutton.h"

MaskedButton::MaskedButton(QWidget *parent): QPushButton(parent) {}

void MaskedButton::SetIcon(const QString & icon)
{
    QIcon buttonIcon(icon);
    setIcon(buttonIcon);
    setIconSize(this->size()*0.6);
}
