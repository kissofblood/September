#include "widgetstyle.h"
#include "ui_widgetstyle.h"

WidgetStyle::WidgetStyle(QWidget* parent) : QWidget(parent),
    ui(new Ui::WidgetStyle)
{
    ui->setupUi(this);
}

WidgetStyle::~WidgetStyle()
{
    delete ui;
}
