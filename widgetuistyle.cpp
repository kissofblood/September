#include "widgetuistyle.h"
#include "ui_widgetuistyle.h"

WidgetUiStyle::WidgetUiStyle(QWidget* parent) : QWidget(parent),
    ui(new Ui::WidgetUiStyle)
{
    ui->setupUi(this);
}

WidgetUiStyle::~WidgetUiStyle()
{
    delete ui;
}
