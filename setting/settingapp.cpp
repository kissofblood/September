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
    beginSchemeSettingKey;
        m_setting->beginGroup(scheme);
            m_setting->beginGroup(group);
                m_setting->setValue(name, key);
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

void SettingApp::writeDefaultSettingKey(const QString& group, const QString& name, const QString& key)
{
    beginDefaultSchemeSettingKey;
        m_setting->beginGroup(group);
            m_setting->setValue(name, key);
        m_setting->endGroup();
    endSetting;
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
    beginSchemeSettingKey;
        m_setting->beginGroup(scheme);
            m_setting->beginGroup(group);
                QString key = m_setting->value(name).toString();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
    return qMove(key);
}

QString SettingApp::readDefaultSettingKey(const QString& group, const QString& name)
{
    beginDefaultSchemeSettingKey;
        m_setting->beginGroup(group);
            QString key = m_setting->value(name).toString();
        m_setting->endGroup();
    endSetting;
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
    beginSchemeSettingKey;
        m_setting->beginGroup(scheme);
            m_setting->beginGroup(group);
                m_setting->remove(name);
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

void SettingApp::removeSettingKey(const QString& scheme)
{
    beginSchemeSettingKey;
        deleteScheme(scheme);
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->remove("");
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

bool SettingApp::containsSettingKey(const QString& scheme, const QString& group, const QString& name)
{
    bool success;
    beginSchemeSettingKey;
        m_setting->beginGroup(scheme);
            m_setting->beginGroup(group);
                success = m_setting->contains(name);
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
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

void SettingApp::writeBackgroundColorSettingSeptember(const QString& scheme, const QColor& color)
{
    beginColorSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("backgroundColor");
                    m_setting->setValue("background", color);
                m_setting->endGroup();
            m_setting->endGroup();
       m_setting->endGroup();
   endSetting;
}

void SettingApp::writeDefaultBackgroundColorSettingSeptember(const QColor& color)
{
    beginDefaultColorSettingSeptember;
        m_setting->beginGroup("backgroundColor");
            m_setting->setValue("background", color);
        m_setting->endGroup();
    endSetting;
}

QColor SettingApp::readBackgroundColorSettingSeptember(const QString& scheme)
{
    beginColorSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("backgroundColor");
                    QColor color = qvariant_cast<QColor>(m_setting->value("background"));
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
    return qMove(color);
}

QColor SettingApp::readDefaultBackgroundColorSettingSeptember()
{
    beginDefaultColorSettingSeptember;
        m_setting->beginGroup("backgroundColor");
            QColor color = qvariant_cast<QColor>(m_setting->value("background"));
        m_setting->endGroup();
    endSetting;
    return qMove(color);
}

void SettingApp::writeCurrentLineColorSettingSeptember(const QString& scheme, const QColor& color)
{
    beginColorSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("currentLineColor");
                    m_setting->setValue("currentLine", color);
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

void SettingApp::writeDefaultCurrentLineColorSettingSeptember(const QColor& color)
{
    beginDefaultColorSettingSeptember;
        m_setting->beginGroup("currentLineColor");
            m_setting->setValue("currentLine", color);
        m_setting->endGroup();
    endSetting;
}

QColor SettingApp::readCurrentLineColorSettingSeptember(const QString& scheme)
{
    beginColorSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("currentLineColor");
                    QColor color = qvariant_cast<QColor>(m_setting->value("currentLine"));
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
    return qMove(color);
}

QColor SettingApp::readDefaultCurrentLineColorSettingSeptember()
{
    beginColorSettingSeptember;
        m_setting->beginGroup("currentLineColor");
            QColor color = qvariant_cast<QColor>(m_setting->value("currentLine"));
        m_setting->endGroup();
    endSetting;
    return qMove(color);
}

void SettingApp::writeSearchTextColorSettingSeptember(const QString& scheme, const QColor& color)
{
    beginColorSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("searchTextColor");
                    m_setting->setValue("searchText", color);
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

void SettingApp::writeDefaultSearchTextColorSettingSeptember(const QColor& color)
{
    beginDefaultColorSettingSeptember;
        m_setting->beginGroup("searchTextColor");
            m_setting->setValue("searchText", color);
        m_setting->endGroup();
    endSetting;
}

QColor SettingApp::readSearchTextColorSettingSeptember(const QString& scheme)
{
    beginColorSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("searchTextColor");
                    QColor color = qvariant_cast<QColor>(m_setting->value("searchText"));
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
    return qMove(color);
}

QColor SettingApp::readDefaultSearchTextColorSettingSeptember()
{
    beginDefaultColorSettingSeptember;
        m_setting->beginGroup("searchTextColor");
            QColor color = qvariant_cast<QColor>(m_setting->value("searchText"));
        m_setting->endGroup();
    endSetting;
    return qMove(color);
}

bool SettingApp::containsColorSettingSeptember()
{
    QVector<bool> success;
    beginDefaultColorSettingSeptember;
        m_setting->beginGroup("backgroundColor");
            success.push_back(m_setting->contains("background"));
        m_setting->endGroup();
        m_setting->beginGroup("currentLineColor");
            success.push_back(m_setting->contains("currentLine"));
        m_setting->endGroup();
        m_setting->beginGroup("searchTextColor");
            success.push_back(m_setting->contains("searchText"));
        m_setting->endGroup();
    endSetting;
    for(auto& s : success) if(!s) return false;
    return true;
}

void SettingApp::writeFontTextSeptember(const QString& scheme, const QFont& font)
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("fontText");
                    m_setting->setValue("font", font);
                m_setting->endGroup();
            m_setting->endGroup();
       m_setting->endGroup();
   m_setting->endGroup();
}

void SettingApp::writeDefaultFontTextSeptember(const QFont& font)
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("defaultFontText");
            m_setting->beginGroup("fontText");
                m_setting->setValue("font", font);
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
}

QFont SettingApp::readFontTextSeptember(const QString& scheme)
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("fontText");
                    QFont font = qvariant_cast<QFont>(m_setting->value("font"));
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
    return qMove(font);
}

QFont SettingApp::readDefaultFontTextSeptember()
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("defaultFontText");
            m_setting->beginGroup("fontText");
                QFont font = qvariant_cast<QFont>(m_setting->value("font"));
            m_setting->endGroup();
        m_setting->endGroup();
   m_setting->endGroup();
   return qMove(font);
}

void SettingApp::writeOtherQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("otherQss");
                    m_setting->setValue("color", color);
                    m_setting->setValue("weight", static_cast<int>(weight));
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

void SettingApp::writeDefaultOtherQssSeptember(const QColor& color, QFont::Weight weight)
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("otherQss");
            m_setting->setValue("color", color);
            m_setting->setValue("weight", static_cast<int>(weight));
        m_setting->endGroup();
    endSetting;
}

