#include "searchandreplace.h"
#include "ui_searchandreplace.h"

SearchAndReplace::SearchAndReplace(QWidget* parent) : QWidget(parent),
    ui(new Ui::SearchAndReplace),
    m_editor(qobject_cast<SeptemberEditor*>(parent->parent()))
{
    ui->setupUi(this);

    this->connect(ui->btnSearch,    &QPushButton::clicked,       this, &SearchAndReplace::searchText);
    this->connect(ui->editSearch,   &QLineEdit::returnPressed,   this, &SearchAndReplace::searchText);
}

SearchAndReplace::~SearchAndReplace()
{ delete ui; }

void SearchAndReplace::searchText()
{
    static QString text;
    QString textSearch = ui->editSearch->text();

    if(text != textSearch)
    {
        for(auto& pair : m_textCharFormatUndo_)
        {
            pair.second.setBackground(Qt::transparent);
            pair.first.mergeCharFormat(pair.second);
        }
        m_textCharFormatUndo_.clear();
        text = textSearch;
    }
    if(textSearch.isEmpty())
        return;

    QTextCursor highlightCursor(m_editor->getDocument());
    QTextCursor cursor(m_editor->getDocument());

    cursor.beginEditBlock();

    QTextCharFormat colorFormat = highlightCursor.charFormat();
    colorFormat.setForeground(QBrush(QColor(170, 170, 170)));
    colorFormat.setBackground(QBrush(QColor(85, 85, 0)));
    while(!highlightCursor.isNull() && !highlightCursor.atEnd())
    {
        highlightCursor = m_editor->getDocument()->find(textSearch, highlightCursor, QTextDocument::FindWholeWords);

        if(!highlightCursor.isNull())
        {
            if(text == textSearch)
                m_textCharFormatUndo_.push_back({ highlightCursor, highlightCursor.charFormat() });
            highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor, 0);
            highlightCursor.mergeCharFormat(colorFormat);
        }
    }

    cursor.endEditBlock();
}
