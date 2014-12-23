#ifndef SETTINGEDITING_H
#define SETTINGEDITING_H

#include <QWidget>

namespace Ui {
class SettingEditing;
}

class SettingEditing : public QWidget
{
    Q_OBJECT
public:
    explicit SettingEditing(QWidget* parent = nullptr);
    ~SettingEditing() override;

private:
    Ui::SettingEditing  *ui = nullptr;
};

#endif // SETTINGEDITING_H
