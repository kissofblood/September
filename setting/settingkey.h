#ifndef SETTINGKEY_H
#define SETTINGKEY_H

#include <QDialog>

namespace Ui {
class SettingKey;
}

class SettingKey : public QDialog
{
    Q_OBJECT
public:
    explicit SettingKey(QWidget* parent = nullptr);
    ~SettingKey() override;

private:
    Ui::SettingKey *ui = nullptr;
};

#endif // SETTINGKEY_H
