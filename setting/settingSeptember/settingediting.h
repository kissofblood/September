#ifndef SETTINGEDITING_H
#define SETTINGEDITING_H

#include "setting/settingapp.h"
#include <QWidget>
#include <QPushButton>

namespace Ui {
class SettingEditing;
}

class SettingEditing : public QWidget
{
    Q_OBJECT
public:
    explicit SettingEditing(QWidget* parent = nullptr);
    ~SettingEditing() override;

    void writeWidthIndent(int indent);
    void writeWidthTab(int tab);
    int widthTab();
    int widthIndent();
    void writeSetting();
    void readSetting();

private:
    Ui::SettingEditing  *ui             = nullptr;
    SettingApp          *m_settingApp   = SettingApp::instance();
};

#endif // SETTINGEDITING_H
