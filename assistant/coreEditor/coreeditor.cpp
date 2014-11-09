#include "coreeditor.h"

CoreEditor::CoreEditor(QWidget* parent) : QPlainTextEdit(parent)
    , m_lineColor(26, 21, 21)
    , m_otherTextColor(170, 170, 170)
{   
    QStringList icons = KeyWords::keyWordsFromFile("listOfIcons");
    QStringList properties = KeyWords::keyWordsFromFile("listOfProperties");
    QStringList pseudo = KeyWords::keyWordsFromFile("listOfPseudo-States");
    QStringList widgets =  KeyWords::keyWordsFromFile("listOfStylableWidgets");
    QStringList sub = KeyWords::keyWordsFromFile("listOfSub-Controls");
    m_completer->setWidget(this);
    m_completer->setModel(new QStringListModel(widgets, this));
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    m_highlighter = new Highlighter(icons, properties, pseudo, widgets, sub,  this->document());

    this->connect(this, &QPlainTextEdit::blockCountChanged,     this, std::bind(&CoreEditor::updateLineNumberAreaWidth, this));
    this->connect(this, &QPlainTextEdit::updateRequest,         this, &CoreEditor::updateLineNumberArea);
    this->connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CoreEditor::highlightCurrentLine);
    this->connect(m_completer, SIGNAL(activated(QString)), SLOT(insertCompletion(QString)));
    this->setFocus();

    updateLineNumberAreaWidth();
    highlightCurrentLine();
    setDocumentColor(QColor(Qt::black));
    this->document()->setDefaultFont(QFont("Droid Sans Mono", 12, QFont::Monospace));
}

void CoreEditor::setVisibleLineNimberArea(bool value)
{
    m_visibleLineNumberAre = value;
    m_lineNumberArea->update();
}

void CoreEditor::setDocumentColor(const QColor& color)
{
    QPalette pal;
    pal.setColor(QPalette::Text, m_otherTextColor);
    pal.setColor(QPalette::Base, color);
    this->setPalette(pal);
}

void CoreEditor::setLineColor(const QColor& color)
{ m_lineColor = color; }

void CoreEditor::setOtherTextColor(const QColor& color)
{ m_otherTextColor = color; }

void CoreEditor::setFormatIcons(const QTextCharFormat& charFormat)
{ m_highlighter->setFormatIcons(charFormat); }

void CoreEditor::setFormatProperties(const QTextCharFormat& charFormat)
{ m_highlighter->setFormatProperties(charFormat); }

void CoreEditor::setFormatPseudo(const QTextCharFormat& charFormat)
{ m_highlighter->setFormatPseudo(charFormat); }

void CoreEditor::setFormatWidgets(const QTextCharFormat& charFormat)
{ m_highlighter->setFormatWidgets(charFormat); }

void CoreEditor::setFormatSub(const QTextCharFormat& charFormat)
{ m_highlighter->setFormatSub(charFormat); }

void CoreEditor::setFormatComment(const QTextCharFormat& charFormat)
{ m_highlighter->setFormatComment(charFormat); }

void CoreEditor::setFormatNumber(const QTextCharFormat& charFormat)
{ m_highlighter->setFormatNumber(charFormat); }

void CoreEditor::updateLineNumberAreaWidth()
{ this->setViewportMargins(lineNumberAreaWidth() + 5, 0, 0, 5); }

void CoreEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    if(!this->isReadOnly())
    {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(m_lineColor);
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

void CoreEditor::insertCompletion(const QString& text)
{
    QTextCursor cursor = this->textCursor();
    int numberOfCharsToComplete = text.length() - m_completer->completionPrefix().length();
    cursor.movePosition(QTextCursor::EndOfWord);
    cursor.insertText(text.right(numberOfCharsToComplete));
    this->setTextCursor(cursor);
}

void CoreEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    if(!m_visibleLineNumberAre)
        return;

    QTextBlock block = this->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = this->blockBoundingGeometry(block).translated(this->contentOffset()).top();
    int bottom = top + this->blockBoundingRect(block).height();

    while(block.isValid() && top <= event->rect().bottom())
    {
        if(block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, m_lineNumberArea->width(), this->fontMetrics().height(), Qt::AlignCenter, number);
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
    int max = this->blockCount();
    while(max >= 10)
    {
        max /= 10;
        digits++;
    }

    return 10 + this->fontMetrics().width('0') * digits;
}

void CoreEditor::resizeEvent(QResizeEvent* event)
{
    QRect rect = this->contentsRect();
    m_lineNumberArea->setGeometry({ rect.left(), rect.top(), lineNumberAreaWidth(), rect.height() });
    QPlainTextEdit::resizeEvent(event);
}

void CoreEditor::keyPressEvent(QKeyEvent* event)
{
    static bool flagKey = false;
    if(m_completer->popup()->isVisible())
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return
            || event->key() == Qt::Key_Escape || event->key() == Qt::Key_Tab)
        {
            flagKey = false;
            event->ignore();
            return;
        }

    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Space)
        flagKey = true;

    if(!(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Space))
        QPlainTextEdit::keyPressEvent(event);

    if((event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Space) || flagKey)
    {
        QTextCursor cursor = this->textCursor();
        cursor.select(QTextCursor::WordUnderCursor);
        QString completePrefix = cursor.selectedText();
        if(!completePrefix.isEmpty() && (completePrefix.end() - 1)->isLetter())
        {
            if(completePrefix != m_completer->completionPrefix())
            {
                m_completer->setCompletionPrefix(completePrefix);
                m_completer->popup()->setCurrentIndex(m_completer->completionModel()->index(0, 0));
            }

            QRect rect = this->cursorRect();
            rect.setWidth(m_completer->popup()->sizeHintForColumn(0) + m_completer->popup()->verticalScrollBar()->sizeHint().width());
            m_completer->complete(rect);
        }
    }
}

CoreEditor::LineNumberArea::LineNumberArea(QWidget* parent) : QWidget(parent)
  , m_editor(qobject_cast<CoreEditor*>(parent))
{ }

QSize CoreEditor::LineNumberArea::sizeHint() const
{ return { m_editor->lineNumberAreaWidth(), 0 }; }

void CoreEditor::LineNumberArea::paintEvent(QPaintEvent* event)
{ m_editor->lineNumberAreaPaintEvent(event); }
