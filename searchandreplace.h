#ifndef SEARCHANDREPLACE_H
#define SEARCHANDREPLACE_H

#include "assistant/coreEditor/coreeditor.h"
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
#include <QRegExp>
#include <QCheckBox>
#include <QFlags>

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
    void cleanResultSearch();

private slots:
    void searchText();
    void nextSearchText();
    void prevSearchText();
    void setRegister(int state);
    void setRegExp(int state);
    void setReplaceTextAll(int state);
    void replaceText();

private:
    Ui::SearchAndReplace    *ui                 = nullptr;
    CoreEditor              *m_editor           = nullptr;
    QMessageBox             *m_msgBox           = new QMessageBox(this);
    QPushButton             *m_btnOk            = nullptr;
    QFlags<QTextDocument::FindFlag> m_findFlag  = QTextDocument::FindWholeWords;
    QVector<QPair<QTextCursor, QTextCharFormat>> m_textCharFormatUndo_;
    int     m_posCursor     = 0;
    bool    m_isRegExp      = false;
    bool    m_isReplaceAll  = false;

    void selectTextSearch();
};

#endif // SEARCHANDREPLACE_H
