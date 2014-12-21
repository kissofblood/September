#ifndef SETTINGFONTANDCOLOR_H
#define SETTINGFONTANDCOLOR_H

#include <QWidget>

namespace Ui {
class SettingFontAndColor;
}

class SettingFontAndColor : public QWidget
{
    Q_OBJECT
public:
    explicit SettingFontAndColor(QWidget* parent = nullptr);
    ~SettingFontAndColor() override;

private:
    Ui::SettingFontAndColor     *ui = nullptr;
};

#endif // SETTINGFONTANDCOLOR_H
