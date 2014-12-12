#include "septembereditor.h"
#include "ui_septembereditor.h"

SeptemberEditor::SeptemberEditor(QWidget* parent) : QMainWindow(parent),
    ui(new Ui::SeptemberEditor)
{
    ui->setupUi(this);
    ui->widgetSearchAndReplace->setVisible(false);
    ui->widgetCreateWidget->setVisible(false);
    ui->widgetOpenUI->setVisible(false);
    ui->fileListView->setModel(m_listModel);
    m_listModel->addItem("Безымянный 1", ui->plainTextEdit, ui->widgetCreateWidget->getScene(), ui->widgetOpenUI->getBufferUi());
    m_fileInfo.setFile("Безымянный 1");
    ui->fileListView->setCurrentIndex(m_listModel->getModelIndex(0));
    ui->splitterEdit->setVisibleHeightHandle(false);

    ui->mnNewFile->setShortcut(QKeySequence::New);
    ui->mnOpen->setShortcut(QKeySequence::Open);
    ui->mnSave->setShortcut(QKeySequence::Save);
    ui->mnSaveAs->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_L);
    ui->mnSaveAll->setShortcut(Qt::CTRL + Qt::Key_L);
    ui->mnPrint->setShortcut(QKeySequence::Print);
    ui->mnCloseFile->setShortcut(QKeySequence::Close);
    ui->mnCloseFileOther->setShortcut(Qt::CTRL + Qt::Key_R);
    ui->mnCloseFileAll->setShortcut(Qt::CTRL + Qt::Key_A);
    ui->mnQuit->setShortcut(QKeySequence::Quit);

    ui->mnUndo->setShortcut(QKeySequence::Undo);
    ui->mnRedo->setShortcut(QKeySequence::Redo);
    ui->mnCut->setShortcut(QKeySequence::Cut);
    ui->mnCopy->setShortcut(QKeySequence::Copy);
    ui->mnPaste->setShortcut(QKeySequence::Paste);
    ui->mnSelectAll->setShortcut(QKeySequence::SelectAll);
    ui->mnSearchReplace->setShortcut(QKeySequence::Find);

    ui->mnListFile->setCheckable(true);
    ui->mnCreateWidget->setCheckable(true);
    ui->mnOpenUi->setCheckable(true);
    ui->mnNumberLine->setCheckable(true);
    ui->mnNumberLine->setChecked(true);
    ui->mnLineWrap->setCheckable(true);
    ui->mnLineWrap->setChecked(true);
    ui->mnNumberLine->setShortcut(Qt::Key_F11);
    ui->mnLineWrap->setShortcut(Qt::Key_F10);
    ui->mnListFile->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_Q);
    ui->mnCreateWidget->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_W);
    ui->mnOpenUi->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_E);
    ui->mnNextFile->setShortcut(Qt::ALT + Qt::Key_Right);
    ui->mnPrevFile->setShortcut(Qt::ALT + Qt::Key_Left);
    ui->mnZoomIn->setShortcut(QKeySequence::ZoomIn);
    ui->mnZoomOut->setShortcut(QKeySequence::ZoomOut);

    ui->mnStatusBar->setCheckable(true);
    ui->mnStatusBar->setChecked(true);
    ui->mnFullScreen->setCheckable(true);
    ui->mnFullScreen->setChecked(false);
    ui->mnPathFile->setCheckable(true);
    ui->mnPathFile->setChecked(false);
    ui->mnStatusBar->setShortcut(Qt::ALT + Qt::Key_F5);
    ui->mnPathFile->setShortcut(Qt::ALT + Qt::Key_F6);
    ui->mnSettingKey->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_K);
    ui->mnSettingSeptember->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_S);
    ui->mnFullScreen->setShortcut(QKeySequence::FullScreen);

    this->connect(ui->btnCloseListFile,     &QPushButton::clicked, this, &SeptemberEditor::closeOrShowListFile);
    this->connect(ui->btnSearchAndReplace,  &QPushButton::clicked, this, &SeptemberEditor::closeOrShowWidgetSearchAndReplace);
    this->connect(ui->btnCreateWidget,      &QPushButton::clicked, this, &SeptemberEditor::closeOrShowCreateWidget);
    this->connect(ui->btnOpenUi,            &QPushButton::clicked, this, &SeptemberEditor::closeOrShowOpenUI);
    this->connect(ui->barBtnCreateFile,     &QPushButton::clicked, this, std::bind(&SeptemberEditor::newFile, this, "Безымянный"));
    this->connect(ui->barBtnOpenFile,       &QPushButton::clicked, this, &SeptemberEditor::openFile);
    this->connect(ui->barBtnSaveFile,       &QPushButton::clicked, this, &SeptemberEditor::saveFile);
    this->connect(ui->barBtnSaveAsFile,     &QPushButton::clicked, this, &SeptemberEditor::saveFileAs);
    this->connect(ui->barBtnNextFile,       &QPushButton::clicked, this, &SeptemberEditor::nextFile);
    this->connect(ui->barBtnPrevFile,       &QPushButton::clicked, this, &SeptemberEditor::prevFile);
    this->connect(ui->mnNewFile,        &QAction::triggered,    this, std::bind(&SeptemberEditor::newFile, this, "Безымянный"));
    this->connect(ui->mnOpen,           &QAction::triggered,    this, &SeptemberEditor::openFile);
    this->connect(ui->mnSave,           &QAction::triggered,    this, &SeptemberEditor::saveFile);
    this->connect(ui->mnSaveAs,         &QAction::triggered,    this, &SeptemberEditor::saveFileAs);
    this->connect(ui->mnPrint,          &QAction::triggered,    this, &SeptemberEditor::printFile);
    this->connect(ui->mnCloseFile,      &QAction::triggered,    this, [this]()
    {
        int row = ui->fileListView->currentIndex().row();
        if(row != -1)
            closeFile(row);
    });
    this->connect(ui->mnNextFile,       &QAction::triggered,    this, &SeptemberEditor::nextFile);
    this->connect(ui->mnPrevFile,       &QAction::triggered,    this, &SeptemberEditor::prevFile);
    this->connect(ui->mnCloseFileOther, &QAction::triggered,    this, &SeptemberEditor::closeFileOther);
    this->connect(ui->mnCloseFileAll,   &QAction::triggered,    this, &SeptemberEditor::closeFileAll);
    this->connect(ui->mnQuit,           &QAction::triggered,    qApp, &QApplication::quit);
    this->connect(ui->mnSearchReplace,  &QAction::triggered,    this, &SeptemberEditor::closeOrShowWidgetSearchAndReplace);
    this->connect(ui->mnListFile,     &QAction::triggered, std::bind(&SeptemberEditor::closeOrShowListFile, this));
    this->connect(ui->mnCreateWidget, &QAction::triggered, std::bind(&SeptemberEditor::closeOrShowCreateWidget, this));
    this->connect(ui->mnOpenUi,       &QAction::triggered, std::bind(&SeptemberEditor::closeOrShowOpenUI, this));
    this->connect(ui->mnLineWrap,   &QAction::triggered, this, &SeptemberEditor::lineWrap);
    this->connect(ui->mnFullScreen, &QAction::triggered, this, &SeptemberEditor::fullScreen);
    this->connect(ui->mnStatusBar,  &QAction::triggered, std::bind(&QLabel::setVisible, ui->lblStatusBar, std::placeholders::_1));
    this->connect(ui->mnPathFile,   &QAction::triggered, this, &SeptemberEditor::pathFile);
    this->connect(ui->mnSettingKey, &QAction::triggered, m_settingKey, &SettingKey::show);
    this->connect(ui->mnSettingSeptember, &QAction::triggered, m_settingSeptember, &SettingSeptember::show);
    this->connect(ui->fileListView, &ListFileView::clickedCloseFile, this, &SeptemberEditor::closeFile);
    this->connect(ui->fileListView, &ListFileView::clicked, this, &SeptemberEditor::selectFile);
    this->setWindowTitle("Безымянный1 -- September");

    connectionCoreEditor(ui->plainTextEdit);
}

