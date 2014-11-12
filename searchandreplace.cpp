#include "searchandreplace.h"
#include "ui_searchandreplace.h"

SearchAndReplace::SearchAndReplace(QWidget* parent) : QWidget(parent),
    ui(new Ui::SearchAndReplace),
    m_editor(qobject_cast<SeptemberEditor*>(parent->parent()))
{
    ui->setupUi(this);
    ui->btnNext->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Up));
    ui->btnPrev->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Down));
    m_btnOk = m_msgBox->addButton("Да", QMessageBox::AcceptRole);
    m_msgBox->addButton("Нет", QMessageBox::RejectRole);
    m_msgBox->setIcon(QMessageBox::Information);

    this->connect(ui->btnSearch,        &QPushButton::clicked,       this, &SearchAndReplace::searchText);
    this->connect(ui->editSearch,       &QLineEdit::returnPressed,   this, &SearchAndReplace::searchText);
    this->connect(ui->btnNext,          &QPushButton::clicked,       this, &SearchAndReplace::nextSearchText);
    this->connect(ui->btnPrev,          &QPushButton::clicked,       this, &SearchAndReplace::prevSearchText);
    this->connect(ui->checkRegister,    &QCheckBox::stateChanged,    this, &SearchAndReplace::setRegister);
    this->connect(ui->checkRegEx,       &QCheckBox::stateChanged,    this, &SearchAndReplace::setRegExp);
}

SearchAndReplace::~SearchAndReplace()
{ delete ui; }

void SearchAndReplace::setFocusEditSearch()
{ ui->editSearch->setFocus(); }

void SearchAndReplace::searchText()
{
    QString textSearch = ui->editSearch->text();

    for(auto& pair : m_textCharFormatUndo_)
    {
        pair.second.setBackground(Qt::transparent);
        pair.first.mergeCharFormat(pair.second);
    }
    m_textCharFormatUndo_.clear();
    if(textSearch.isEmpty())
        return;

    QTextCursor highlightCursor(m_editor->getDocument());
    QTextCursor cursor(m_editor->getDocument());

    cursor.beginEditBlock();

    QTextCharFormat colorFormat = highlightCursor.charFormat();
    colorFormat.setBackground(QBrush(QColor(85, 85, 0)));
    while(!highlightCursor.isNull() && !highlightCursor.atEnd())
    {
        if(!m_isRegExp)
            highlightCursor = m_editor->getDocument()->find(textSearch, highlightCursor, m_findFlag);
        else
        {
            QRegExp regExp(R"()" + textSearch + R"()");
            if(m_findFlag == QTextDocument::FindWholeWords)
                regExp.setCaseSensitivity(Qt::CaseInsensitive);
            else
                regExp.setCaseSensitivity(Qt::CaseSensitive);
            highlightCursor = m_editor->getDocument()->find(regExp, highlightCursor);
        }

        if(!highlightCursor.isNull())
        {
            m_textCharFormatUndo_.push_back({ highlightCursor, highlightCursor.charFormat() });
            highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor, 0);
            highlightCursor.mergeCharFormat(colorFormat);
        }
    }

    cursor.endEditBlock();
    m_posCursor = -1;
    if(!m_textCharFormatUndo_.empty())
    {
        QTextCursor cursorFirst(m_editor->getDocument());
        cursorFirst.setPosition(m_textCharFormatUndo_[0].first.position());
        m_editor->setPositionCursor(cursor);
    }
}

void SearchAndReplace::nextSearchText()
{
    if(m_textCharFormatUndo_.empty())
        return;
    QTextCursor cursor(m_editor->getDocument());
    if(m_posCursor < 0)
        m_posCursor = -1;
    m_posCursor += 1;
    if(m_posCursor < m_textCharFormatUndo_.size())
    {
        cursor.setPosition(m_textCharFormatUndo_[m_posCursor].first.position());
        m_editor->setPositionCursor(cursor);

    }
    else
    {
        m_msgBox->setText("Достигнуто конец документа, продолжать с начало?");
        m_msgBox->exec();

        if(m_btnOk == m_msgBox->clickedButton())
        {
            m_posCursor = 0;
            cursor.setPosition(m_textCharFormatUndo_[m_posCursor].first.position());
            m_editor->setPositionCursor(cursor);
        }
    }
}

void SearchAndReplace::prevSearchText()
{
    if(m_textCharFormatUndo_.empty())
        return;
    QTextCursor cursor(m_editor->getDocument());
    if(m_posCursor >= m_textCharFormatUndo_.size() || m_posCursor == -1)
        m_posCursor = m_textCharFormatUndo_.size();
    m_posCursor -= 1;
    if(m_posCursor >= 0)
    {
        cursor.setPosition(m_textCharFormatUndo_[m_posCursor].first.position());
        m_editor->setPositionCursor(cursor);
    }
    else
    {
        m_msgBox->setText("Достигнуто начало документа, продолжать с конца?");
        m_msgBox->exec();

        if(m_btnOk == m_msgBox->clickedButton())
        {
            m_posCursor = m_textCharFormatUndo_.size() - 1;
            cursor.setPosition(m_textCharFormatUndo_[m_posCursor].first.position());
            m_editor->setPositionCursor(cursor);
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
