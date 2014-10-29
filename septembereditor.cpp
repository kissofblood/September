#include "septembereditor.h"
#include "ui_septembereditor.h"

SeptemberEditor::SeptemberEditor(QWidget* parent) : QMainWindow(parent),
    ui(new Ui::SeptemberEditor)
{
    ui->setupUi(this);
    ui->btnCloseListFile->setDown(true);

    this->connect(ui->btnCloseListFile, &QPushButton::clicked, this, &SeptemberEditor::closeOrOpenListFile);
}

SeptemberEditor::~SeptemberEditor()
{
    delete ui;
}

void SeptemberEditor::closeOrOpenListFile()
{
    static bool clicked = false;
    if(clicked)
    {
        clicked = false;
        ui->btnCloseListFile->setDown(true);
        ui->listFile->setVisible(true);
    }
    else
    {
        clicked = true;
        ui->btnCloseListFile->setDown(false);
        ui->listFile->setVisible(false);
    }
}
