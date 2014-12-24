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
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup(group);
                    m_setting->setValue(name, key);
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
}

void SettingApp::writeDefaultSettingKey(const QString& scheme, const QString& group, const QString& name, const QString& key)
{
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup("defaultScheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup(group);
                    m_setting->setValue(name, key);
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
}

void SettingApp::writeSettingKey(const QString& scheme, int pos)
{
    m_setting->beginGroup("settingKey");
        m_setting->beginWriteArray("schemes");
            m_setting->setArrayIndex(pos);
            m_setting->setValue("name", scheme);
        m_setting->endArray();
    m_setting->endGroup();
}

void SettingApp::writeCurrentSettingKey(const QString& scheme)
{
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup("currentScheme");
            m_setting->setValue("name", scheme);
        m_setting->endGroup();
    m_setting->endGroup();
}

QString SettingApp::readCurrentSettingKey()
{
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup("currentScheme");
            QString current = m_setting->value("name").toString();
        m_setting->endGroup();
    m_setting->endGroup();
    return qMove(current);
}

QString SettingApp::readSettingKey(const QString& scheme, const QString& group, const QString& name)
{
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup(group);
                    QString key = m_setting->value(name).toString();
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
    return qMove(key);
}

QString SettingApp::readDefaultSettingKey(const QString& scheme, const QString& group, const QString& name)
{
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup("defaultScheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup(group);
                    QString key = m_setting->value(name).toString();
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
    return qMove(key);
}

QStringList SettingApp::readSettingKey()
{
    QStringList list;
    m_setting->beginGroup("settingKey");
        int size = m_setting->beginReadArray("schemes");
        for(int i = 0; i < size; i++)
        {
            m_setting->setArrayIndex(i);
            list.push_back(m_setting->value("name").toString());
        }
        m_setting->endArray();
    m_setting->endGroup();
    return qMove(list);
}

void SettingApp::removeSettingKey(const QString& scheme, const QString& group, const QString& name)
{
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup(group);
                    m_setting->remove(name);
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
}

void SettingApp::removeSettingKey(const QString& scheme)
{
    m_setting->beginGroup("settingKey");
        int size = m_setting->beginReadArray("schemes");
        int index = 0;
        for(; index < size; index++)
        {
            m_setting->setArrayIndex(index);
            QString key = m_setting->value("name").toString();
            if(key == scheme)
            {
                m_setting->remove("name");
                break;
            }
        }
        m_setting->endArray();
        if(index != size)
        {
            QStringList list;
            m_setting->beginReadArray("schemes");
                for(int i = index + 1; i < size; i++)
                {
                    m_setting->setArrayIndex(i);
                    list.push_back(m_setting->value("name").toString());
                    m_setting->remove("name");
                }
            m_setting->endArray();
            m_setting->beginWriteArray("schemes", size - 1);
                if(!list.isEmpty())
                    for(int i = index, j = 0; i < size - 1; i++)
                    {
                        m_setting->setArrayIndex(i);
                        m_setting->setValue("name", list[j]);
                    }
            m_setting->endArray();
        }
        m_setting->beginGroup(scheme);
            m_setting->remove("");
        m_setting->endGroup();
    m_setting->endGroup();
}

bool SettingApp::containsSettingKey(const QString& scheme, const QString& group, const QString& name)
{
    bool success;
    m_setting->beginGroup("settingKey");
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup(group);
                    success = m_setting->contains(name);
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
    return success;
}

void SettingApp::writeHistoryFile(const QString& file)
{
    QFileInfoList list = readHistoryFile();
    clearHistoryFile();
    for(int i = 0; i < list.size(); i++)
        if(list[i].filePath() == file)
        {
            list.removeAt(i);
            break;
        }
    list.push_front(file);
    if(list.size() == 6)
        list.pop_back();

    m_setting->beginGroup("historyFile");
        m_setting->beginWriteArray("pathFile");
            for(int i = 0; i < list.size(); i++)
            {
                m_setting->setArrayIndex(i);
                m_setting->setValue("file", list[i].filePath());
            }
        m_setting->endArray();
    m_setting->endGroup();
}

QFileInfoList SettingApp::readHistoryFile()
{
    m_setting->beginGroup("historyFile");
        int size = m_setting->beginReadArray("pathFile");
        QFileInfoList list;
        for(int i = 0; i < size; i++)
        {
            m_setting->setArrayIndex(i);
            list.push_back(m_setting->value("file").toString());
        }
        m_setting->endArray();
    m_setting->endGroup();
    return qMove(list);
}

void SettingApp::clearHistoryFile()
{
    m_setting->beginGroup("historyFile");
        m_setting->remove("");
    m_setting->endGroup();
}

void SettingApp::writeBackgroundColorSettingSeptember(const QColor& color)
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("colorEdit");
            m_setting->beginGroup("backgroundColor");
                m_setting->setValue("background", color);
            m_setting->endGroup();
        m_setting->endGroup();
   m_setting->endGroup();
}

QColor SettingApp::readBackgroundColorSettingSeptember()
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("colorEdit");
            m_setting->beginGroup("backgroundColor");
                QColor color = qvariant_cast<QColor>(m_setting->value("background"));
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
    return qMove(color);
}

void SettingApp::writeCurrentLineColorSettingSeptember(const QColor& color)
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("colorEdit");
            m_setting->beginGroup("currentLineColor");
                m_setting->setValue("currentLine", color);
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
}

QColor SettingApp::readCurrentLineColorSettingSeptember()
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("colorEdit");
            m_setting->beginGroup("currentLineColor");
                QColor color = qvariant_cast<QColor>(m_setting->value("currentLine"));
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
    return qMove(color);
}

void SettingApp::writeSearchTextColorSettingSeptember(const QColor& searchText)
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("colorEdit");
            m_setting->beginGroup("searchTextColor");
                m_setting->setValue("searchText", searchText);
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
}

QColor SettingApp::readSearchTextColorSettingSeptember()
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("colorEdit");
            m_setting->beginGroup("searchTextColor");
                QColor color = qvariant_cast<QColor>(m_setting->value("searchText"));
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
    return qMove(color);
}

bool SettingApp::containsColorSettingSeptember()
{
    bool success;
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("colorEdit");
            m_setting->beginGroup("backgroundColor");
                success = m_setting->contains("background");
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
    return success;
}

void SettingApp::writeFontText(const QFont& font)
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("fontText");
            m_setting->setValue("font", font);
        m_setting->endGroup();
    m_setting->endGroup();
}

QFont SettingApp::readFontText()
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("fontText");
            QFont font = qvariant_cast<QFont>(m_setting->value("font"));
        m_setting->endGroup();
    m_setting->endGroup();
    return qMove(font);
}