QPair<QColor, QFont::Weight> SettingApp::readOtherQssSeptember(const QString& scheme)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("otherQss");
                    QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                          static_cast<QFont::Weight>(m_setting->value("weight").toInt())};
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

QPair<QColor, QFont::Weight> SettingApp::readDefaultOtherQssSeptember()
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("otherQss");
            QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                  static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

void SettingApp::writePropertiesQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("propertiesQss");
                    m_setting->setValue("color", color);
                    m_setting->setValue("weight", static_cast<int>(weight));
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
   endSetting;
}

void SettingApp::writeDefaultPropertiesQssSeptember(const QColor& color, QFont::Weight weight)
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("propertiesQss");
            m_setting->setValue("color", color);
            m_setting->setValue("weight", static_cast<int>(weight));
        m_setting->endGroup();
    endSetting;
}

QPair<QColor, QFont::Weight> SettingApp::readPropertiesQssSeptember(const QString& scheme)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("propertiesQss");
                    QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                          static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

QPair<QColor, QFont::Weight> SettingApp::readDefaultPropertiesQssSeptember()
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("propertiesQss");
            QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                  static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

void SettingApp::writePseudoQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("pseudoQss");
                    m_setting->setValue("color", color);
                    m_setting->setValue("weight", static_cast<int>(weight));
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

void SettingApp::writeDefaultPseudoQssSeptember(const QColor& color, QFont::Weight weight)
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("pseudoQss");
            m_setting->setValue("color", color);
            m_setting->setValue("weight", static_cast<int>(weight));
        m_setting->endGroup();
    endSetting;
}

QPair<QColor, QFont::Weight> SettingApp::readPseudoQssSeptember(const QString& scheme)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("pseudoQss");
                    QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                          static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

QPair<QColor, QFont::Weight> SettingApp::readDefaultPseudoQssSeptember()
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("pseudoQss");
            QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                  static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

void SettingApp::writeSubQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("subQss");
                    m_setting->setValue("color", color);
                    m_setting->setValue("weight", static_cast<int>(weight));
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

void SettingApp::writeDefaultSubQssSeptember(const QColor& color, QFont::Weight weight)
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("subQss");
            m_setting->setValue("color", color);
            m_setting->setValue("weight", static_cast<int>(weight));
        m_setting->endGroup();
    endSetting;
}

QPair<QColor, QFont::Weight> SettingApp::readSubQssSeptember(const QString& scheme)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("subQss");
                    QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                          static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

QPair<QColor, QFont::Weight> SettingApp::readDefaultSubQssSeptember()
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("subQss");
            QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                  static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

void SettingApp::writeWidgetQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("widgetQss");
                    m_setting->setValue("color", color);
                    m_setting->setValue("weight", weight);
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

void SettingApp::writeDefaultWidgetQssSeptember(const QColor& color, QFont::Weight weight)
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("widgetQss");
            m_setting->setValue("color", color);
            m_setting->setValue("weight", weight);
        m_setting->endGroup();
    endSetting;
}

