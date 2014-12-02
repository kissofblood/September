#include "settingkey.h"
#include "ui_settingkey.h"

SettingKey::SettingKey(QWidget* parent) : QDialog(parent),
    ui(new Ui::SettingKey)
{
    ui->setupUi(this);
    this->setWindowTitle("Настройка комбинаций клавиш -- September");
}

SettingKey::~SettingKey()
{
    delete ui;
}
