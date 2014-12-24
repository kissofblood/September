#include "settingfontandcolor.h"
#include "ui_settingfontandcolor.h"

SettingFontAndColor::SettingFontAndColor(QWidget* parent) : QWidget(parent),
    ui(new Ui::SettingFontAndColor)
{
    ui->setupUi(this);
    ui->btnColorSelectText->setPalette(QPalette(Qt::blue));

    this->connect(ui->btnColorBackground,   &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnColorSelectText,   &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnColorCurrentLine,  &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnColorSearchText,   &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
}

SettingFontAndColor::~SettingFontAndColor()
{ delete ui; }

void SettingFontAndColor::setBackgroundColor(const QColor& background)
{ ui->btnColorBackground->setPalette(QPalette(background)); }

QColor SettingFontAndColor::backgroundColor()
{ return ui->btnColorBackground->palette().color(QPalette::Button); }

void SettingFontAndColor::setCurrentLineColor(const QColor& currentLine)
{ ui->btnColorCurrentLine->setPalette(QPalette(currentLine)); }

QColor SettingFontAndColor::currentLineColor()
{ return ui->btnColorCurrentLine->palette().color(QPalette::Button); }

void SettingFontAndColor::setSearchTextColor(const QColor& searchText)
{ ui->btnColorSearchText->setPalette(QPalette(searchText)); }

QColor SettingFontAndColor::searchTextColor()
{ return ui->btnColorSearchText->palette().color(QPalette::Button); }

void SettingFontAndColor::setFontText(const QFont& font)
{ ui->fontText->setCurrentFont(font); }

QFont SettingFontAndColor::fontText()
{ return ui->fontText->currentFont(); }

void SettingFontAndColor::amendColorEdit()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if(!color.isValid())
        return;

    QPushButton* btn = qobject_cast<QPushButton*>(this->sender());
    btn->setPalette(QPalette(color));
}
