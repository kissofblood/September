#include "settingediting.h"
#include "ui_settingediting.h"

SettingEditing::SettingEditing(QWidget* parent) : QWidget(parent),
    ui(new Ui::SettingEditing)
{
    ui->setupUi(this);

    this->connect(ui->btnDefault, &QPushButton::clicked, this, [this]()
    {
        ui->spnIndent->setValue(m_settingApp->readDefualtWidthIndent());
        ui->spnTab->setValue(m_settingApp->readDefualtWidthTab());
    });
}

SettingEditing::~SettingEditing()
{ delete ui; }

void SettingEditing::writeWidthIndent(int indent)
{
    m_settingApp->writeWidthIndent(indent);
    m_settingApp->writeDefaultWidthIndent(indent);
    ui->spnIndent->setValue(indent);
}

void SettingEditing::writeWidthTab(int tab)
{
    m_settingApp->writeWidthTab(tab);
    m_settingApp->writeDefaultWidthTab(tab);
    ui->spnTab->setValue(tab);
}

int SettingEditing::widthTab()
{ return ui->spnTab->value(); }

int SettingEditing::widthIndent()
{ return ui->spnIndent->value(); }

void SettingEditing::writeSetting()
{
    m_settingApp->writeWidthIndent(widthIndent());
    m_settingApp->writeWidthTab(widthTab());
}

void SettingEditing::readSetting()
{
    ui->spnIndent->setValue(m_settingApp->readWidthIndent());
    ui->spnTab->setValue(m_settingApp->readWidthTab());
}
