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
    void writeFontTextSeptember(const QString& scheme, const QFont& font);
    void writeDefaultFontTextSeptember(const QFont& font);
    QFont readFontTextSeptember(const QString& scheme);
    QFont readDefaultFontTextSeptember();
    void writeOtherQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultOtherQssSeptember(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readOtherQssSeptember(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultOtherQssSeptember();
    void writePropertiesQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultPropertiesQssSeptember(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readPropertiesQssSeptember(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultPropertiesQssSeptember();
    void writePseudoQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultPseudoQssSeptember(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readPseudoQssSeptember(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultPseudoQssSeptember();
    void writeSubQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultSubQssSeptember(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readSubQssSeptember(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultSubQssSeptember();
    void writeWidgetQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultWidgetQssSeptember(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readWidgetQssSeptember(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultWidgetQssSeptember();
    void writeCommentQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultCommentQssSeptember(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readCommentQssSeptember(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultCommentQssSeptember();
    void writeNumberQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight);
    void writeDefaultNumberQssSeptember(const QColor& color, QFont::Weight weight);
    QPair<QColor, QFont::Weight> readNumberQssSeptember(const QString& scheme);
    QPair<QColor, QFont::Weight> readDefaultNumberQssSeptember();
    bool containsQssSettingSeptember();
    void writeSchemeSettingSeptember(const QString& scheme, int pos);
    void removeSchemeSettingSeptember(const QString& scheme);
    QStringList readSchemeSettingSeptember();
    void writeCurrentSchemeSettingSeptember(const QString& scheme);
    QString readCurrentSchemeSettingSeptember();
    void writeWarningChangeFileSeptember(bool value);
    bool readWarningChangeFileSeptember();
    void writeWidthIndent(int indent);
    void writeDefaultWidthIndent(int indent);
    int readWidthIndent();
    int readDefualtWidthIndent();
    void writeWidthTab(int tab);
    void writeDefaultWidthTab(int tab);
    int readWidthTab();
    int readDefualtWidthTab();

private:
    QSettings   *m_setting = nullptr;

    void deleteScheme(const QString& scheme);
    void beginColorSettingSeptember();
    void beginQssSettingSeptember();
    void beginSchemeSettingKey();
    void beginDefaultSchemeSettingKey();
    void beginDefaultColorSettingSeptember();
    void beginDefaultQssSettingSeptember();
    void endSetting();
};

#endif // SETTINGAPP_H
