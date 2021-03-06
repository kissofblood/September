#include "highlighter.h"

Highlighter::Highlighter(const QStringList& properties, const QStringList& pseudo,
                         const QStringList& widgets,    const QStringList& sub,
                         const QStringList& other,    QTextDocument* parent) : QSyntaxHighlighter(parent)
    , m_commentStart(QRegExp(R"(/\*)"))
    , m_commentEnd(QRegExp(R"(\*/)"))
    , m_number(QRegExp(R"(([0-9]+)|([0-9]+\.[0-9]+)|(#\b(([a-fA-F]|\d)+)\b))"))
{
    this->connect(m_settingSeptember, &SettingSeptember::settingSeptemberOK, this, &Highlighter::readValue);

    auto setHighlighter = [](const QString& name, const QStringList& list)
    {
        HighlightingRule rule;
        QVector<HighlightingRule> vecRule;

        for(auto& str : list)
        {
            if(name == "widgets" || name == "properties")
                rule.pattern.setPattern(R"(\b)" + str + R"(\b)");
            else if(name == "pseudo")
                rule.pattern.setPattern(R"(\b(:\!)" + str + R"(|:)" + str + R"()\b)");
            else if(name == "sub")
                rule.pattern.setPattern(R"(\b::)" + str + R"(\b)");
            else if(name == "other")
                rule.pattern.setPattern(R"(\:.*)" + str + R"(.*;)");
            vecRule.push_back(rule);
        }
        return vecRule;
    };
    QStringList strList;
    for(QString str : other)
        strList.push_back(str.remove(QRegExp(R"(\(.*\))")));

    m_highlightingRule_.push_back({ "widgets", setHighlighter("widgets", widgets) });
    m_highlightingRule_.push_back({ "sub", setHighlighter("sub", sub) });
    m_highlightingRule_.push_back({ "pseudo", setHighlighter("pseudo", pseudo) });
    m_highlightingRule_.push_back({ "properties", setHighlighter("properties", properties) });
    m_highlightingRule_.push_back({ "ot0her", setHighlighter("other", strList) });

    m_settingSeptember->readScheme();
    if(m_settingSeptember->containsKey())
        readValue();
    else
    {
        setCharFormat("properties", { QColor(255, 255, 85), QFont::Bold });
        m_settingSeptember->writeDefaultPropertiesQss(QColor(255, 255, 85), QFont::Bold);
        setCharFormat("pseudo", { QColor(84, 84, 255), QFont::Bold });
        m_settingSeptember->writeDefaultPseudoQss(QColor(84, 84, 255), QFont::Bold);
        setCharFormat("widgets", { QColor(85, 255, 85), QFont::DemiBold });
        m_settingSeptember->writeDefaultWidgetQss(QColor(85, 255, 85), QFont::DemiBold);
        setCharFormat("sub", { QColor(100, 74, 155), QFont::Bold });
        m_settingSeptember->writeDefaultSubQss(QColor(100, 74, 155), QFont::Bold);
        setCharFormat("other", { QColor(Qt::gray), QFont::Bold });
        m_settingSeptember->writeDefaultOtherQss(QColor(Qt::gray), QFont::Bold);
        m_commentTextFormat.setForeground(QColor(85, 255, 255));
        m_commentTextFormat.setFontWeight(QFont::Normal);
        m_settingSeptember->writeDefaultCommentQss(QColor(85, 255, 255), QFont::Normal);
        m_numberFormat.setForeground(QColor(243, 81, 243));
        m_numberFormat.setFontWeight(QFont::Normal);
        m_settingSeptember->writeDefaultNumberQss(QColor(243, 81, 243), QFont::Normal);
    }
}

void Highlighter::highlightBlock(const QString& text)
{
    for(auto i = m_highlightingRule_.begin(); i != m_highlightingRule_.end(); i++)
        for(auto& rule : i->second)
        {
            int index = rule.pattern.indexIn(text);
            while(index >= 0)
            {
                int length;
                if(i->first == "properties" || i->first == "widgets")
                {

                    if(index > 1)
                        if(text[index - 1] == ':' || text[index - 1] == '!')
                            break;
                    length = rule.pattern.matchedLength();
                }
                else if(i->first == "pseudo")
                {
                    if(text[index + 1] == '!')
                    {
                        index += 2;
                        length = rule.pattern.matchedLength() - 2;
                    }
                    else
                    {
                        index += 1;
                        length = rule.pattern.matchedLength() - 1;
                    }
                }
                else if(i->first == "sub")
                {
                    index += 2;
                    length = rule.pattern.matchedLength() - 2;
                }
                else if(i->first == "other")
                {
                    length = rule.pattern.matchedLength();
                }
                QString tmp;
                for(int q = index; q < length; q++)
                    tmp += text[q];
                this->setFormat(index, length, rule.format);
                index = rule.pattern.indexIn(text, index + length);
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

void Highlighter::readValue()
{
    m_settingSeptember->addValueQss();
    QPair<QColor, QFont::Weight> pair;
    pair = m_settingSeptember->readOtherQss();
    setCharFormat("other", pair);
    pair = m_settingSeptember->readSubQss();
    setCharFormat("sub", pair);
    pair = m_settingSeptember->readWidgetQss();
    setCharFormat("widgets", pair);
    pair = m_settingSeptember->readPseudoQss();
    setCharFormat("pseudo", pair);
    pair = m_settingSeptember->readPropertiesQss();
    setCharFormat("properties", pair);
    pair = m_settingSeptember->readCommentQss();
    m_commentTextFormat.setForeground(QBrush(pair.first));
    m_commentTextFormat.setFontWeight(pair.second);
    pair = m_settingSeptember->readNumberQss();
    m_numberFormat.setForeground(QBrush(pair.first));
    m_numberFormat.setFontWeight(pair.second);
    this->rehighlight();
}

void Highlighter::setCharFormat(const QString& name, const QPair<QColor, QFont::Weight>& pair)
{
    QTextCharFormat charFormat;
    charFormat.setForeground(QBrush(pair.first));
    charFormat.setFontWeight(pair.second);
    for(auto& rule1 : m_highlightingRule_)
        if(rule1.first == name)
        {
            for(HighlightingRule& rule2 : rule1.second)
                rule2.format = charFormat;
            break;
        }
}
