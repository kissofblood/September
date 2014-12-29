#include "settingediting.h"
#include "ui_settingediting.h"

SettingEditing::SettingEditing(QWidget* parent) : QWidget(parent),
    ui(new Ui::SettingEditing)
{
    ui->setupUi(this);
}

SettingEditing::~SettingEditing()
{ delete ui; }
