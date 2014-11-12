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

namespace Ui {
class SearchAndReplace;
}

class SearchAndReplace : public QWidget
{
    Q_OBJECT
public:
    explicit SearchAndReplace(QWidget* parent = nullptr);
    ~SearchAndReplace() override;

private slots:
    void searchText();
    void nextSearchText();
    void prevSearchText();

private:
    Ui::SearchAndReplace    *ui             = nullptr;
    SeptemberEditor         *m_editor       = nullptr;
    QMessageBox             *m_msgBox       = new QMessageBox(this);
    QPushButton             *m_btnOk        = nullptr;
    QVector<QPair<QTextCursor, QTextCharFormat>> m_textCharFormatUndo_;
    int m_posCursor = 0;
};

#endif // SEARCHANDREPLACE_H
