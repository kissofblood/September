#include "settingapp.h"

SettingApp::SettingApp(int& argc, char** argv, const QString& org, const QString& appName) : QApplication(argc, argv)
    , m_setting(new QSettings(org, appName, this))
{
    this->setOrganizationName(org);
    this->setApplicationName(appName);
}

SettingApp* SettingApp::instance()
{ return dynamic_cast<SettingApp*>(qApp); }

void SettingApp::writeSettingKey(const QString& scheme, const QString& group, const QString& name, const QString& key)
{
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup(scheme);
            m_setting->beginGroup(group);
                m_setting->setValue(name, key);
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
}

QString SettingApp::readSettingKey(const QString& scheme, const QString& group, const QString& name)
{
    QString key = "";
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup(scheme);
            m_setting->beginGroup(group);
                QVariant var = m_setting->value(name);
                if(var.isValid())
                    key = var.toString();
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
    return key;
}

void SettingApp::removeSettingKey(const QString& scheme, const QString& group, const QString& name)
{
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup(scheme);
            m_setting->beginGroup(group);
                m_setting->remove(name);
            m_setting->endGroup();
        m_setting->endGroup();
   m_setting->endGroup();
}

void SettingApp::removeSettingKey(const QString& scheme)
{
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup(scheme);
                m_setting->remove("");
        m_setting->endGroup();
   m_setting->endGroup();
}
