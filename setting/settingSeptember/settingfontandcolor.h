#ifndef SETTINGFONTANDCOLOR_H
#define SETTINGFONTANDCOLOR_H

#include <QWidget>
#include <QColor>
#include <QPalette>
#include <QPushButton>
#include <QColorDialog>
#include <QFont>

#include <QDebug>

namespace Ui {
class SettingFontAndColor;
}

class SettingFontAndColor : public QWidget
{
    Q_OBJECT
public:
    explicit SettingFontAndColor(QWidget* parent = nullptr);
    ~SettingFontAndColor() override;

    void setBackgroundColor(const QColor& background);
    QColor backgroundColor();
    void setCurrentLineColor(const QColor& currentLine);
    QColor currentLineColor();
    void setSearchTextColor(const QColor& searchText);
    QColor searchTextColor();
    void setFontText(const QFont& font);
    QFont fontText();

private slots:
    void amendColorEdit();

private:
    Ui::SettingFontAndColor     *ui = nullptr;
};

#endif // SETTINGFONTANDCOLOR_H
