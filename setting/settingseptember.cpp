#include "settingseptember.h"
#include "ui_settingseptember.h"

SettingSeptember::SettingSeptember(QWidget* parent) : QDialog(parent),
    ui(new Ui::SettingSeptember)
{
    ui->setupUi(this);
    this->setWindowTitle("Настройка -- September");
}

SettingSeptember::~SettingSeptember()
{
    delete ui;
}
