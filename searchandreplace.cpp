#include "searchandreplace.h"
#include "ui_searchandreplace.h"

SearchAndReplace::SearchAndReplace(QWidget* parent) : QWidget(parent),
    ui(new Ui::SearchAndReplace)
{
    ui->setupUi(this);
}

SearchAndReplace::~SearchAndReplace()
{
    delete ui;
}
