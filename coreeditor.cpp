#include "coreeditor.h"

CoreEditor::CoreEditor(QWidget* parent) : QPlainTextEdit(parent)
{
    this->connect(this, &QPlainTextEdit::blockCountChanged, this, std::bind(&CoreEditor::updateLineNumberAreaWidth, this));
    this->connect(this, &QPlainTextEdit::updateRequest, this, &CoreEditor::updateLineNumberArea);
    this->connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CoreEditor::highlightCurrentLine);

    updateLineNumberAreaWidth();
    highlightCurrentLine();
}

void CoreEditor::updateLineNumberAreaWidth()
{ this->setViewportMargins(lineNumberAreaWidth(), 0, 0, 0); }

void CoreEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    if(!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = this->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    this->setExtraSelections(extraSelections);
}

void CoreEditor::updateLineNumberArea(const QRect& rect, int dy)
{
    if(dy != 0)
        m_lineNumberArea->scroll(0, dy);
    else
        m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());

    if(rect.contains(this->viewport()->rect()))
        updateLineNumberAreaWidth();
}

void CoreEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = this->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = this->blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + this->blockBoundingRect(block).height();

    while(block.isValid() && top <= event->rect().bottom())
    {
        if(block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, m_lineNumberArea->width(), this->fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + this->blockBoundingRect(block).height();
        blockNumber++;
    }
}

int CoreEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, this->blockCount());
    while(max >= 10)
    {
        max /= 10;
        digits++;
    }

    return 3 + this->fontMetrics().width('0') * digits;
}

void CoreEditor::resizeEvent(QResizeEvent* event)
{
    QRect rect = this->contentsRect();
    m_lineNumberArea->setGeometry(QRect(rect.left(), rect.top(), lineNumberAreaWidth(), rect.height()));
    QPlainTextEdit::resizeEvent(event);
}

CoreEditor::LineNumberArea::LineNumberArea(QWidget* parent) : QWidget(parent)
  , m_editor(qobject_cast<CoreEditor*>(parent))
{ }

QSize CoreEditor::LineNumberArea::sizeHint() const
{ return QSize(m_editor->lineNumberAreaWidth(), 0); }

void CoreEditor::LineNumberArea::paintEvent(QPaintEvent* event)
{ m_editor->lineNumberAreaPaintEvent(event); }
