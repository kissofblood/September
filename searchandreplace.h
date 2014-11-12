#ifndef SEARCHANDREPLACE_H
#define SEARCHANDREPLACE_H

#include "septembereditor.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextDocument>
#include <QBrush>
#include <QColor>
#include <QMessageBox>
#include <QVector>
#include <QPair>
#include <QKeySequence>
#include <QRegExp>
#include <QCheckBox>

namespace Ui {
class SearchAndReplace;
}

class SearchAndReplace : public QWidget
{
    Q_OBJECT
public:
    explicit SearchAndReplace(QWidget* parent = nullptr);
    ~SearchAndReplace() override;

    void setFocusEditSearch();

private slots:
    void searchText();
    void nextSearchText();
    void prevSearchText();
    void setRegister(int state);
    void setRegExp(int state);
    void replace();

private:
    Ui::SearchAndReplace    *ui                 = nullptr;
    SeptemberEditor         *m_editor           = nullptr;
    QMessageBox             *m_msgBox           = new QMessageBox(this);
    QPushButton             *m_btnOk            = nullptr;
    QFlags<QTextDocument::FindFlag> m_findFlag  = QTextDocument::FindWholeWords;
    QVector<QPair<QTextCursor, QTextCharFormat>> m_textCharFormatUndo_;
    int     m_posCursor = 0;
    bool    m_isRegExp  = false;
};

#endif // SEARCHANDREPLACE_H
