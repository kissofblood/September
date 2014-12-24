#ifndef SETTINGSEPTEMBER_H
#define SETTINGSEPTEMBER_H

#include "settingSeptember/settingcommon.h"
#include "settingSeptember/settingsession.h"
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

#include <QDebug>

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
    bool containsKey();
    QColor readBackgroundColor();
    QColor readCurrentLineColor();
    QColor readSearchTextColor();
    QFont readFontText();
    void addValue();

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
    SettingSession          *m_settingSession       = new SettingSession;
    SettingFontAndColor     *m_settingFontAndColor  = new SettingFontAndColor;
    SettingEditing          *m_settingEditing       = new SettingEditing;
    QWidget                 *m_currentSetting       = nullptr;
    QSpacerItem             *m_spacerSetting        = nullptr;
};

#endif // SETTINGSEPTEMBER_H
