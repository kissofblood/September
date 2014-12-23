#ifndef SEPTEMBEREDITOR_H
#define SEPTEMBEREDITOR_H

#include "setting/settingkey.h"
#include "setting/settingseptember.h"
#include "setting/settingapp.h"
#include "src/fileView/listfilemodel.h"
#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QModelIndex>
#include <QFileInfo>
#include <QMetaObject>
#include <QPair>
#include <QAction>
#include <QFile>
#include <QKeySequence>
#include <QPushButton>
#include <functional>
#include <QLabel>
#include <QFileDialog>
#include <QIODevice>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QRegExp>
#include <QBuffer>
#include <QGraphicsScene>
#include <tuple>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QMessageBox>
#include <QFileInfoList>

#include <QDebug>

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
    void newFile(const QString& name);
    void closeFile(int row);
    void selectFile(const QModelIndex& index);
    void closeFileOther();
    void closeFileAll();
    void nextFile();
    void prevFile();
    void printFile();
    void showSettingKey();
    void showSettingSeptember();
    void clearHistoryFile();
    void openHistoryFile();

private:
    struct ClickedButton
    {
        bool searchAndReplace   = false;
        bool createWidget       = false;
        bool openUI             = false;
    };
    Ui::SeptemberEditor         *ui                 = nullptr;
    SettingKey                  *m_settingKey       = SettingKey::instance(this);
    SettingSeptember            *m_settingSeptember = SettingSeptember::instance(this);
    ListFileModel               *m_listModel        = new ListFileModel(this);
    SettingApp                  *m_settingApp       = SettingApp::instance();
    ClickedButton               m_clickedButton;
    QFileInfo                   m_fileInfo;
    QVector<QMetaObject::Connection>    m_connectionCoreEditor;
    QVector<QPair<QAction*, QString>>   m_historyFile_;
    bool                        m_visiblePathFile   = false;
    bool                        m_visibleLineWrap   = true;
    int                         m_countUnnamedFile  = 1;
    const QString               m_nameGroup         = { "September" };

    void connectionCoreEditor();
    void readSettingKey();
    void readHistoryFile();
    void writeFile(const QString& path, QFile& file);
};

#endif // SEPTEMBEREDITOR_H