SeptemberEditor::~SeptemberEditor()
{ delete ui; }

void SeptemberEditor::closeOrShowListFile()
{
    QPushButton* button = qobject_cast<QPushButton*>(this->sender());
    static bool clicked = true;
    if(clicked)
    {
        if(button != nullptr)
            ui->mnListFile->setChecked(false);

        clicked = false;
        ui->fileListView->setVisible(false);
        ui->splitterList->setVisibleWidthHandle(false);

    }
    else
    {
        if(button != nullptr)
            ui->mnListFile->setChecked(true);

        clicked = true;
        ui->fileListView->setVisible(true);
        ui->splitterList->setVisibleWidthHandle(true);
        ui->splitterList->setWidth(120);
    }
}

void SeptemberEditor::closeOrShowWidgetSearchAndReplace()
{
    if(m_clickedButton.searchAndReplace)
    {
        m_clickedButton.searchAndReplace = false;
        ui->widgetSearchAndReplace->setVisible(false);
        ui->widgetSearchAndReplace->clearResultSearch();
        ui->plainTextEdit->clearSelectTextSearch();
        ui->plainTextEdit->setFocus();
    }
    else
    {
        m_clickedButton.searchAndReplace = true;
        m_clickedButton.createWidget = false;
        m_clickedButton.openUI = false;
        ui->splitterEdit->setVisibleHeightHandle(false);
        ui->btnOpenUi->setDown(false);
        ui->widgetCreateWidget->setVisible(false);
        ui->widgetOpenUI->setVisible(false);
        ui->widgetSearchAndReplace->setVisible(true);
        ui->widgetSearchAndReplace->setFocusEditSearch();
        ui->mnCreateWidget->setChecked(false);
        ui->mnOpenUi->setChecked(false);
    }
}

