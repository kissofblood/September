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
            if(text[i] == '!' && text[i - 1].isLetter())
            {
                emit stringListModelChanged(m_strListModel_["empty"]);
                break;
            }
            if(text[i] == '!' && text[i - 1] == ':')
            {
                int count = 0;
                for(int j = i - 2; j >= 0; j--)
                {
                    if(text[j].isLetter())
                        break;
                    else
                        count += 1;
                }
                if(count == 0)
                    emit stringListModelChanged(m_strListModel_["pseudo"]);
                else
                    emit stringListModelChanged(m_strListModel_["empty"]);
                break;
            }
            else if(text[i] == ':' && text[i - 1].isLetter())
            {
                emit stringListModelChanged(m_strListModel_["pseudo"]);
                break;
            }
            else if(text[i] == ':' && text[i - 1] == ':')
            {
                int count = 0;
                for(int j = i - 2; j >= 0; j--)
                {
                    if(text[j].isLetter())
                        break;
                    else
                        count += 1;
                }

                if(count == 0)
                    emit stringListModelChanged(m_strListModel_["sub"]);
                else
                    emit stringListModelChanged(m_strListModel_["empty"]);
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
