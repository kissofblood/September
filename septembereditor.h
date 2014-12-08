#ifndef SEPTEMBEREDITOR_H
#define SEPTEMBEREDITOR_H

#include "setting/settingkey.h"
#include "setting/settingseptember.h"
#include "assistant/fileView/listfilemodel.h"
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
#include <QDirModel>

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
    void newFile(const QString& name = "Безымянный");
    void switchTreeFileView();
    void switchListFileView();
    void closeFile(int row);
    void selectFile(const QModelIndex& index);

private:
    struct ClickedButton
    {
        bool searchAndReplace   = false;
        bool createWidget       = false;
        bool openUI             = false;
    };
    Ui::SeptemberEditor         *ui                 = nullptr;
    SettingKey                  *m_settingKey       = new SettingKey(this);
    SettingSeptember            *m_settingSeptember = new SettingSeptember(this);
    ListFileModel               *m_listModel        = new ListFileModel(this);
    ClickedButton               m_clickedButton;
    QFileInfo                   m_fileInfo;
    QVector<QMetaObject::Connection> m_connectionCoreEditor;
    bool                        m_visiblePathFile   = false;

    void connectionCoreEditor(CoreEditor* coreEditor);
};

#endif // SEPTEMBEREDITOR_H
