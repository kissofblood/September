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

#include <QtWidgets>

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

private:
    Ui::SearchAndReplace    *ui         = nullptr;
    SeptemberEditor         *m_editor   = nullptr;
    QVector<QPair<QTextCursor, QTextCharFormat>> m_textCharFormatUndo_;
};

#endif // SEARCHANDREPLACE_H
