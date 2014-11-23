#include "observercodeqss.h"

ObserverCodeQss::ObserverCodeQss(const QStringList& properties, const QStringList& pseudo,
                                 const QStringList& widgets,    const QStringList& sub,
                                 const QStringList& other, QObject* parent) : QObject(parent)
{
    m_strListModel_.insert("properties", new QStringListModel(properties, this));
    m_strListModel_.insert("pseudo", new QStringListModel(pseudo, this));
    m_strListModel_.insert("widgets", new QStringListModel(widgets, this));
    m_strListModel_.insert("sub", new QStringListModel(sub, this));
    m_strListModel_.insert("other", new QStringListModel(other, this));
    m_strListModel_.insert("empty", new QStringListModel(this));
}

void ObserverCodeQss::textParserHead(const QString& text)
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

void ObserverCodeQss::textParserBody(const QString& text)
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

QVector<int> ObserverCodeQss::checkingCodeQss(std::string& text, const QMap<std::string::iterator, int>& blockCh)
{
    std::string::iterator begin = text.begin();
    std::string::iterator end = text.end();

    bool success = qi::phrase_parse(begin, end, CheckingCodeQss(), qi::space);

    for(auto i = begin; i != end; i++)
        std::cout<<*i;

    qDebug()<<(begin == end && success)<<'\n';

    if(begin == end)
        return QVector<int>();
    else
        return { blockCh[begin] };
}

ObserverCodeQss::CheckingCodeQss::CheckingCodeQss() : qi::grammar<std::string::iterator, qi::space_type, std::string()>::base_type(m_expession)
{
    m_expession = *(m_header | m_ignore);

    m_ignore = qi::skip["/*" >> *(qi::print -"*/") >> "*/"];

    m_sub = (':' >> m_selector) | (":!" >> m_selector) | m_ignore;

    m_header = ((('.' >> m_selector) | m_selector) >> -
                (
                    ("::" >> m_selector >> *m_sub)       |
                    (':' >> m_selector >> *m_sub)        |
                    (":!" >> m_selector >> *m_sub)       |
                    ('#' >> m_selector >>
                     '[' >> m_selector >> "=\"" >> m_selector >> "\"]" >> *m_sub) |
                    ('#' >> m_selector >> *m_sub)       ||
                    +m_ignore
                    ) >> *m_ignore) % ',' >> '{' >> *(m_body | m_ignore) >> '}';

    m_body = m_property >> ':' >> +(m_ignore | m_value) >> ';';

    m_property = qi::alnum >> *(((qi::lit('-') | qi::lit('_')) >> qi::alnum) | qi::alnum);
    m_selector = qi::alnum >> *(((qi::lit('-') | qi::lit('_')) >> qi::alnum) | qi::alnum);

    m_function = +qi::alnum >> '(' >> *(qi::print -')') >> ')';

    m_value = m_function | ('-' | '+' >> +qi::alnum) | ('"' >> +qi::alnum >> '"') | +qi::alnum | ('#' >> qi::hex);
}
