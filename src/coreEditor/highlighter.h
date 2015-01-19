#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include "setting/settingseptember.h"
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
#include <QPair>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    Highlighter(const QStringList& properties,  const QStringList& pseudo,
                const QStringList& widgets,     const QStringList& sub,
                const QStringList& other, QTextDocument* parent = nullptr);
    ~Highlighter() override = default;

    void highlightBlock(const QString& text) override;

private slots:
    void readValue();

private:
    struct HighlightingRule
    {
        QRegExp         pattern;
        QTextCharFormat format;
    };
    QVector<QPair<QString, QVector<HighlightingRule>>>  m_highlightingRule_;
    QTextCharFormat     m_commentTextFormat;
    QTextCharFormat     m_numberFormat;
    QRegExp             m_commentStart;
    QRegExp             m_commentEnd;
    QRegExp             m_number;
    SettingSeptember    *m_settingSeptember = SettingSeptember::instance();

    void setCharFormat(const QString& name, const QPair<QColor, QFont::Weight>& pair);
};

#endif // HIGHLIGHTER_H
