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
    m_strListModel_.insert("pathRes", new QStringListModel(this));
}

void ObserverCodeQss::textParserHead(const QString& text)
{
    if(!m_isTextParserHead)
        return;

    if(text.length() < 2)
    {
        emit stringListModelChanged(m_strListModel_["widgets"]);
        return;
    }

    for(int i = text.length() - 1; i >= 0; i--)
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
                else if(text[j] == '(')
                {
                    m_isTextParserHead = false;
                    emit stringListModelChanged(m_strListModel_["pathRes"]);
                    break;
                }
            }
            break;
        }
    }
}

QVector<int> ObserverCodeQss::checkingCodeQss(std::string& text, QTextBlock& textBlock)
{
    QMap<std::string::iterator, int> blockCharacter;
    std::string::iterator iterText = text.begin();
    int numberBlock = 1;    

    while(textBlock.isValid())
    {
        std::string tmpText = textBlock.text().toStdString();
        if(tmpText.empty() || *(tmpText.end() - 1) != '\n')
            tmpText += '\n';

        for(std::size_t i = 0; i < tmpText.length(); i++)
            if(iterText != text.end())
            {
                blockCharacter.insert(iterText, numberBlock);
                iterText += 1;
            }
        numberBlock += 1;
        textBlock = textBlock.next();
    }

    std::string::iterator begin = text.begin();
    std::string::iterator end = text.end();
    CheckingCodeQss cheking(begin, end);

    bool success = qi::phrase_parse(begin, end, cheking, qi::space);

    if(begin == end && success)
    {
        qDebug()<<"true!!";
        return QVector<int>();
    }
    qDebug()<<"false!!";
    return { blockCharacter[cheking.getIterator()] };
}

void ObserverCodeQss::addAutoComplete(const QStringList& list)
{ m_strListModel_["pathRes"]->setStringList(list); }

ObserverCodeQss::CheckingCodeQss::CheckingCodeQss(std::string::iterator first, std::string::iterator last) : qi::grammar<std::string::iterator, qi::space_type>::base_type(m_expession)
    , m_iterFirst(first)
    , m_iterLast(last)
{
    auto comp = std::bind(&CheckingCodeQss::compareCh, this, std::placeholders::_1);
    auto compS1 = std::bind(&CheckingCodeQss::compareStr, this, "/*");
    auto compS2 = std::bind(&CheckingCodeQss::compareStr, this, "*/");
    auto compS3 = std::bind(&CheckingCodeQss::compareCh, this, ':');
    auto compS4 = std::bind(&CheckingCodeQss::compareStr, this, ":!");
    auto compS5 = std::bind(&CheckingCodeQss::compareCh, this, '.');
    auto compS6 = std::bind(&CheckingCodeQss::compareStr, this, "::");
    auto compS7 = std::bind(&CheckingCodeQss::compareCh, this, '#');
    auto compS8 = std::bind(&CheckingCodeQss::compareCh, this, '[');
    auto compS9 = std::bind(&CheckingCodeQss::compareCh, this, '=');
    auto compS10 = std::bind(&CheckingCodeQss::compareCh, this, '"');
    auto compS11 = std::bind(&CheckingCodeQss::compareCh, this, ']');
    auto compS12 = std::bind(&CheckingCodeQss::compareCh, this, '{');
    auto compS13 = std::bind(&CheckingCodeQss::compareCh, this, '}');
    auto compS14 = std::bind(&CheckingCodeQss::compareCh, this, ',');
    auto compS15 = std::bind(&CheckingCodeQss::compareCh, this, ';');
    auto compS16 = std::bind(&CheckingCodeQss::compareCh, this, '-');
    auto compS17 = std::bind(&CheckingCodeQss::compareCh, this, '_');
    auto compS18 = std::bind(&CheckingCodeQss::compareCh, this, '+');
    auto compS19 = std::bind(&CheckingCodeQss::compareCh, this, '(');
    auto compS20 = std::bind(&CheckingCodeQss::compareCh, this, ')');

    m_expession = *(m_header | m_comment);

    m_comment = qi::lit("/*")[compS1] >> *(qi::print[comp] -"*/") >> qi::lit("*/")[compS2];

    m_sub = (qi::lit(':')[compS3] >> m_selector) | (qi::lit(":!")[compS4] >> m_selector);

    m_header = ((qi::lit('.')[compS5] || m_selector) >> -
               (
                   (qi::lit("::")[compS6] >> m_selector >> *m_sub)       |
                   (qi::lit(':')[compS3] >> m_selector >> *m_sub)        |
                   (qi::lit(":!")[compS4] >> m_selector >> *m_sub)       |
                   (qi::lit('#')[compS7] >> m_selector ||
                   (
                       qi::lit('[')[compS8]
                           >> m_selector >> qi::lit('=')[compS9] >> qi::lit('"')[compS10] >> m_selector >>
                       qi::lit('"')[compS10] >> qi::lit(']')[compS11]
                   ) >> *m_sub)
               ) >> *m_comment) % qi::lit(',')[compS14] >> qi::lit('{')[compS12]
                                                        >> *(m_body | m_comment)
                                                        >> qi::lit('}')[compS13];

    m_body = m_property >> qi::lit(':')[compS3]
                        >> +(m_comment | m_value)
                        >> qi::lit(';')[compS15];

    m_property = qi::alpha[comp] >> *(((qi::lit('-')[compS16] | qi::lit('_')[compS17])
                                 >> qi::alnum[comp]) | qi::alnum[comp]);
    m_selector = qi::alpha[comp] >> *(((qi::lit('-')[compS16] | qi::lit('_')[compS17])
                                 >> qi::alnum[comp]) | qi::alnum[comp]);

    m_function = qi::lit('(')[compS19] >> *(qi::print[comp] -')') >> qi::lit(')')[compS20];

    m_value = (+qi::alnum[comp] || m_function)                     |
              (qi::lit('-')[compS16] | qi::lit('+')[compS18] >> +qi::alnum[comp])    |
              (qi::lit('"')[compS10] >> +qi::alnum[comp] >> qi::lit('"')[compS10]);
}

std::string::iterator ObserverCodeQss::CheckingCodeQss::getIterator() const
{ return m_iterFirst; }

void ObserverCodeQss::CheckingCodeQss::compareCh(const char& ch)
{
    forever
    {
        if(m_iterFirst == m_iterLast)
            break;
        else if(*m_iterFirst == ch)
            break;
        m_iterFirst += 1;
    }
}

void ObserverCodeQss::CheckingCodeQss::compareStr(const std::string& str)
{
    for(std::size_t i = 0; i < str.length(); i++)
    {
        if(m_iterFirst == m_iterLast)
            break;
        else
            m_iterFirst += 1;
    }
}