void SeptemberEditor::closeOrShowCreateWidget()
{
    QPushButton* button = qobject_cast<QPushButton*>(this->sender());
    if(m_clickedButton.createWidget)
    {
        if(button != nullptr)
            ui->mnCreateWidget->setChecked(false);

        m_clickedButton.createWidget = false;
        ui->widgetCreateWidget->setVisible(false);
        ui->plainTextEdit->clearSelectTextSearch();
        ui->plainTextEdit->setFocus();
        if(m_clickedButton.openUI == false && m_clickedButton.createWidget == false)
            ui->splitterEdit->setVisibleHeightHandle(false);
    }
    else
    {
        if(button == nullptr)
            ui->mnOpenUi->setChecked(false);
        else
        {
            ui->mnCreateWidget->setChecked(true);
            ui->mnOpenUi->setChecked(false);
        }
        m_clickedButton.createWidget = true;
        m_clickedButton.searchAndReplace = false;
        m_clickedButton.openUI = false;
        ui->widgetSearchAndReplace->setVisible(false);
        ui->widgetSearchAndReplace->clearResultSearch();
        ui->widgetOpenUI->setVisible(false);
        ui->widgetCreateWidget->setVisible(true);
        ui->widgetCreateWidget->setFocusLineEdit();
        ui->splitterEdit->setVisibleHeightHandle(true);
        ui->splitterEdit->setHeight(ui->widgetCreateWidget->minimumSizeHint().height());
    }
}

