#include "fontpage.h"

FontPage::FontPage(QWidget* parent) : QFontDialog(parent)
{
    this->setOption(QFontDialog::NoButtons);
}


