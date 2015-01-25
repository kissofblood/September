#include "coreeditor.h"

CoreEditor::CoreEditor(QWidget* parent) : QPlainTextEdit(parent)
    , m_lineColor(26, 21, 21)
    , m_otherTextColor(170, 170, 170)
    , m_backgroundDoc(Qt::black)
    , m_fontText(QFont("Droid Sans Mono", m_zoomDocument, QFont::Monospace))
{
    QStringList properties = Common::keyWordsFromFile("listOfProperties") + Common::keyWordsFromFile("listOfIcons");
    QStringList pseudo = Common::keyWordsFromFile("listOfPseudo-States");
    QStringList widgets =  Common::keyWordsFromFile("listOfStylableWidgets");
    QStringList sub = Common::keyWordsFromFile("listOfSub-Controls");
    QStringList other = Common::keyWordsFromFile("other");
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
    { m_observerCode->textParser(this->toPlainText().left(this->textCursor().position())); });
    this->connect(m_observerCode, &ObserverCodeQss::stringListModelChanged, m_completer, &QCompleter::setModel);
    this->connect(m_settingSeptember, &SettingSeptember::settingSeptemberOK, this, &CoreEditor::readValue);
    this->connect(this, &QPlainTextEdit::textChanged, this, [this]()
    {
        emit updateStyleSheet(this->document()->toPlainText());
        if(m_afterFile)
            emit textChangedAfterSetFile();
    });
    this->setFocus();
    this->setObjectName("plainTextEdit");

    m_settingSeptember->readScheme();
    if(m_settingSeptember->containsKey())
        readValue();
    else
    {
        QPalette pal;
        pal.setColor(QPalette::Text, m_otherTextColor);
        pal.setColor(QPalette::Base, m_backgroundDoc);
        this->setPalette(pal);
        m_settingSeptember->writeDefaultBackgroundColor(m_backgroundDoc);
        m_settingSeptember->writeDefaultCurrentLineColor(m_lineColor);
        m_settingSeptember->writeDefaultFontText(m_fontText);
        m_settingSeptember->writeDefaultWidthTab(4);
        m_settingSeptember->writeDefaultWidthIndent(m_indent);
        this->setTabStopWidth(40);
    }

    updateLineNumberAreaWidth();
    highlightCurrentLine();
    this->document()->setDefaultFont(m_fontText);
}

void CoreEditor::setVisibleLineNimberArea(bool value)
{
    m_visibleLineNumberAre = value;
    m_lineNumberArea->update();
}

void CoreEditor::autoCompletePathResource(const QStringList& list)
{ m_observerCode->addAutoComplete(list); }

void CoreEditor::insertOrRemove(int block)
{
    if(m_blockNumberError_.size() < block)
        m_blockNumberError_.push_back(false);
    else
        m_blockNumberError_.pop_back();
}

void CoreEditor::setOtherTextColor(const QColor& color)
{ m_otherTextColor = color; }

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

void CoreEditor::selectTextSearch(const QTextCursor& cursor, const QTextCharFormat& format)
{ m_selectTextSearch_.insert(cursor.blockNumber(), std::make_tuple(cursor, format, false)); }

void CoreEditor::replaceSelectTextSearch(const QTextCursor& cursor, const QTextCharFormat& formatNew, const QTextCharFormat& formatOld)
{
    for(auto i = m_selectTextSearch_.find(cursor.blockNumber()); i != m_selectTextSearch_.end(); i++)
    {
        QTextCursor cursorOld;
        QTextCharFormat format;
        bool selectFlag;
        std::tie(cursorOld, format, selectFlag) = i.value();
        if(selectFlag)
            i.value() = std::make_tuple(cursorOld, formatOld, false);
        else if(cursorOld == cursor)
            i.value() = std::make_tuple(cursor, formatNew, true);
    }
}

void CoreEditor::clearSelectTextSearch()
{
    m_selectTextSearch_.clear();
    highlightCurrentLine();
}

