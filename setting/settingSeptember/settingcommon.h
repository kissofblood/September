#ifndef SETTINGCOMMON_H
#define SETTINGCOMMON_H

#include "setting/settingapp.h"
#include <QWidget>
#include <QCheckBox>

namespace Ui {
class SettingCommon;
}

class SettingCommon : public QWidget
{
    Q_OBJECT
public:
    explicit SettingCommon(QWidget* parent = nullptr);
    ~SettingCommon() override;

    bool getState() const;
    void writeState();

private slots:
    void setBool(int state);

private:
    Ui::SettingCommon   *ui             = nullptr;
    SettingApp          *m_settingApp   = SettingApp::instance();
    bool m_state;
};

#endif // SETTINGCOMMON_H
