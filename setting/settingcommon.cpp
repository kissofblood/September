#include "settingcommon.h"
#include "ui_settingcommon.h"

SettingCommon::SettingCommon(QWidget* parent) : QWidget(parent),
    ui(new Ui::SettingCommon)
{
    ui->setupUi(this);
}

SettingCommon::~SettingCommon()
{
    delete ui;
}
