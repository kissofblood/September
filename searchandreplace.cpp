#include "searchandreplace.h"
#include "ui_searchandreplace.h"

SearchAndReplace::SearchAndReplace(QWidget* parent) : QWidget(parent),
    ui(new Ui::SearchAndReplace),
    m_editor(parent->parent()->findChild<CoreEditor*>())
{
    ui->setupUi(this);
    ui->btnNext->setShortcut(Qt::CTRL + Qt::Key_Up);
    ui->btnPrev->setShortcut(Qt::CTRL + Qt::Key_Down);
    m_btnOk = m_msgBox->addButton("Да", QMessageBox::AcceptRole);
    m_msgBox->addButton("Нет", QMessageBox::RejectRole);
    m_msgBox->setIcon(QMessageBox::Information);

    this->connect(ui->btnSearch,        &QPushButton::clicked,       this, &SearchAndReplace::searchText);
    this->connect(ui->editSearch,       &QLineEdit::returnPressed,   this, &SearchAndReplace::searchText);
    this->connect(ui->editReplace,      &QLineEdit::returnPressed,   this, &SearchAndReplace::replaceText);
    this->connect(ui->btnNext,          &QPushButton::clicked,       this, &SearchAndReplace::nextSearchText);
    this->connect(ui->btnPrev,          &QPushButton::clicked,       this, &SearchAndReplace::prevSearchText);
    this->connect(ui->btnReplace,       &QPushButton::clicked,       this, &SearchAndReplace::replaceText);
    this->connect(ui->checkRegister,    &QCheckBox::stateChanged,    this, &SearchAndReplace::setRegister);
    this->connect(ui->checkRegEx,       &QCheckBox::stateChanged,    this, &SearchAndReplace::setRegExp);
    this->connect(ui->checkReplaceAll,  &QCheckBox::stateChanged,    this, &SearchAndReplace::setReplaceTextAll);
    this->connect(ui->editSearch, &QLineEdit::textChanged, this, [this](const QString& text)
    {
        if(text.isEmpty())
        {
            QPalette pal = ui->editSearch->palette();
            pal.setColor(ui->editSearch->backgroundRole(), Qt::transparent);
            ui->editSearch->setPalette(pal);
            m_editor->clearSelectTextSearch();
        }
    });

    m_settingKey->addItem("Поиск и Замена", ui->btnNext->text(), ui->btnNext->shortcut().toString());
    m_settingKey->addItem("Поиск и Замена", ui->btnPrev->text(), ui->btnPrev->shortcut().toString());
}

SearchAndReplace::~SearchAndReplace()
{ delete ui; }

void SearchAndReplace::setFocusEditSearch()
{ ui->editSearch->setFocus(); }

void SearchAndReplace::clearResultSearch()
{
    clearTextCharFormatUndo();
    ui->editReplace->clear();
    ui->editSearch->clear();
}

void SearchAndReplace::searchText()
{
    m_editor = this->parent()->findChild<CoreEditor*>();
    m_editor->clearSelectTextSearch();
    QString textSearch = ui->editSearch->text();
    clearTextCharFormatUndo();
    if(textSearch.isEmpty())
        return;

    QTextCursor highlightCursor(m_editor->document());

    QTextCharFormat colorFormat = highlightCursor.charFormat();
    colorFormat.setBackground(QBrush(QColor(85, 85, 0)));
    while(!highlightCursor.isNull() && !highlightCursor.atEnd())
    {
        if(!m_isRegExp)
            highlightCursor = m_editor->document()->find(textSearch, highlightCursor, m_findFlag);
        else
        {
            QRegExp regExp(R"()" + textSearch + R"()");
            if(m_findFlag == QTextDocument::FindWholeWords)
                regExp.setCaseSensitivity(Qt::CaseInsensitive);
            else
                regExp.setCaseSensitivity(Qt::CaseSensitive);
            highlightCursor = m_editor->document()->find(regExp, highlightCursor);
        }

        if(!highlightCursor.isNull())
        {
            m_textCharFormatUndo_.push_back({ highlightCursor, highlightCursor.charFormat() });
            m_editor->selectTextSearch(highlightCursor, highlightCursor.charFormat());
            highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor, 0);
            highlightCursor.mergeCharFormat(colorFormat);
        }
    }

    m_posCursor = -1;
    QPalette pal = ui->editSearch->palette();
    if(m_textCharFormatUndo_.empty())
        pal.setColor(ui->editSearch->backgroundRole(), QColor(Qt::red).lighter(180));
    else
    {
        nextSearchText();
        pal.setColor(ui->editSearch->backgroundRole(), Qt::transparent);
    }

    ui->editSearch->setPalette(pal);
}