void SeptemberEditor::closeOrShowOpenUI()
{
    QPushButton* button = qobject_cast<QPushButton*>(this->sender());
    if(m_clickedButton.openUI)
    {
        if(button != nullptr)
            ui->mnOpenUi->setChecked(false);

        m_clickedButton.openUI = false;
        ui->widgetOpenUI->setVisible(false);
        ui->plainTextEdit->clearSelectTextSearch();
        ui->plainTextEdit->setFocus();
        if(m_clickedButton.openUI == false && m_clickedButton.createWidget == false)
            ui->splitterEdit->setVisibleHeightHandle(false);
    }
    else
    {
        if(button == nullptr)
            ui->mnCreateWidget->setChecked(false);
        else
        {
            ui->mnOpenUi->setChecked(true);
            ui->mnCreateWidget->setChecked(false);
        }
        m_clickedButton.openUI = true;
        m_clickedButton.searchAndReplace = false;
        m_clickedButton.createWidget = false;
        ui->widgetSearchAndReplace->setVisible(false);
        ui->widgetSearchAndReplace->clearResultSearch();
        ui->widgetCreateWidget->setVisible(false);
        ui->widgetOpenUI->setVisible(true);
        ui->splitterEdit->setVisibleHeightHandle(true);
        ui->splitterEdit->setHeight(ui->widgetOpenUI->minimumSizeHint().height());
    }
}

void SeptemberEditor::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Open file", QString(), "*.qss");
    if(path.isEmpty())
        return;

    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        m_fileInfo.setFile(path);
        pathFile(m_visiblePathFile);
        if(m_listModel->rowCount() == 1)
        {
            if(!ui->plainTextEdit->toPlainText().isEmpty())
            {
                newFile(m_fileInfo.fileName());
                selectFile(m_listModel->getModelIndex(m_listModel->rowCount() - 1));
                ui->plainTextEdit->appendText(file.readAll());
            }
            else
            {
                ui->plainTextEdit->appendText(file.readAll());
                m_listModel->removeItem(0);
                m_listModel->addItem(path, ui->plainTextEdit, ui->widgetCreateWidget->getScene(), ui->widgetOpenUI->getBufferUi());
                ui->fileListView->setCurrentIndex(m_listModel->getModelIndex(m_listModel->rowCount() - 1));
            }
        }
        else
        {
            newFile(path);
            selectFile(m_listModel->getModelIndex(m_listModel->rowCount() - 1));
            ui->plainTextEdit->appendText(file.readAll());
        }
        QTextCursor cursorFirst(ui->plainTextEdit->document());
        cursorFirst.setPosition(0);
        ui->plainTextEdit->setTextCursor(cursorFirst);
        ui->plainTextEdit->checkingCodeQss();
    }
    file.close();
}

void SeptemberEditor::lineWrap(bool trigger)
{
    if(trigger)
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    else
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
}

void SeptemberEditor::fullScreen(bool trigger)
{
    if(trigger)
        this->showFullScreen();
    else
        this->showMaximized();
}

void SeptemberEditor::pathFile(bool trigger)
{
    m_visiblePathFile = trigger;
    if(!m_fileInfo.isFile())
    {
        this->setWindowTitle("Безымянный -- September");
        return;
    }

    if(trigger)
        this->setWindowTitle(m_fileInfo.filePath() + " -- September");
    else
        this->setWindowTitle(m_fileInfo.fileName() + " -- September");
}

void SeptemberEditor::setStatusBar()
{
    QTextCursor currentCursor = ui->plainTextEdit->textCursor();
    ui->lblStatusBar->setText(QString("Строка: %1 из %2 Столбец: %3")
                                .arg(QString::number(currentCursor.blockNumber() + 1))
                                .arg(QString::number(ui->plainTextEdit->blockCount()))
                                .arg(QString::number(currentCursor.positionInBlock() + 1)));
}

void SeptemberEditor::saveFile()
{
    QString path;
    if(m_fileInfo.exists())
        path = m_fileInfo.filePath();
    else
    {
        path = QFileDialog::getSaveFileName(this, "Save file", QString(), "*.qss");
        if(path.isEmpty())
            return;
        if(!path.contains(QRegExp(R"(.+\.qss)")))
            path += ".qss";
        m_fileInfo.setFile(path);
    }
    QFile file(path);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(ui->plainTextEdit->toPlainText().toUtf8());
        pathFile(m_visiblePathFile);
    }
    file.close();
}

