#include "septembereditor.h"
#include "ui_septembereditor.h"

SeptemberEditor::SeptemberEditor(QWidget* parent) : QMainWindow(parent),
    ui(new Ui::SeptemberEditor)
{
    ui->setupUi(this);
    ui->widgetSearchAndReplace->setVisible(false);
    ui->widgetWidget->setVisible(false);
    ui->widgetUI->setVisible(false);
    ui->mnNew->setShortcut(QKeySequence(QKeySequence::New));
    ui->mnOpen->setShortcut(QKeySequence(QKeySequence::Open));
    ui->mnExit->setShortcut(QKeySequence(QKeySequence::Quit));

    this->connect(ui->btnCloseListFile,     &QPushButton::clicked, this, &SeptemberEditor::closeOrOpenListFile);
    this->connect(ui->btnSearchAndReplace,  &QPushButton::clicked, this, &SeptemberEditor::closeOrOpenWidgetSearchAndReplace);
    this->connect(ui->btnWidget,            &QPushButton::clicked, this, &SeptemberEditor::closeOrOpenWidgetWidget);
    this->connect(ui->btnUi,                &QPushButton::clicked, this, &SeptemberEditor::closeOrOpenWidgetUI);
    this->connect(ui->barBtnOpenFile,       &QPushButton::clicked, this, &SeptemberEditor::openFile);
    this->connect(ui->mnOpen,               &QAction::triggered,   this, &SeptemberEditor::openFile);
    this->connect(ui->mnExit,               &QAction::triggered,   qApp, &QApplication::quit);

    this->connect(ui->plainTextEdit, &CoreEditor::textChanged, this, [this]()
    { emit updateStyleSheet(ui->plainTextEdit->document()->toPlainText()); });
}

SeptemberEditor::~SeptemberEditor()
{ delete ui; }

QString SeptemberEditor::styleSheet() const
{ return ui->plainTextEdit->document()->toPlainText(); }

QTextDocument* SeptemberEditor::getDocument() const
{ return ui->plainTextEdit->document(); }

void SeptemberEditor::closeOrOpenListFile()
{
    static bool clicked = true;
    if(clicked)
    {
        clicked = false;
        ui->listFile->setVisible(false);
    }
    else
    {
        clicked = true;
        ui->listFile->setVisible(true);
    }
}

void SeptemberEditor::closeOrOpenWidgetSearchAndReplace()
{
    if(m_clickedButton.searchAndReplace)
    {
        m_clickedButton.searchAndReplace = false;
        ui->widgetSearchAndReplace->setVisible(false);
    }
    else
    {
        m_clickedButton.searchAndReplace = true;
        m_clickedButton.widget = false;
        m_clickedButton.widgetUI = false;
        ui->btnUi->setDown(false);
        ui->widgetWidget->setVisible(false);
        ui->widgetUI->setVisible(false);
        ui->widgetSearchAndReplace->setVisible(true);
    }
}

void SeptemberEditor::closeOrOpenWidgetWidget()
{
    if(m_clickedButton.widget)
    {
        m_clickedButton.widget = false;
        ui->widgetWidget->setVisible(false);
    }
    else
    {
        m_clickedButton.widget = true;
        m_clickedButton.searchAndReplace = false;
        m_clickedButton.widgetUI = false;
        ui->widgetSearchAndReplace->setVisible(false);
        ui->widgetUI->setVisible(false);
        ui->widgetWidget->setVisible(true);
    }
}

void SeptemberEditor::closeOrOpenWidgetUI()
{
    if(m_clickedButton.widgetUI)
    {
        m_clickedButton.widgetUI = false;
        ui->widgetUI->setVisible(false);
    }
    else
    {
        m_clickedButton.widgetUI = true;
        m_clickedButton.searchAndReplace = false;
        m_clickedButton.widget = false;
        ui->widgetSearchAndReplace->setVisible(false);
        ui->widgetWidget->setVisible(false);
        ui->widgetUI->setVisible(true);
    }
}

void SeptemberEditor::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, QString("Open file"), QString(), QString("*.qss"));
    if(path.length() == 0)
        return;

    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(file.readAll());
    }
    file.close();
}
