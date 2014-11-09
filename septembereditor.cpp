#include "septembereditor.h"
#include "ui_septembereditor.h"

SeptemberEditor::SeptemberEditor(QWidget* parent) : QMainWindow(parent),
    ui(new Ui::SeptemberEditor)
{
    ui->setupUi(this);
    ui->widgetSearchAndReplace->setVisible(false);
    ui->widgetWidget->setVisible(false);
    ui->widgetUI->setVisible(false);
    ui->mnFileExit->setShortcut(QKeySequence(QKeySequence::Quit));

    this->connect(ui->btnCloseListFile,     &QPushButton::clicked, this, &SeptemberEditor::closeOrOpenListFile);
    this->connect(ui->btnSearchAndReplace,  &QPushButton::clicked, this, &SeptemberEditor::closeOrOpenWidgetSearchAndReplace);
    this->connect(ui->btnWidget,            &QPushButton::clicked, this, &SeptemberEditor::closeOrOpenWidgetWidget);
    this->connect(ui->btnUi,                &QPushButton::clicked, this, &SeptemberEditor::closeOrOpenWidgetUI);
    this->connect(ui->mnFileExit,           &QAction::triggered,   qApp, &QApplication::quit);



    this->connect(ui->plainTextEdit, &CoreEditor::textChanged, this, [this]()
    { emit updateStyleSheet(ui->plainTextEdit->document()->toPlainText()); });

    this->connect(ui->barBtnCreateFile, &QPushButton::clicked, this, [this]()
    {
        static bool value = false;
        ui->plainTextEdit->setVisibleLineNimberArea(value);
        if(value)
            value = false;
        else
            value = true;
        qDebug()<<value;
    });
}

SeptemberEditor::~SeptemberEditor()
{
    delete ui;
}

QString SeptemberEditor::styleSheet() const
{ return ui->plainTextEdit->document()->toPlainText(); }

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
