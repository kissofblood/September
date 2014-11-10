#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QTextDocument>
#include <QSyntaxHighlighter>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QTextCharFormat>
#include <QVector>
#include <QHash>
#include <QBrush>
#include <QFont>
#include <QColor>

class Highlighter : public QSyntaxHighlighter
{
public:
    Highlighter(const QStringList& icons,  const QStringList& properties,
                const QStringList& pseudo, const QStringList& widgets,
                const QStringList& sub,    QTextDocument* parent = nullptr);
    ~Highlighter() override = default;

    void setFormatIcons(const QTextCharFormat& charFormat);
    void setFormatProperties(const QTextCharFormat& charFormat);
    void setFormatPseudo(const QTextCharFormat& charFormat);
    void setFormatWidgets(const QTextCharFormat& charFormat);
    void setFormatSub(const QTextCharFormat& charFormat);
    void setFormatComment(const QTextCharFormat& charFormat);
    void setFormatNumber(const QTextCharFormat& charFormat);
    void highlightBlock(const QString& text) override;

private:
    struct HighlightingRule
    {
        QRegExp         pattern;
        QTextCharFormat format;
    };
    QHash<QString, QVector<HighlightingRule>> m_highlightingRule_;
    QTextCharFormat m_commentTextFormat;
    QTextCharFormat m_numberFormat;
    QRegExp         m_commentStart;
    QRegExp         m_commentEnd;
    QRegExp         m_number;

    void setCharFormat(const QString& name, const QTextCharFormat& charFormat);
};

#endif // HIGHLIGHTER_H
