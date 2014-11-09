#include "highlighter.h"

Highlighter::Highlighter(const QStringList& icons,  const QStringList& properties,
                         const QStringList& pseudo, const QStringList& widgets,
                         const QStringList& sub,    QTextDocument* parent) : QSyntaxHighlighter(parent)
    , m_commentStart("/\\*")
    , m_commentEnd("\\*/")
    , m_number("[0-9]+")
{
    std::function<QVector<HighlightingRule>(const QBrush&, QFont::Weight, const QStringList&)> setHighlighter
            = [](const QBrush& bruch, QFont::Weight weight, const QStringList& list)
    {
        QTextCharFormat charFormat;
        HighlightingRule rule;
        QVector<HighlightingRule> vecRule;

        charFormat.setForeground(bruch);
        charFormat.setFontWeight(weight);
        for(auto& str : list)
        {
            rule.pattern.setPattern("\\b" + str + "\\b");
            rule.format = charFormat;
            vecRule.push_back(rule);
        }
        return vecRule;
    };

    m_highlightingRule_.insert("icons", setHighlighter(QBrush(Qt::green), QFont::Bold, icons));
    m_highlightingRule_.insert("properties", setHighlighter(QBrush(QColor(255, 255, 85)), QFont::Bold, properties));
    m_highlightingRule_.insert("pseudo", setHighlighter(QBrush(QColor(84, 84, 255)), QFont::Bold, pseudo));
    m_highlightingRule_.insert("widgets", setHighlighter(QBrush(QColor(85, 255, 85)), QFont::Bold, widgets));
    m_highlightingRule_.insert("sub", setHighlighter(QBrush(QColor(100, 74, 155)), QFont::Bold, sub));
    m_commentTextFormat.setForeground(QColor(85, 255, 255));
    m_numberFormat.setForeground(QColor(243, 81, 243));
}

void Highlighter::setFormatIcons(const QTextCharFormat& charFormat)
{ setCharFormat("icons", charFormat); }

void Highlighter::setFormatProperties(const QTextCharFormat& charFormat)
{ setCharFormat("properties", charFormat); }

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
                int length = expression.matchedLength();
                this->setFormat(index, length, rule.format);
                index = expression.indexIn(text, index + length);
            }
        }
    this->setCurrentBlockState(0);
    int indexNum = m_number.indexIn(text);
    if(indexNum == -1)
        this->setFormat(1, m_number.matchedLength(), m_numberFormat);
    else
        this->setFormat(indexNum, m_number.matchedLength(), m_numberFormat);
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
