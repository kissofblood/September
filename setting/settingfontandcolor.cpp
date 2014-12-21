#include "settingfontandcolor.h"
#include "ui_settingfontandcolor.h"

SettingFontAndColor::SettingFontAndColor(QWidget* parent) : QWidget(parent),
    ui(new Ui::SettingFontAndColor)
{
    ui->setupUi(this);
}

SettingFontAndColor::~SettingFontAndColor()
{
    delete ui;
}
