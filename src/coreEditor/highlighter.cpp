#include "highlighter.h"

Highlighter::Highlighter(const QStringList& properties, const QStringList& pseudo,
                         const QStringList& widgets,    const QStringList& sub,
                         const QStringList& other,    QTextDocument* parent) : QSyntaxHighlighter(parent)
    , m_commentStart(R"(/\*)")
    , m_commentEnd(R"(\*/)")
    , m_number(R"(([0-9]+)|([0-9]+\.[0-9]+)|(#\b(([a-fA-F]|\d)+)\b))")
{
    auto setHighlighter = [](const QString& name, const QBrush& bruch, QFont::Weight weight, const QStringList& list)
    {
        QTextCharFormat charFormat;
        HighlightingRule rule;
        QVector<HighlightingRule> vecRule;

        charFormat.setForeground(bruch);
        charFormat.setFontWeight(weight);
        for(auto& str : list)
        {
            if(name == "widgets" || name == "properties")
                rule.pattern.setPattern(R"(\b)" + str + R"(\b)");
            else if(name == "pseudo")
                rule.pattern.setPattern(R"(\b(:\!)" + str + R"(|:)" + str + R"()\b)");
            else if(name == "sub")
                rule.pattern.setPattern(R"(\b::)" + str + R"(\b)");
            else if(name == "other")
                rule.pattern.setPattern(R"(:(\w|\s)*)" + str + R"(.*;)");
            rule.format = charFormat;
            vecRule.push_back(rule);
        }
        return vecRule;
    };

    QStringList strList;
    for(QString str : other)
        strList.push_back(str.remove(QRegExp(R"(\(.*\))")));

    m_highlightingRule_.insert("properties", setHighlighter("properties", QBrush(QColor(255, 255, 85)), QFont::Bold, properties));
    m_highlightingRule_.insert("pseudo", setHighlighter("pseudo", QBrush(QColor(84, 84, 255)), QFont::Bold, pseudo));
    m_highlightingRule_.insert("widgets", setHighlighter("widgets", QBrush(QColor(85, 255, 85)), QFont::Bold, widgets));
    m_highlightingRule_.insert("sub", setHighlighter("sub", QBrush(QColor(100, 74, 155)), QFont::Bold, sub));
    m_highlightingRule_.insert("other", setHighlighter("other", QBrush(QColor(Qt::gray)), QFont::Bold, strList));
    m_commentTextFormat.setForeground(QColor(85, 255, 255));
    m_numberFormat.setForeground(QColor(243, 81, 243));
}

void Highlighter::setFormatOther(const QTextCharFormat& charFormat)
{ setCharFormat("other", charFormat); }

void Highlighter::setFormatProperties(const QTextCharFormat& charFormat)
{
    setCharFormat("properties", charFormat);
    setCharFormat("icons", charFormat);
}

void Highlighter::setFormatPseudo(const QTextCharFormat& charFormat)
{ setCharFormat("pseudo", charFormat); }

void Highlighter::setFormatWidgets(const QTextCharFormat& charFormat)
{ setCharFormat("widgets", charFormat); }

void Highlighter::setFormatSub(const QTextCharFormat& charFormat)
{ setCharFormat("sub", charFormat); }

void Highlighter::setFormatComment(const QTextCharFormat& charFormat)
{ m_commentTextFormat = charFormat; }

void Highlighter::setFormatNumber(const QTextCharFormat& charFormat)
{ m_numberFormat = charFormat; }

void Highlighter::highlightBlock(const QString& text)
{
    for(auto i = m_highlightingRule_.begin(); i != m_highlightingRule_.end(); i++)
        for(auto& rule : i.value())
        {
            QRegExp expression(rule.pattern);
            int index = expression.indexIn(text);
            while(index >= 0)
            {
                int length;
                if(i.key() == "properties" || i.key() == "widgets")
                {
                    if(index > 1)
                        if(text[index - 1] == ':' || text[index - 1] == '!')
                            break;
                    length = expression.matchedLength();
                }
                else if(i.key() == "pseudo")
                {
                    if(text[index + 1] == '!')
                    {
                        index += 2;
                        length = expression.matchedLength() - 2;
                    }
                    else
                    {
                        index += 1;
                        length = expression.matchedLength() - 1;
                    }
                }
                else if(i.key() == "sub")
                {
                    index += 2;
                    length = expression.matchedLength() - 2;
                }
                else if(i.key() == "other")
                {
                    index += 1;
                    length = expression.matchedLength() - 2;
                }
                this->setFormat(index, length, rule.format);
                index = expression.indexIn(text, index + length);
            }
        }

    this->setCurrentBlockState(0);
    int indexNum = m_number.indexIn(text);
    if(indexNum == -1)
        indexNum = 1;
    while(indexNum >= 0)
    {
        int length = m_number.matchedLength();
        this->setFormat(indexNum, length, m_numberFormat);
        indexNum = m_number.indexIn(text, indexNum + length);
    }
    this->setCurrentBlockState(0);

    int indexStart = 0;
    if(this->previousBlockState() != 1)
        indexStart = m_commentStart.indexIn(text);
    while(indexStart >= 0)
    {
        int indexEnd = m_commentEnd.indexIn(text, indexStart);
        int commentLength;
        if(indexEnd == -1)
        {
            this->setCurrentBlockState(1);
            commentLength = text.length() - indexStart;
        }
        else
            commentLength = indexEnd - indexStart + m_commentEnd.matchedLength();
        this->setFormat(indexStart, commentLength, m_commentTextFormat);
        indexStart = m_commentStart.indexIn(text, indexStart + commentLength);
    }
}

void Highlighter::setCharFormat(const QString& name, const QTextCharFormat& charFormat)
{
    for(auto& rule : m_highlightingRule_[name])
        rule.format = charFormat;
}