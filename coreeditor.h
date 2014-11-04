#ifndef COREEDITOR_H
#define COREEDITOR_H

#include <QWidget>
#include <QPlainTextEdit>
#include <functional>

#include <QtWidgets>

class CoreEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CoreEditor(QWidget* parent = nullptr);
    ~CoreEditor() override = default;

private slots:
    void updateLineNumberAreaWidth();
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);

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

    LineNumberArea      *m_lineNumberArea = new LineNumberArea(this);

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth();
    void resizeEvent(QResizeEvent* event) override;

};

#endif // COREEDITOR_H
