#include "settingkey.h"
#include "ui_settingkey.h"

SettingKey::SettingKey(QWidget* parent) : QDialog(parent),
    ui(new Ui::SettingKey)
{
    ui->setupUi(this);
    ui->grpScheme->setVisible(false);

    this->connect(ui->btnCancel,  &QPushButton::clicked, this, &QDialog::close);
    this->connect(ui->btnDetails, &QPushButton::clicked, this, &SettingKey::visibleGrpScheme);
    this->setWindowTitle("Настройка комбинаций клавиш -- September");
}

SettingKey::~SettingKey()
{ delete ui; }

void SettingKey::visibleGrpScheme()
{
    static bool visible = false;
    if(visible)
    {
        ui->grpScheme->setVisible(false);
        visible = false;
    }
    else
    {
        ui->grpScheme->setVisible(true);
        visible = true;
    }
}
