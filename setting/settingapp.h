#ifndef SETTINGAPP_H
#define SETTINGAPP_H

#include <QApplication>
#include <QString>
#include <QSettings>
#include <QStringList>

class SettingApp : public QApplication
{
public:
    SettingApp(int& argc, char** argv, const QString& org, const QString& appName);
    ~SettingApp() override = default;

    static SettingApp* instance();
    void writeSettingKey(const QString& scheme, const QString& group, const QString& name, const QString& key = QString());
    void writeSettingKey(const QString& scheme, int pos);
    void writeCurrentSettingKey(const QString& scheme);
    QString readCurrentSettingKey();
    QString readSettingKey(const QString& scheme, const QString& group, const QString& name);
    QStringList readSettingKey();
    void removeSettingKey(const QString& scheme, const QString& group, const QString& name);
    void removeSettingKey(const QString& scheme);
    bool containsSettingKey(const QString& scheme, const QString& group, const QString& name);

private:
    QSettings       *m_setting = nullptr;
};

#endif // SETTINGAPP_H
