#ifndef SETTINGSESSION_H
#define SETTINGSESSION_H

#include <QWidget>

namespace Ui {
class SettingSession;
}

class SettingSession : public QWidget
{
    Q_OBJECT
public:
    explicit SettingSession(QWidget* parent = nullptr);
    ~SettingSession() override;

private:
    Ui::SettingSession      *ui = nullptr;
};

#endif // SETTINGSESSION_H
