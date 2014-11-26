#include "coreeditor.h"

CoreEditor::CoreEditor(QWidget* parent) : QPlainTextEdit(parent)
    , m_lineColor(26, 21, 21)
    , m_otherTextColor(170, 170, 170)
{
    QStringList properties = KeyWords::keyWordsFromFile("listOfProperties") + KeyWords::keyWordsFromFile("listOfIcons");
    QStringList pseudo = KeyWords::keyWordsFromFile("listOfPseudo-States");
    QStringList widgets =  KeyWords::keyWordsFromFile("listOfStylableWidgets");
    QStringList sub = KeyWords::keyWordsFromFile("listOfSub-Controls");
    QStringList other = KeyWords::keyWordsFromFile("other");
    m_highlighter = new Highlighter(properties, pseudo, widgets, sub, other, this->document());
    m_observerCode = new ObserverCodeQss(properties, pseudo, widgets, sub, other, this);
    m_completer->setWidget(this);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    m_blockNumberError_.push_back(false);

    this->connect(this, &QPlainTextEdit::blockCountChanged,     this, std::bind(&CoreEditor::updateLineNumberAreaWidth, this));
    this->connect(this, &QPlainTextEdit::blockCountChanged,     this, &CoreEditor::insertOrRemove);
    this->connect(this, &QPlainTextEdit::updateRequest,         this, &CoreEditor::updateLineNumberArea);
    this->connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CoreEditor::highlightCurrentLine);
    this->connect(m_completer, SIGNAL(activated(QString)), SLOT(insertCompletion(QString)));
    this->connect(this, &QPlainTextEdit::cursorPositionChanged, this, [this]()
    {
        QTextCursor cursor = this->textCursor();
        cursor.select(QTextCursor::BlockUnderCursor);

        QTextCursor startBlock = this->textCursor();
        startBlock.movePosition(QTextCursor::StartOfBlock, QTextCursor::KeepAnchor);

        m_observerCode->textParserBody(this->document()->toPlainText().left(this->textCursor().position()));
        m_observerCode->textParserHead(cursor.selectedText().left(this->textCursor().position() - startBlock.position() + 1));
    });
    this->connect(m_observerCode, &ObserverCodeQss::stringListModelChanged, m_completer, &QCompleter::setModel);
    this->setFocus();

    updateLineNumberAreaWidth();
    highlightCurrentLine();
    setDocumentColor(Qt::black);
    this->document()->setDefaultFont(QFont("Droid Sans Mono", 12, QFont::Monospace));
}

void CoreEditor::setVisibleLineNimberArea(bool value)
{
    m_visibleLineNumberAre = value;
    m_lineNumberArea->update();
}

void CoreEditor::insertOrRemove(int block)
{
    if(m_blockNumberError_.size() < block)
        m_blockNumberError_.push_back(false);
    else
        m_blockNumberError_.pop_back();
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

void CoreEditor::checkingCodeQss()
{
    QTextDocument* doc = this->document();
    std::string stdString = doc->toPlainText().toStdString();
    QTextBlock textBlock = doc->begin();
    for(auto& numError : m_observerCode->checkingCodeQss(stdString, textBlock))
        m_blockNumberError_[numError - 1] = true;
    m_lineNumberArea->update();
}

void CoreEditor::appendText(const QString& text)
{
    this->clear();
    this->appendPlainText(text);
    m_blockNumberError_.clear();
    for(int i = 0; i < this->blockCount(); i++)
        m_blockNumberError_.push_back(false);
}

void CoreEditor::updateLineNumberAreaWidth()
{ this->setViewportMargins(lineNumberAreaWidth(), 0, 0, 1); }

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
    cursor.select(QTextCursor::WordUnderCursor);
    if((cursor.selectedText().end() - 1)->isLetter())
        cursor.removeSelectedText();
    else
        cursor.setPosition(cursor.position());
    cursor.insertText(text);
    this->setTextCursor(cursor);
}

void CoreEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), QColor(35, 35, 35));

    QTextBlock block = this->firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = this->blockBoundingGeometry(block).translated(this->contentOffset()).top();
    int bottom = top + this->blockBoundingRect(block).height();

    while(block.isValid() && top <= event->rect().bottom())
    {
        if(block.isVisible() && bottom >= event->rect().top())
        {
            if(m_blockNumberError_[blockNumber])
            {
                painter.setBrush(Qt::red);
                painter.setPen(Qt::transparent);
                painter.drawRect(0, top, m_lineNumberArea->width(), this->fontMetrics().height());
            }

            if(!m_visibleLineNumberAre)
                return;

            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(136, 136, 136));
            painter.setFont(QFont("Areal", -1, QFont::Bold));
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

void CoreEditor::zoomDocIn()
{
    m_zoomDocument += 1;
    this->zoomIn();
    this->document()->setDefaultFont(QFont("Droid Sans Mono", m_zoomDocument, QFont::Monospace));
}

void CoreEditor::zoomDocOut()
{
    m_zoomDocument -= 1;
    if(m_zoomDocument < 1)
        m_zoomDocument = 1;
    this->zoomOut();
    this->document()->setDefaultFont(QFont("Droid Sans Mono", m_zoomDocument, QFont::Monospace));
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

        if(completePrefix.isEmpty() || !(completePrefix.end() - 1)->isLetter())
            m_completer->setCompletionPrefix(QString());
        else
        {
            if(completePrefix != m_completer->completionPrefix())
            {
                m_completer->setCompletionPrefix(completePrefix);
                m_completer->popup()->setCurrentIndex(m_completer->completionModel()->index(0, 0));
            }
        }

        QRect rect = this->cursorRect();
        rect.setWidth(m_completer->popup()->sizeHintForColumn(0) + m_completer->popup()->verticalScrollBar()->sizeHint().width());

        m_completer->complete(rect);
    }
}

void CoreEditor::wheelEvent(QWheelEvent* event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->delta() > 0)
            zoomDocIn();
        else
            zoomDocOut();
    }
    QPlainTextEdit::wheelEvent(event);
}

CoreEditor::LineNumberArea::LineNumberArea(CoreEditor* parent) : QWidget(parent)
  , m_editor(parent)
{ }

QSize CoreEditor::LineNumberArea::sizeHint() const
{ return { m_editor->lineNumberAreaWidth(), 0 }; }

void CoreEditor::LineNumberArea::paintEvent(QPaintEvent* event)
{ m_editor->lineNumberAreaPaintEvent(event); }
