#ifndef SETTINGSEPTEMBER_H
#define SETTINGSEPTEMBER_H

#include <QDialog>

namespace Ui {
class SettingSeptember;
}

class SettingSeptember : public QDialog
{
    Q_OBJECT
public:
    explicit SettingSeptember(QWidget* parent = nullptr);
    ~SettingSeptember() override;

private:
    Ui::SettingSeptember *ui;
};

#endif // SETTINGSEPTEMBER_H
