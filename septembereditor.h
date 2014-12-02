#ifndef SEPTEMBEREDITOR_H
#define SEPTEMBEREDITOR_H

#include "setting/settingkey.h"
#include "setting/settingseptember.h"
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
#include <QString>

namespace Ui {
class SeptemberEditor;
}

class SeptemberEditor : public QMainWindow
{
    Q_OBJECT
public:
    explicit SeptemberEditor(QWidget* parent = nullptr);
    ~SeptemberEditor() override;

private slots:
    void closeOrShowListFile();
    void closeOrShowWidgetSearchAndReplace();
    void closeOrShowCreateWidget();
    void closeOrShowOpenUI();
    void openFile();
    void lineWrap(bool trigger);
    void fullScreen(bool trigger);
    void pathFile(bool trigger);
    void setStatusBar();
    void saveFile();
    void saveFileAs();

private:
    struct ClickedButton
    {
        bool searchAndReplace   = false;
        bool createWidget       = false;
        bool openUI             = false;
    };
    Ui::SeptemberEditor         *ui = nullptr;
    SettingKey                  *m_settingKey       = new SettingKey(this);
    SettingSeptember            *m_settingSeptember = new SettingSeptember(this);
    ClickedButton               m_clickedButton;
    QFileInfo                   m_fileInfo;
    bool                        m_visiblePathFile   = false;
};

#endif // SEPTEMBEREDITOR_H