void SeptemberEditor::saveFileAs()
{
    QString path = QFileDialog::getSaveFileName(this, "Save file", QString(), "*.qss");
    if(path.isEmpty())
        return;
    if(!path.contains(QRegExp(R"(.+\.qss)")))
        path += ".qss";
    m_fileInfo.setFile(path);

    QFile file(path);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(ui->plainTextEdit->toPlainText().toUtf8());
        pathFile(m_visiblePathFile);
    }
    file.close();
}

void SeptemberEditor::newFile(const QString& name)
{
    CoreEditor* editor = new CoreEditor(this);
    editor->setVisible(false);
    if(name == "Безымянный")
        m_listModel->addItem("Безымянный " + QString::number(++m_countUnnamedFile), editor, ui->widgetCreateWidget->createScene(), ui->widgetOpenUI->createBufferUi());
    else
        m_listModel->addItem(name, editor, ui->widgetCreateWidget->createScene(), ui->widgetOpenUI->createBufferUi());
    selectFile(m_listModel->getModelIndex(m_listModel->rowCount() - 1));
}

void SeptemberEditor::closeFile(int row)
{
    QGraphicsScene* sceneStyle  = nullptr;
    QBuffer* bufferUI           = nullptr;
    CoreEditor* coreEditor      = nullptr;
    if(m_listModel->rowCount() == 1)
    {
        std::tie(coreEditor, sceneStyle, bufferUI) = m_listModel->getItem(row);
        ui->plainTextEdit = new CoreEditor;
        connectionCoreEditor(ui->plainTextEdit);
        ui->widgetCreateWidget->setScene(ui->widgetCreateWidget->createScene());
        ui->widgetOpenUI->setBufferUi(ui->widgetOpenUI->createBufferUi());
        ui->horizontalLayout_8->removeWidget(coreEditor);
        ui->horizontalLayout_8->addWidget(ui->plainTextEdit);
        m_listModel->addItem("Безымянный 1", ui->plainTextEdit, ui->widgetCreateWidget->getScene(), ui->widgetOpenUI->getBufferUi());
        m_countUnnamedFile = 1;
    }
    else
    {
        std::tie(coreEditor, sceneStyle, bufferUI) = m_listModel->getItem(row);
        int index = ui->horizontalLayout_8->indexOf(coreEditor);
        if(row == 0 && index != -1)
            selectFile(m_listModel->getModelIndex(row + 1));
        else if(index != -1)
            selectFile(m_listModel->getModelIndex(row - 1));
    }
    m_listModel->removeItem(row);
    coreEditor->deleteLater();
    sceneStyle->deleteLater();
    bufferUI->deleteLater();
}

void SeptemberEditor::selectFile(const QModelIndex& index)
{
    QGraphicsScene* sceneStyle  = nullptr;
    QBuffer* bufferUI           = nullptr;
    CoreEditor* select          = nullptr;
    std::tie(select, sceneStyle, bufferUI) = m_listModel->getItem(index.row());
    if(select == ui->plainTextEdit)
        return;
    ui->horizontalLayout_8->removeWidget(ui->plainTextEdit);
    for(auto& dis : m_connectionCoreEditor) this->disconnect(dis);
    m_connectionCoreEditor.clear();

    ui->plainTextEdit->setParent(this);
    ui->plainTextEdit = select;
    ui->plainTextEdit->setVisible(true);
    ui->horizontalLayout_8->addWidget(ui->plainTextEdit);
    ui->plainTextEdit->setFocus();
    ui->widgetCreateWidget->setScene(sceneStyle);
    ui->widgetOpenUI->setBufferUi(bufferUI);
    ui->fileListView->setCurrentIndex(index);
    connectionCoreEditor(ui->plainTextEdit);
}

void SeptemberEditor::closeFileOther()
{
    int currentRow = ui->fileListView->currentIndex().row();
    if(currentRow != -1)
    {
        CoreEditor* editor = std::get<0>(m_listModel->getItem(currentRow));
        forever
        {
            int rowCount = m_listModel->rowCount() - 1;
            if(rowCount == 0)
                break;
            else if(editor == std::get<0>(m_listModel->getItem(rowCount)))
                closeFile(rowCount - 1);
            else
                closeFile(rowCount);
        }
    }
}

