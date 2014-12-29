#ifndef SETTINGFONTANDCOLOR_H
#define SETTINGFONTANDCOLOR_H

#include "setting/settingapp.h"
#include <QWidget>
#include <QColor>
#include <QPalette>
#include <QPushButton>
#include <QColorDialog>
#include <QFont>
#include <QPair>

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

    void writeBackgroundColor(const QColor& color);
    void writeCurrentLineColor(const QColor& color);
    void writeSearchTextColor(const QColor& color);
    void writeFontText(const QFont& font);
    void writeOtherQss(const QColor& color, QFont::Weight weight);
    void writePropertiesQss(const QColor& color, QFont::Weight weight);
    void writePseudoQss(const QColor& color, QFont::Weight weight);
    void writeSubQss(const QColor& color, QFont::Weight weight);
    void writeWidgetQss(const QColor& color, QFont::Weight weight);
    void writeCommentQss(const QColor& color, QFont::Weight weight);
    void writeNumberQss(const QColor& color, QFont::Weight weight);
    QColor backgroundColor();
    QColor currentLineColor();
    QColor searchTextColor();
    QFont fontText();
    void readSettingColor();
    void writeSettingColor();
    void readSettingQss();
    void writeSettingQss();
    QPair<QColor, QFont::Weight> otherQss();
    QPair<QColor, QFont::Weight> propertiesQss();
    QPair<QColor, QFont::Weight> pseudoQss();
    QPair<QColor, QFont::Weight> subQss();
    QPair<QColor, QFont::Weight> widgetQss();
    QPair<QColor, QFont::Weight> commentQss();
    QPair<QColor, QFont::Weight> numberQss();

private slots:
    void amendColorEdit();

private:
    Ui::SettingFontAndColor     *ui = nullptr;
    SettingApp                  *m_settingApp = SettingApp::instance();

    void addScheme();
};

#endif // SETTINGFONTANDCOLOR_H
