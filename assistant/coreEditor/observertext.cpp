#include "observertext.h"

ObserverText::ObserverText(const QStringList& properties,   const QStringList& pseudo,
                           const QStringList& widgets,      const QStringList& sub,
                           const QStringList& other, QObject* parent) : QObject(parent)
{
    m_strListModel_.insert("properties", new QStringListModel(properties, this));
    m_strListModel_.insert("pseudo", new QStringListModel(pseudo, this));
    m_strListModel_.insert("widgets", new QStringListModel(widgets, this));
    m_strListModel_.insert("sub", new QStringListModel(sub, this));
    m_strListModel_.insert("other", new QStringListModel(other, this));
    m_strListModel_.insert("empty", new QStringListModel(this));
}

void ObserverText::textParserHead(const QString& text)
{
    if(!m_isTextParserHead)
        return;

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
                if(text[i - 2].isLetter())
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
                if(text[i - 2].isLetter())
                    emit stringListModelChanged(m_strListModel_["sub"]);
                else
                    emit stringListModelChanged(m_strListModel_["empty"]);
                break;
            }
            else if(text[i] == 'Q' || text[i] == ',' || text[i] == ' ')
            {
                emit stringListModelChanged(m_strListModel_["widgets"]);
                break;
            }
        }
    }
}

void ObserverText::textParserBody(const QString& text)
{
    for(int i = text.length() - 1; i >= 0; i--)
    {
        if(text[i] == '}' || i == 0)
        {
            m_isTextParserHead = true;
            break;
        }
        else if(text[i] == '{' || text[i] == ';')
        {
            m_isTextParserHead = false;
            emit stringListModelChanged(m_strListModel_["properties"]);
            break;
        }
        else if(text[i] == ':')
        {
            for(int j = i - 1; j >= 0; j--)
            {
                if(text[j] == 'Q')
                {
                    m_isTextParserHead = true;
                    break;
                }
                else if(text[j] == '{')
                {
                    m_isTextParserHead = false;
                    emit stringListModelChanged(m_strListModel_["other"]);
                    break;
                }
            }
            break;
        }
    }
}