void SeptemberEditor::closeFileAll()
{
    forever
    {
        if(m_listModel->rowCount() == 1)
            break;
        else
            closeFile(0);
    }
    closeFile(0);
}

void SeptemberEditor::nextFile()
{
    if(m_listModel->rowCount() == 1)
        return;

    int currentRow = ui->fileListView->currentIndex().row();
    if(currentRow != -1)
    {
        currentRow += 1;
        if(currentRow < m_listModel->rowCount())
            selectFile(m_listModel->getModelIndex(currentRow));
        else
            selectFile(m_listModel->getModelIndex(0));
    }
}

void SeptemberEditor::prevFile()
{
    if(m_listModel->rowCount() == 1)
        return;

    int currentRow = ui->fileListView->currentIndex().row();
    if(currentRow != -1)
    {
        currentRow -= 1;
        if(currentRow >= 0)
            selectFile(m_listModel->getModelIndex(currentRow));
        else
            selectFile(m_listModel->getModelIndex(m_listModel->rowCount() - 1));
    }
}

void SeptemberEditor::printFile()
{
    QPrinter print(QPrinter::HighResolution);
    QString filename = m_fileInfo.filePath().isEmpty() ? m_fileInfo.fileName() : m_fileInfo.filePath();
    if(filename.contains(QRegExp(R"(.+\.qss)")))
        filename.remove(filename.length() - 4, 4);
    filename += ".pdf";
    print.setOutputFileName(filename);
    print.setOutputFormat(QPrinter::PdfFormat);
    QPrintDialog dialog(&print, this);
    if(dialog.exec() == QDialog::Accepted)
        ui->plainTextEdit->document()->print(&print);
}

void SeptemberEditor::connectionCoreEditor(CoreEditor* coreEditor)
{
    m_connectionCoreEditor.push_back(this->connect(ui->mnUndo,           &QAction::triggered,    coreEditor, &CoreEditor::undo));
    m_connectionCoreEditor.push_back(this->connect(ui->mnRedo,           &QAction::triggered,    coreEditor, &CoreEditor::redo));
    m_connectionCoreEditor.push_back(this->connect(ui->mnCut,            &QAction::triggered,    coreEditor, &CoreEditor::cut));
    m_connectionCoreEditor.push_back(this->connect(ui->mnCopy,           &QAction::triggered,    coreEditor, &CoreEditor::copy));
    m_connectionCoreEditor.push_back(this->connect(ui->mnPaste,          &QAction::triggered,    coreEditor, &CoreEditor::paste));
    m_connectionCoreEditor.push_back(this->connect(ui->mnSelectAll,      &QAction::triggered,    coreEditor, &CoreEditor::selectAll));
    m_connectionCoreEditor.push_back(this->connect(ui->mnZoomIn,         &QAction::triggered, coreEditor, &CoreEditor::zoomDocIn));
    m_connectionCoreEditor.push_back(this->connect(ui->mnZoomOut,        &QAction::triggered, coreEditor, &CoreEditor::zoomDocOut));
    m_connectionCoreEditor.push_back(this->connect(ui->mnNumberLine,     &QAction::triggered, coreEditor, &CoreEditor::setVisibleLineNimberArea));
    m_connectionCoreEditor.push_back(this->connect(coreEditor,   &CoreEditor::cursorPositionChanged, this, &SeptemberEditor::setStatusBar));
    m_connectionCoreEditor.push_back(this->connect(coreEditor,   &CoreEditor::updateStyleSheet, ui->widgetCreateWidget, &WidgetStyle::setStyleSheetWidget));
    m_connectionCoreEditor.push_back(this->connect(coreEditor,   &CoreEditor::updateStyleSheet, ui->widgetOpenUI,       &WidgetUiStyle::setStyleSheetWidget));
}
