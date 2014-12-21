#ifndef SETTINGSEPTEMBER_H
#define SETTINGSEPTEMBER_H

#include "settingcommon.h"
#include "settingsession.h"
#include "settingfontandcolor.h"
#include "settingediting.h"
#include <QDialog>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QString>
#include <functional>
#include <QSpacerItem>

#include <QtWidgets>

namespace Ui {
class SettingSeptember;
}

class SettingSeptember : public QDialog
{
    Q_OBJECT
public:
    explicit SettingSeptember(QWidget* parent = nullptr);
    ~SettingSeptember() override;

private slots:
    void selectSetting(QTreeWidgetItem* item);

private:
    Ui::SettingSeptember    *ui                     = nullptr;
    SettingCommon           *m_settingCommon        = nullptr;
    SettingSession          *m_settingSession       = new SettingSession;
    SettingFontAndColor     *m_settingFontAndColor  = new SettingFontAndColor;
    SettingEditing          *m_settingEditing       = new SettingEditing;
    QWidget                 *m_currentSetting       = nullptr;
    QSpacerItem             *m_spacerSetting        = nullptr;
};

#endif // SETTINGSEPTEMBER_H
