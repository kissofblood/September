#include "settingcommon.h"
#include "ui_settingcommon.h"

SettingCommon::SettingCommon(QWidget* parent) : QWidget(parent),
    ui(new Ui::SettingCommon)
{
    ui->setupUi(this);
    ui->chkChangeFile->setChecked(m_settingApp->readWarningChangeFileSeptember());
    m_state = ui->chkChangeFile->isChecked();

    this->connect(ui->chkChangeFile, &QCheckBox::stateChanged, this, &SettingCommon::setBool);
}

SettingCommon::~SettingCommon()
{ delete ui; }

bool SettingCommon::getState() const
{ return m_state; }

void SettingCommon::writeState()
{ m_settingApp->writeWarningChangeFileSeptember(m_state); }

void SettingCommon::setBool(int state)
{
    if(state == 0)
        m_state = false;
    else if(state == 2)
        m_state = true;
}
