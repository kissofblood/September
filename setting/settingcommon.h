#ifndef SETTINGCOMMON_H
#define SETTINGCOMMON_H

#include <QWidget>

namespace Ui {
class SettingCommon;
}

class SettingCommon : public QWidget
{
    Q_OBJECT
public:
    explicit SettingCommon(QWidget* parent = nullptr);
    ~SettingCommon() override;

private:
    Ui::SettingCommon   *ui = nullptr;
};

#endif // SETTINGCOMMON_H
