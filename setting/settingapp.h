#ifndef SETTINGAPP_H
#define SETTINGAPP_H

#include <QApplication>
#include <QString>
#include <QSettings>

class SettingApp : public QApplication
{
public:
    SettingApp(int& argc, char** argv, const QString& org, const QString& appName);
    ~SettingApp() override = default;

    static SettingApp* instance();

    void writeSettingKey(const QString& scheme, const QString& group, const QString& name, const QString& key = QString());
    QString readSettingKey(const QString& scheme, const QString& group, const QString& name);
    void removeSettingKey(const QString& scheme, const QString& group, const QString& name);
    void removeSettingKey(const QString& scheme);

private:
    QSettings       *m_setting = nullptr;
};

#endif // SETTINGAPP_H
