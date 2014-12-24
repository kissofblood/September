#ifndef FONTPAGE_H
#define FONTPAGE_H

#include <QWidget>
#include <QFontDialog>

class FontPage : public QFontDialog
{
public:
    explicit FontPage(QWidget* parent = nullptr) : QFontDialog(parent)
    { this->setOption(QFontDialog::NoButtons); }
    ~FontPage() override = default;
};

#endif // FONTPAGE_H
