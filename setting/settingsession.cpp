#include "settingsession.h"
#include "ui_settingsession.h"

SettingSession::SettingSession(QWidget* parent) : QWidget(parent),
    ui(new Ui::SettingSession)
{
    ui->setupUi(this);
}

SettingSession::~SettingSession()
{
    delete ui;
}
