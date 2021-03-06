#ifndef SETTINGSEPTEMBER_H
#define SETTINGSEPTEMBER_H

#include "settingSeptember/settingcommon.h"
#include "settingSeptember/settingfontandcolor.h"
#include "settingSeptember/settingediting.h"
#include "settingapp.h"
#include <QDialog>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QString>
#include <functional>
#include <QSpacerItem>
#include <QColor>
#include <QFont>

namespace Ui {
class SettingSeptember;
}

class SettingSeptember : public QDialog
{
    Q_OBJECT
private:
    explicit SettingSeptember(QWidget* parent = nullptr);
    ~SettingSeptember() override;

public:
    static SettingSeptember* instance(QWidget* parent = nullptr);
    void writeDefaultBackgroundColor(const QColor& background);
    void writeDefaultCurrentLineColor(const QColor& currentLine);
    void writeDefaultSearchTextColor(const QColor& searchText);
    void writeDefaultFontText(const QFont& font);
    void writeDefaultOtherQss(const QColor& color, QFont::Weight weight);
    void writeDefaultSubQss(const QColor& color, QFont::Weight weight);
    void writeDefaultWidgetQss(const QColor& color, QFont::Weight weight);
    void writeDefaultPseudoQss(const QColor& color, QFont::Weight weight);
    void writeDefaultPropertiesQss(const QColor& color, QFont::Weight weight);
    void writeDefaultCommentQss(const QColor& color, QFont::Weight weight);
    void writeDefaultNumberQss(const QColor& color, QFont::Weight weight);
    void writeDefaultWidthIndent(int indent);
    void writeDefaultWidthTab(int tab);
    bool containsKey();
    QColor readBackgroundColor();
    QColor readCurrentLineColor();
    QColor readSearchTextColor();
    QFont readFontText();
    QPair<QColor, QFont::Weight> readOtherQss();
    QPair<QColor, QFont::Weight> readSubQss();
    QPair<QColor, QFont::Weight> readWidgetQss();
    QPair<QColor, QFont::Weight> readPseudoQss();
    QPair<QColor, QFont::Weight> readPropertiesQss();
    QPair<QColor, QFont::Weight> readCommentQss();
    QPair<QColor, QFont::Weight> readNumberQss();
    int readWidthIndent();
    int readWidthTab();
    void addValueColor();
    void addValueQss();
    void addKey();
    void readScheme();
    void readSettingEditing();
    bool warningChangeFile();

signals:
    void settingSeptemberOK();

private slots:
    void selectSetting(QTreeWidgetItem* item);
    void writeSetting();

private:    
    static SettingSeptember *m_singleton;
    Ui::SettingSeptember    *ui                     = nullptr;
    SettingCommon           *m_settingCommon        = nullptr;
    SettingApp              *m_settingApp           = SettingApp::instance();
    SettingFontAndColor     *m_settingFontAndColor  = new SettingFontAndColor;
    SettingEditing          *m_settingEditing       = new SettingEditing;
    QWidget                 *m_currentSetting       = nullptr;
    QSpacerItem             *m_spacerSetting        = nullptr;
    bool                    m_removeSpacer          = false;

    void closeEvent(QCloseEvent* event) override;
};

#endif // SETTINGSEPTEMBER_H