void CoreEditor::afterSetFileTrue()
{ m_afterFile = true; }

void CoreEditor::updateLineNumberAreaWidth()
{ this->setViewportMargins(lineNumberAreaWidth(), 0, 0, 1); }

void CoreEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    if(!this->isReadOnly())
    {
        QTextEdit::ExtraSelection selectionLine;
        selectionLine.format.setBackground(m_lineColor);
        selectionLine.format.setProperty(QTextFormat::FullWidthSelection, true);
        selectionLine.cursor = this->textCursor();
        selectionLine.cursor.clearSelection();
        extraSelections.push_back(selectionLine);

        for(auto i = m_selectTextSearch_.find(this->textCursor().blockNumber()); i != m_selectTextSearch_.end(); i++)
        {
            QTextCursor cursor;
            QTextCharFormat format;
            std::tie(cursor, format, std::ignore) = i.value();
            QTextEdit::ExtraSelection selectionSearch;
            selectionSearch.format = format;
            selectionSearch.cursor = cursor;
            extraSelections.push_back(selectionSearch);
        }
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
    cursor.movePosition(QTextCursor::WordLeft);
    cursor.select(QTextCursor::WordUnderCursor);
    QString selectedText = cursor.selectedText();
    int lenghtST = selectedText.length() - 1;
    if(lenghtST < 0) lenghtST = 0;
    if(selectedText[lenghtST].isLetter())
        cursor.removeSelectedText();
    cursor.setPosition(this->textCursor().position());
    cursor.insertText(text);
    this->setTextCursor(cursor);
}

void CoreEditor::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), m_backgroundDoc.darker());

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

            if(m_backgroundDoc == QColor(Qt::black))
                painter.setPen(QColor(136, 136, 136));
            else
                painter.setPen(m_backgroundDoc.lighter());
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
    m_fontText.setPixelSize(m_zoomDocument);
    this->document()->setDefaultFont(m_fontText);
}

void CoreEditor::zoomDocOut()
{
    m_zoomDocument -= 1;
    if(m_zoomDocument < 1)
        m_zoomDocument = 1;
    this->zoomOut();
    m_fontText.setPixelSize(m_zoomDocument);
    this->document()->setDefaultFont(m_fontText);
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
        cursor.movePosition(QTextCursor::WordLeft);
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
    else if(event->key() == Qt::Key_Return)
    {
        QString text = this->toPlainText().left(this->textCursor().position());
        for(int i = text.length() - 1; i >= 0; i--)
        {
            if(text[i] == '}' || text[i] == ',')
                return;
            if(text[i] == '{' || text[i] == ';')
            {
                for(int i = 0; i < m_indent; i++)
                    this->insertPlainText(QString(" "));
                break;
            }
        }
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

void CoreEditor::readValue()
{
    m_settingSeptember->addValueColor();
    m_settingSeptember->readSettingEditing();
    QPalette pal;
    m_backgroundDoc = m_settingSeptember->readBackgroundColor();
    pal.setColor(QPalette::Text, m_otherTextColor);
    pal.setColor(QPalette::Base, m_backgroundDoc);
    this->setPalette(pal);
    m_lineColor = m_settingSeptember->readCurrentLineColor();
    m_fontText = m_settingSeptember->readFontText();
    m_zoomDocument = m_fontText.pointSize();
    m_indent = m_settingSeptember->readWidthIndent();
    this->document()->setDefaultFont(m_fontText);
    this->setTabStopWidth(m_settingSeptember->readWidthTab() * 10);
    highlightCurrentLine();
}

CoreEditor::LineNumberArea::LineNumberArea(CoreEditor* parent) : QWidget(parent)
  , m_editor(parent)
{ }

QSize CoreEditor::LineNumberArea::sizeHint() const
{ return { m_editor->lineNumberAreaWidth(), 0 }; }

void CoreEditor::LineNumberArea::paintEvent(QPaintEvent* event)
{ m_editor->lineNumberAreaPaintEvent(event); }
