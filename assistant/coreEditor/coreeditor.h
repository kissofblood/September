#ifndef COREEDITOR_H
#define COREEDITOR_H

#include "assistant/keywords.h"
#include "highlighter.h"
#include <QWidget>
#include <QPlainTextEdit>
#include <QSize>
#include <QRect>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QColor>
#include <QList>
#include <QTextEdit>
#include <QTextFormat>
#include <QPainter>
#include <QTextBlock>
#include <QString>
#include <functional>
#include <QCompleter>

#include <QtWidgets>

class CoreEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CoreEditor(QWidget* parent = nullptr);
    ~CoreEditor() override = default;

    void setVisibleLineNimberArea(bool value);
    void setDocumentColor(const QColor& color);
    void setLineColor(const QColor& color);
    void setOtherTextColor(const QColor& color);
    void setFormatIcons(const QTextCharFormat& charFormat);
    void setFormatProperties(const QTextCharFormat& charFormat);
    void setFormatPseudo(const QTextCharFormat& charFormat);
    void setFormatWidgets(const QTextCharFormat& charFormat);
    void setFormatSub(const QTextCharFormat& charFormat);
    void setFormatComment(const QTextCharFormat& charFormat);
    void setFormatNumber(const QTextCharFormat& charFormat);

private slots:
    void updateLineNumberAreaWidth();
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);
    void insertCompletion(const QString& text);

private:
    class LineNumberArea : public QWidget
    {
    public:
        explicit LineNumberArea(QWidget* parent = nullptr);
        ~LineNumberArea() override = default;

        QSize sizeHint() const override;

    private:
        CoreEditor      *m_editor = nullptr;

        void paintEvent(QPaintEvent* event) override;
    };

    LineNumberArea  *m_lineNumberArea       = new LineNumberArea(this);
    QCompleter      *m_completer            = new QCompleter(this);
    Highlighter     *m_highlighter          = nullptr;
    QColor          m_lineColor;
    QColor          m_otherTextColor;
    bool            m_visibleLineNumberAre  = true;

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // COREEDITOR_H