#include "observertext.h"

ObserverText::ObserverText(const QStringList& icons,    const QStringList& properties,
                           const QStringList& pseudo,   const QStringList& widgets,
                           const QStringList& sub,      const QStringList& other, QObject* parent) : QObject(parent)
{
    m_strListModel_.insert("icons", new QStringListModel(icons, this));
    m_strListModel_.insert("properties", new QStringListModel(properties, this));
    m_strListModel_.insert("pseudo", new QStringListModel(pseudo, this));
    m_strListModel_.insert("widgets", new QStringListModel(widgets, this));
    m_strListModel_.insert("sub", new QStringListModel(sub, this));
    m_strListModel_.insert("other", new QStringListModel(other, this));
    m_strListModel_.insert("empty", new QStringListModel(this));
}

void ObserverText::textParser(const QString& text)
{
    for(int i = text.length() - 1; i >= 0; i--)
    {
        if(text.length() < 2)
        {
            emit stringListModelChanged(m_strListModel_["widgets"]);
            break;
        }
        else
        {
            if(text[i] == '!' && text[i - 1] == ':' && text[i - 2] == ':')
            {
                emit stringListModelChanged(m_strListModel_["empty"]);
                break;
            }
            else if(text[i] == '!' && text[i - 1] == ':')
            {
                emit stringListModelChanged(m_strListModel_["pseudo"]);
                break;
            }
            else if(text[i] == '!' && text[i - 1] != ':')
            {
                emit stringListModelChanged(m_strListModel_["empty"]);
                break;
            }
            else if(text[i] == ':' && text[i - 1] == '!')
            {
                emit stringListModelChanged(m_strListModel_["empty"]);
                break;
            }
            else if(text[i] == ':' && text[i - 1] != ':')
            {
                emit stringListModelChanged(m_strListModel_["pseudo"]);
                break;
            }
            else if(text[i] == ':' && text[i - 1] == ':')
            {
                emit stringListModelChanged(m_strListModel_["sub"]);
                break;
            }
            else if(text[i] == 'Q' || text[i] == ',')
            {
                emit stringListModelChanged(m_strListModel_["widgets"]);
                break;
            }
        }
    }
}
