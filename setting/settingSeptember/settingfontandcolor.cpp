#include "settingfontandcolor.h"
#include "ui_settingfontandcolor.h"

SettingFontAndColor::SettingFontAndColor(QWidget* parent) : QWidget(parent),
    ui(new Ui::SettingFontAndColor)
{
    ui->setupUi(this);
    ui->btnColorSelectText->setPalette(QPalette(Qt::blue));
    QVector<QPair<QString, int>> vec = {{ "Light", 25 }, { "Normal", 50 }, { "DemiBold", 63 }, { "Bold", 75 }, { "Black", 87 }};
    for(auto& pair : vec)
    {
        ui->cmbOtherWeight->addItem(pair.first, pair.second);
        ui->cmbPropertiesWeight->addItem(pair.first, pair.second);
        ui->cmbPseudoWeight->addItem(pair.first, pair.second);
        ui->cmbSubWeight->addItem(pair.first, pair.second);
        ui->cmbWidgetWeight->addItem(pair.first, pair.second);
        ui->cmbNumberWeight->addItem(pair.first, pair.second);
        ui->cmbCommentWeight->addItem(pair.first, pair.second);
    }
   // addScheme();
    ui->cmbScheme->addItem("Default");

    this->connect(ui->btnColorBackground,   &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnColorSelectText,   &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnColorCurrentLine,  &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnColorSearchText,   &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnOtherColor,        &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnPropertiesColor,   &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnPseudoColor,       &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnSubColor,          &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnWidgetColor,       &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnCommentColor,      &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
    this->connect(ui->btnNumberColor,       &QPushButton::clicked, this, &SettingFontAndColor::amendColorEdit);
}

SettingFontAndColor::~SettingFontAndColor()
{ delete ui; }

void SettingFontAndColor::writeBackgroundColor(const QColor& color)
{
    m_settingApp->writeBackgroundColorSettingSeptember(ui->cmbScheme->currentText(), color);
    m_settingApp->writeDefaultBackgroundColorSettingSeptember(color);
    ui->btnColorBackground->setPalette(QPalette(color));
}

void SettingFontAndColor::writeCurrentLineColor(const QColor& color)
{
    m_settingApp->writeCurrentLineColorSettingSeptember(ui->cmbScheme->currentText(), color);
    m_settingApp->writeDefaultCurrentLineColorSettingSeptember(color);
    ui->btnColorCurrentLine->setPalette(QPalette(color));
}

void SettingFontAndColor::writeSearchTextColor(const QColor& color)
{
    m_settingApp->writeSearchTextColorSettingSeptember(ui->cmbScheme->currentText(), color);
    m_settingApp->writeDefaultSearchTextColorSettingSeptember(color);
    ui->btnColorSearchText->setPalette(QPalette(color));
}

void SettingFontAndColor::writeFontText(const QFont& font)
{
    m_settingApp->writeFontText(ui->cmbScheme->currentText(), font);
    m_settingApp->writeDefaultFontText(font);
    ui->fontText->setCurrentFont(font);
}

void SettingFontAndColor::writeOtherQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writeOtherQss(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultOtherQss(color, weight);
    ui->btnOtherColor->setPalette(QPalette(color));
    ui->cmbOtherWeight->setCurrentIndex(ui->cmbOtherWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writePropertiesQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writePropertiesQss(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultPropertiesQss(color, weight);
    ui->btnPropertiesColor->setPalette(QPalette(color));
    ui->cmbPropertiesWeight->setCurrentIndex(ui->cmbPropertiesWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writePseudoQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writePseudoQss(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultPseudoQss(color, weight);
    ui->btnPseudoColor->setPalette(QPalette(color));
    ui->cmbPseudoWeight->setCurrentIndex(ui->cmbPseudoWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writeSubQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writeSubQss(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultSubQss(color, weight);
    ui->btnSubColor->setPalette(QPalette(color));
    ui->cmbSubWeight->setCurrentIndex(ui->cmbSubWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writeWidgetQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writeWidgetQss(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultWidgetQss(color, weight);
    ui->btnWidgetColor->setPalette(QPalette(color));
    ui->cmbWidgetWeight->setCurrentIndex(ui->cmbWidgetWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writeCommentQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writeCommentQss(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultCommentQss(color, weight);
    ui->btnCommentColor->setPalette(QPalette(color));
    ui->cmbCommentWeight->setCurrentIndex(ui->cmbCommentWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writeNumberQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writeNumberQss(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultNumberQss(color, weight);
    ui->btnNumberColor->setPalette(QPalette(color));
    ui->cmbNumberWeight->setCurrentIndex(ui->cmbNumberWeight->findData(static_cast<int>(weight)));
}

QColor SettingFontAndColor::backgroundColor()
{ return ui->btnColorBackground->palette().color(QPalette::Button); }

QColor SettingFontAndColor::currentLineColor()
{ return ui->btnColorCurrentLine->palette().color(QPalette::Button); }

QColor SettingFontAndColor::searchTextColor()
{ return ui->btnColorSearchText->palette().color(QPalette::Button); }

QFont SettingFontAndColor::fontText()
{ return ui->fontText->currentFont(); }

void SettingFontAndColor::readSettingColor()
{
   // addScheme();

    if(!m_settingApp->containsColorSettingSeptember())
        return;

    QString scheme = ui->cmbScheme->currentText();
    ui->btnColorBackground->setPalette(QPalette(m_settingApp->readBackgroundColorSettingSeptember(scheme)));
    ui->btnColorCurrentLine->setPalette(QPalette(m_settingApp->readCurrentLineColorSettingSeptember(scheme)));
    ui->btnColorSearchText->setPalette(QPalette(m_settingApp->readSearchTextColorSettingSeptember(scheme)));
    ui->fontText->setCurrentFont(m_settingApp->readFontText(scheme));
}

void SettingFontAndColor::writeSettingColor()
{
    QString scheme = ui->cmbScheme->currentText();
    m_settingApp->writeBackgroundColorSettingSeptember(scheme, backgroundColor());
    m_settingApp->writeCurrentLineColorSettingSeptember(scheme, currentLineColor());
    m_settingApp->writeSearchTextColorSettingSeptember(scheme, searchTextColor());
    m_settingApp->writeFontText(scheme, fontText());
}

void SettingFontAndColor::readSettingQss()
{
    if(!m_settingApp->containsQssSettingSeptember())
        return;

    QPair<QColor, QFont::Weight> pair;
    QString scheme = ui->cmbScheme->currentText();
    pair = m_settingApp->readOtherQss(scheme);
    ui->btnOtherColor->setPalette(QPalette(pair.first));
    ui->cmbOtherWeight->setCurrentIndex(ui->cmbOtherWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readPropertiesQss(scheme);
    ui->btnPropertiesColor->setPalette(QPalette(pair.first));
    ui->cmbPropertiesWeight->setCurrentIndex(ui->cmbPropertiesWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readPseudoQss(scheme);
    ui->btnPseudoColor->setPalette(QPalette(pair.first));
    ui->cmbPseudoWeight->setCurrentIndex(ui->cmbPseudoWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readSubQss(scheme);
    ui->btnSubColor->setPalette(QPalette(pair.first));
    ui->cmbSubWeight->setCurrentIndex(ui->cmbSubWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readWidgetQss(scheme);
    ui->btnWidgetColor->setPalette(QPalette(pair.first));
    ui->cmbWidgetWeight->setCurrentIndex(ui->cmbWidgetWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readCommentQss(scheme);
    ui->btnCommentColor->setPalette(QPalette(pair.first));
    ui->cmbCommentWeight->setCurrentIndex(ui->cmbCommentWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readNumberQss(scheme);
    ui->btnNumberColor->setPalette(QPalette(pair.first));
    ui->cmbNumberWeight->setCurrentIndex(ui->cmbNumberWeight->findData(static_cast<int>(pair.second)));
}

void SettingFontAndColor::writeSettingQss()
{
    QPair<QColor, QFont::Weight> pair;
    QString scheme = ui->cmbScheme->currentText();
    pair = otherQss();
    m_settingApp->writeOtherQss(scheme, pair.first, pair.second);
    pair = propertiesQss();
    m_settingApp->writePropertiesQss(scheme, pair.first, pair.second);
    pair = pseudoQss();
    m_settingApp->writePseudoQss(scheme, pair.first, pair.second);
    pair = subQss();
    m_settingApp->writeSubQss(scheme, pair.first, pair.second);
    pair = widgetQss();
    m_settingApp->writeWidgetQss(scheme, pair.first, pair.second);
    pair = commentQss();
    m_settingApp->writeCommentQss(scheme, pair.first, pair.second);
    pair = numberQss();
    m_settingApp->writeNumberQss(scheme, pair.first, pair.second);
}

QPair<QColor, QFont::Weight> SettingFontAndColor::otherQss()
{
    return { ui->btnOtherColor->palette().color(QPalette::Button),
             static_cast<QFont::Weight>(ui->cmbOtherWeight->currentData().toInt()) };
}

QPair<QColor, QFont::Weight> SettingFontAndColor::propertiesQss()
{
    return { ui->btnPropertiesColor->palette().color(QPalette::Button),
             static_cast<QFont::Weight>(ui->cmbPropertiesWeight->currentData().toInt()) };
}

QPair<QColor, QFont::Weight> SettingFontAndColor::pseudoQss()
{
    return { ui->btnPseudoColor->palette().color(QPalette::Button),
             static_cast<QFont::Weight>(ui->cmbPseudoWeight->currentData().toInt()) };
}

QPair<QColor, QFont::Weight> SettingFontAndColor::subQss()
{
    return { ui->btnSubColor->palette().color(QPalette::Button),
             static_cast<QFont::Weight>(ui->cmbSubWeight->currentData().toInt()) };
}

QPair<QColor, QFont::Weight> SettingFontAndColor::widgetQss()
{
    return { ui->btnWidgetColor->palette().color(QPalette::Button),
                static_cast<QFont::Weight>(ui->cmbWidgetWeight->currentData().toInt()) };
}

QPair<QColor, QFont::Weight> SettingFontAndColor::commentQss()
{
    return { ui->btnCommentColor->palette().color(QPalette::Button),
                static_cast<QFont::Weight>(ui->cmbCommentWeight->currentData().toInt()) };
}

QPair<QColor, QFont::Weight> SettingFontAndColor::numberQss()
{
    return { ui->btnNumberColor->palette().color(QPalette::Button),
             static_cast<QFont::Weight>(ui->cmbNumberWeight->currentData().toInt()) };
}

void SettingFontAndColor::amendColorEdit()
{
    QPushButton* btn = qobject_cast<QPushButton*>(this->sender());
    QColor color = QColorDialog::getColor(btn->palette().color(QPalette::Button), this);
    if(!color.isValid())
        return;

    btn->setPalette(QPalette(color));
}

void SettingFontAndColor::addScheme()
{
    ui->cmbScheme->clear();
    QStringList listScheme = m_settingApp->readSettingSeptember();
    if(listScheme.isEmpty())
    {
        ui->cmbScheme->addItem("Default");
        m_settingApp->writeSettingSeptember("Default", 0);
    }
    else for(auto& scheme : listScheme)
    {
        if(ui->cmbScheme->findText(scheme) == -1)
            ui->cmbScheme->addItem(scheme);
    }
}
