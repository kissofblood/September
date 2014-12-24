#ifndef SETTINGAPP_H
#define SETTINGAPP_H

#include <QApplication>
#include <QString>
#include <QSettings>
#include <QStringList>
#include <QFileInfoList>
#include <QColor>
#include <QFont>

class SettingApp : public QApplication
{
public:
    SettingApp(int& argc, char** argv, const QString& org, const QString& appName);
    ~SettingApp() override = default;

    static SettingApp* instance();

    void writeSettingKey(const QString& scheme, const QString& group, const QString& name, const QString& key);
    void writeDefaultSettingKey(const QString& scheme, const QString& group, const QString& name, const QString& key);
    void writeSettingKey(const QString& scheme, int pos);
    void writeCurrentSettingKey(const QString& scheme);
    QString readCurrentSettingKey();
    QString readSettingKey(const QString& scheme, const QString& group, const QString& name);
    QString readDefaultSettingKey(const QString& scheme, const QString& group, const QString& name);
    QStringList readSettingKey();
    void removeSettingKey(const QString& scheme, const QString& group, const QString& name);
    void removeSettingKey(const QString& scheme);
    bool containsSettingKey(const QString& scheme, const QString& group, const QString& name);

    void writeHistoryFile(const QString& file);
    QFileInfoList readHistoryFile();
    void clearHistoryFile();

    void writeBackgroundColorSettingSeptember(const QColor& color);
    QColor readBackgroundColorSettingSeptember();
    void writeCurrentLineColorSettingSeptember(const QColor& color);
    QColor readCurrentLineColorSettingSeptember();
    void writeSearchTextColorSettingSeptember(const QColor& searchText);
    QColor readSearchTextColorSettingSeptember();
    bool containsColorSettingSeptember();
    void writeFontText(const QFont& font);
    QFont readFontText();

private:
    QSettings   *m_setting = nullptr;
};

#endif // SETTINGAPP_H
