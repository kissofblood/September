#ifndef SEPTEMBEREDITOR_H
#define SEPTEMBEREDITOR_H

#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QKeySequence>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QAction>
#include <QTextDocument>
#include <QTextCursor>
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <functional>

namespace Ui {
class SeptemberEditor;
}

class SeptemberEditor : public QMainWindow
{
    Q_OBJECT
public:
    explicit SeptemberEditor(QWidget* parent = nullptr);
    ~SeptemberEditor() override;

    QTextDocument* getDocument() const;
    void setPositionCursor(const QTextCursor& cursor);

private slots:
    void closeOrShowListFile();
    void closeOrShowWidgetSearchAndReplace();
    void closeOrShowCreateWidget();
    void closeOrShowOpenUI();
    void openFile();

    void qwer()
    {
        closeOrShowCreateWidget();
    }

private:
    struct ClickedButton
    {
        bool searchAndReplace   = false;
        bool createWidget       = false;
        bool openUI             = false;
    };
    Ui::SeptemberEditor         *ui = nullptr;
    ClickedButton               m_clickedButton;
};

#endif // SEPTEMBEREDITOR_H