QPair<QColor, QFont::Weight> SettingApp::readWidgetQssSeptember(const QString& scheme)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("widgetQss");
                    QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                          static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

QPair<QColor, QFont::Weight> SettingApp::readDefaultWidgetQssSeptember()
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("widgetQss");
            QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                  static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

void SettingApp::writeCommentQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("commentQss");
                    m_setting->setValue("color", color);
                    m_setting->setValue("weight", weight);
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

void SettingApp::writeDefaultCommentQssSeptember(const QColor& color, QFont::Weight weight)
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("commentQss");
            m_setting->setValue("color", color);
            m_setting->setValue("weight", weight);
        m_setting->endGroup();
    endSetting;
}

QPair<QColor, QFont::Weight> SettingApp::readCommentQssSeptember(const QString& scheme)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("commentQss");
                    QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                          static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
   endSetting;
   return qMove(pair);
}

QPair<QColor, QFont::Weight> SettingApp::readDefaultCommentQssSeptember()
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("commentQss");
            QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                  static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

void SettingApp::writeNumberQssSeptember(const QString& scheme, const QColor& color, QFont::Weight weight)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("numberQss");
                    m_setting->setValue("color", color);
                    m_setting->setValue("weight", weight);
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    endSetting;
}

void SettingApp::writeDefaultNumberQssSeptember(const QColor& color, QFont::Weight weight)
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("numberQss");
            m_setting->setValue("color", color);
            m_setting->setValue("weight", weight);
        m_setting->endGroup();
    endSetting;
}

QPair<QColor, QFont::Weight> SettingApp::readNumberQssSeptember(const QString& scheme)
{
    beginQssSettingSeptember;
        m_setting->beginGroup("scheme");
            m_setting->beginGroup(scheme);
                m_setting->beginGroup("numberQss");
                    QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                          static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
   endSetting;
   return qMove(pair);
}

QPair<QColor, QFont::Weight> SettingApp::readDefaultNumberQssSeptember()
{
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("numberQss");
            QPair<QColor, QFont::Weight> pair = { qvariant_cast<QColor>(m_setting->value("color")),
                                                  static_cast<QFont::Weight>(m_setting->value("weight").toInt()) };
        m_setting->endGroup();
    endSetting;
    return qMove(pair);
}

bool SettingApp::containsQssSettingSeptember()
{
    QVector<bool> success;
    beginDefaultQssSettingSeptember;
        m_setting->beginGroup("otherQss");
            success.push_back(m_setting->contains("color"));
        m_setting->endGroup();
        m_setting->beginGroup("propertiesQss");
            success.push_back(m_setting->contains("color"));
        m_setting->endGroup();
        m_setting->beginGroup("pseudoQss");
            success.push_back(m_setting->contains("color"));
        m_setting->endGroup();
        m_setting->beginGroup("subQss");
            success.push_back(m_setting->contains("color"));
        m_setting->endGroup();
        m_setting->beginGroup("widgetQss");
            success.push_back(m_setting->contains("color"));
        m_setting->endGroup();
        m_setting->beginGroup("commentQss");
            success.push_back(m_setting->contains("color"));
        m_setting->endGroup();
        m_setting->beginGroup("numberQss");
            success.push_back(m_setting->contains("color"));
        m_setting->endGroup();
    endSetting;
    for(auto& s : success) if(!s) return false;
    return true;
}

void SettingApp::writeSchemeSettingSeptember(const QString& scheme, int pos)
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginWriteArray("schemes");
            m_setting->setArrayIndex(pos);
            m_setting->setValue("name", scheme);
        m_setting->endArray();
    m_setting->endGroup();
}

void SettingApp::removeSchemeSettingSeptember(const QString& scheme)
{
    m_setting->beginGroup("settingSeptember");
        deleteScheme(scheme);
        m_setting->beginGroup("colorEdit");
            m_setting->beginGroup("scheme");
                m_setting->beginGroup(scheme);
                    m_setting->remove("");
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
        m_setting->beginGroup("qss");
            m_setting->beginGroup("scheme");
                m_setting->beginGroup(scheme);
                    m_setting->remove("");
                m_setting->endGroup();
            m_setting->endGroup();
        m_setting->endGroup();
    m_setting->endGroup();
}

QStringList SettingApp::readSchemeSettingSeptember()
{
    QStringList list;
    m_setting->beginGroup("settingSeptember");
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

void SettingApp::writeCurrentSchemeSettingSeptember(const QString& scheme)
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("currentScheme");
            m_setting->setValue("name", scheme);
        m_setting->endGroup();
    m_setting->endGroup();
}

QString SettingApp::readCurrentSchemeSettingSeptember()
{
    m_setting->beginGroup("settingSeptember");
        m_setting->beginGroup("currentScheme");
            QString current = m_setting->value("name").toString();
        m_setting->endGroup();
    m_setting->endGroup();
    return qMove(current);
}

void SettingApp::deleteScheme(const QString& scheme)
{
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
}
