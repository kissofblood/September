#ifndef COREEDITOR_H
#define COREEDITOR_H

#include "keywords.h"
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
    bool            m_visibleLineNumberAre  = true;

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // COREEDITOR_H