void SearchAndReplace::nextSearchText()
{
    if(m_textCharFormatUndo_.empty())
        return;
    QTextCursor cursor(m_editor->document());
    if(m_posCursor < 0)
        m_posCursor = -1;
    m_posCursor += 1;
    if(m_posCursor < m_textCharFormatUndo_.size())
    {
        selectTextSearch();
        cursor.setPosition(m_textCharFormatUndo_[m_posCursor].first.position());
        m_editor->setTextCursor(cursor);
    }
    else
    {
        m_msgBox->setText("Достигнуто конец документа, продолжать с начало?");
        m_msgBox->exec();

        if(m_btnOk == m_msgBox->clickedButton())
        {
            m_posCursor = 0;
            selectTextSearch();
            cursor.setPosition(m_textCharFormatUndo_[m_posCursor].first.position());
            m_editor->setTextCursor(cursor);
        }
    }
}

void SearchAndReplace::prevSearchText()
{
    if(m_textCharFormatUndo_.empty())
        return;
    QTextCursor cursor(m_editor->document());
    if(m_posCursor >= m_textCharFormatUndo_.size() || m_posCursor == -1)
        m_posCursor = m_textCharFormatUndo_.size();
    m_posCursor -= 1;
    if(m_posCursor >= 0)
    {
        selectTextSearch();
        cursor.setPosition(m_textCharFormatUndo_[m_posCursor].first.position());
        m_editor->setTextCursor(cursor);
    }
    else
    {
        m_msgBox->setText("Достигнуто начало документа, продолжать с конца?");
        m_msgBox->exec();

        if(m_btnOk == m_msgBox->clickedButton())
        {
            m_posCursor = m_textCharFormatUndo_.size() - 1;
            selectTextSearch();
            cursor.setPosition(m_textCharFormatUndo_[m_posCursor].first.position());
            m_editor->setTextCursor(cursor);
        }
    }
}

void SearchAndReplace::setRegister(int state)
{
    if(state == 0)
        m_findFlag = QTextDocument::FindWholeWords;
    else if(state == 2)
        m_findFlag = QTextDocument::FindWholeWords | QTextDocument::FindCaseSensitively;
}

void SearchAndReplace::setRegExp(int state)
{
    if(state == 0)
        m_isRegExp = false;
    else if(state == 2)
        m_isRegExp = true;
}

void SearchAndReplace::setReplaceTextAll(int state)
{
    if(state == 0)
        m_isReplaceAll = false;
    else if(state == 2)
        m_isReplaceAll = true;
}

void SearchAndReplace::replaceText()
{
    QString text = ui->editReplace->text();
    if(text.isEmpty())
        return;
    else if(m_textCharFormatUndo_.empty())
        return;

    if(m_isReplaceAll)
    {
        for(auto& pair : m_textCharFormatUndo_)
        {
            pair.first.removeSelectedText();
            pair.first.insertText(text);
        }
        return;
    }

    int pos = m_posCursor;
    if(m_posCursor < 0)
        pos = 0;
    else if(m_posCursor >= m_textCharFormatUndo_.size())
        pos = m_textCharFormatUndo_.size() - 1;
    m_textCharFormatUndo_[pos].first.removeSelectedText();
    m_textCharFormatUndo_[pos].first.insertText(text);
}

void SearchAndReplace::selectTextSearch()
{
    QTextCharFormat format = m_textCharFormatUndo_[m_posCursor].second;
    format.setBackground(QBrush(QColor(160, 160, 160)));
    format.setForeground(QBrush(QColor(12, 12, 12)));
    m_editor->replaceSelectTextSearch(m_textCharFormatUndo_[m_posCursor].first, format, m_textCharFormatUndo_[m_posCursor].second);

}

void SearchAndReplace::clearTextCharFormatUndo()
{
    for(auto& pair : m_textCharFormatUndo_)
    {
        pair.second.setBackground(Qt::transparent);
        pair.first.mergeCharFormat(pair.second);
    }
    m_textCharFormatUndo_.clear();
}
