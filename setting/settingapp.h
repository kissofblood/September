#ifndef SETTINGAPP_H
#define SETTINGAPP_H

#include <QApplication>
#include <QString>
#include <QSettings>
#include <QStringList>
#include <QFileInfoList>
#include <QColor>
#include <QFont>
#include <QPair>
#include <QVector>

#define beginColorSettingSeptember              \
    m_setting->beginGroup("settingSeptember");  \
    m_setting->beginGroup("colorEdit");
#define beginQssSettingSeptember                \
    m_setting->beginGroup("settingSeptember");  \
    m_setting->beginGroup("qss");
#define beginSchemeSettingKey                   \
    m_setting->beginGroup("settingKey");        \
    m_setting->beginGroup("scheme");
#define beginDefaultSchemeSettingKey            \
    m_setting->beginGroup("settingKey");        \
    m_setting->beginGroup("defaultScheme");
#define beginDefaultColorSettingSeptember       \
    m_setting->beginGroup("settingSeptember");  \
    m_setting->beginGroup("defaultColorEdit");
#define beginDefaultQssSettingSeptember         \
    m_setting->beginGroup("settingSeptember");  \
    m_setting->beginGroup("defaultQss");
#define endSetting                              \
    m_setting->endGroup();                      \
    m_setting->endGroup();

class SettingApp : public QApplication
{
public:
    SettingApp(int& argc, char** argv, const QString& org, const QString& appName);
    ~SettingApp() override = default;

    static SettingApp* instance();

    void writeSettingKey(const QString& scheme, const QString& group, const QString& name, const QString& key);
    void writeDefaultSettingKey(const QString& group, const QString& name, const QString& key);
    void writeSettingKey(const QString& scheme, int pos);
    void writeCurrentSettingKey(const QString& scheme);
    QString readCurrentSettingKey();
    QString readSettingKey(const QString& scheme, const QString& group, const QString& name);
    QString readDefaultSettingKey(const QString& group, const QString& name);
    QStringList readSettingKey();
    void removeSettingKey(const QString& scheme, const QString& group, const QString& name);
    void removeSettingKey(const QString& scheme);
    bool containsSettingKey(const QString& scheme, const QString& group, const QString& name);

    void writeHistoryFile(const QString& file);
    QFileInfoList readHistoryFile();
    void clearHistoryFile();

    void writeBackgroundColorSettingSeptember(const QString& scheme, const QColor& color);
    void writeDefaultBackgroundColorSettingSeptember(const QColor& color);
    QColor readBackgroundColorSettingSeptember(const QString& scheme);
    QColor readDefaultBackgroundColorSettingSeptember();
    void writeCurrentLineColorSettingSeptember(const QString& scheme, const QColor& color);
    void writeDefaultCurrentLineColorSettingSeptember(const QColor& color);
    QColor readCurrentLineColorSettingSeptember(const QString& scheme);
    QColor readDefaultCurrentLineColorSettingSeptember();
    void writeSearchTextColorSettingSeptember(const QString& scheme, const QColor& color);
    void writeDefaultSearchTextColorSettingSeptember(const QColor& color);
    QColor readSearchTextColorSettingSeptember(const QString& scheme);
    QColor readDefaultSearchTextColorSettingSeptember();
    bool containsColorSettingSeptember();
    void writeFontText(const QString& scheme, const QFont& font);
    void writeDefaultFontText(const QFont& font);
    QFont readFontText(const QString& scheme);
    QFont readDefaultFontText();
    void writeOtherQss(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultOtherQss(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readOtherQss(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultOtherQss();
    void writePropertiesQss(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultPropertiesQss(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readPropertiesQss(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultPropertiesQss();
    void writePseudoQss(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultPseudoQss(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readPseudoQss(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultPseudoQss();
    void writeSubQss(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultSubQss(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readSubQss(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultSubQss();
    void writeWidgetQss(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultWidgetQss(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readWidgetQss(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultWidgetQss();
    void writeCommentQss(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultCommentQss(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readCommentQss(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultCommentQss();
    void writeNumberQss(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultNumberQss(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readNumberQss(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultNumberQss();
    bool containsQssSettingSeptember();
    void writeSchemeSettingSeptember(const QString& scheme, int pos);
    void removeSchemeSettingSeptember(const QString& scheme);
    QStringList readSchemeSettingSeptember();
    void writeCurrentSchemeSettingSeptember(const QString& scheme);
    QString readCurrentSchemeSettingSeptember();

private:
    QSettings   *m_setting = nullptr;

    void deleteScheme(const QString& scheme);
};

#endif // SETTINGAPP_H
