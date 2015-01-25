#include "settingseptember.h"
#include "ui_settingseptember.h"

SettingSeptember* SettingSeptember::m_singleton = nullptr;

SettingSeptember::SettingSeptember(QWidget* parent) : QDialog(parent),
    ui(new Ui::SettingSeptember)
{
    ui->setupUi(this);
    m_settingCommon = ui->widget;
    m_currentSetting = m_settingCommon;
    m_spacerSetting = ui->vSpacerSetting;

    QTreeWidgetItem* item = ui->treeSetting->topLevelItem(0);
    ui->treeSetting->setItemExpanded(item, true);
    ui->treeSetting->setItemExpanded(ui->treeSetting->topLevelItem(1), true);
    ui->treeSetting->setCurrentItem(item->child(0));

    this->connect(ui->treeSetting,  &QTreeWidget::itemClicked, std::bind(&SettingSeptember::selectSetting, this, std::placeholders::_1));
    this->connect(ui->btnOK,        &QPushButton::clicked, this, &SettingSeptember::writeSetting);
    this->connect(ui->btnOK,        &QPushButton::clicked, this, &QDialog::close);
    this->connect(ui->btnApply,     &QPushButton::clicked, this, &SettingSeptember::writeSetting);
    this->connect(ui->btnCancel,    &QPushButton::clicked, this, &QDialog::close);
    this->setWindowTitle("Настройка -- September");
}

SettingSeptember::~SettingSeptember()
{
    delete ui;
    delete m_settingCommon;
    delete m_settingFontAndColor;
    delete m_settingEditing;
    if(m_removeSpacer)
        delete m_spacerSetting;
}

SettingSeptember* SettingSeptember::instance(QWidget* parent)
{
    if(m_singleton == nullptr)
        m_singleton = new SettingSeptember(parent);
    return m_singleton;
}

void SettingSeptember::writeDefaultBackgroundColor(const QColor& background)
{ m_settingFontAndColor->writeBackgroundColor(background); }

void SettingSeptember::writeDefaultCurrentLineColor(const QColor& currentLine)
{ m_settingFontAndColor->writeCurrentLineColor(currentLine); }

void SettingSeptember::writeDefaultSearchTextColor(const QColor& searchText)
{ m_settingFontAndColor->writeSearchTextColor(searchText); }

void SettingSeptember::writeDefaultFontText(const QFont& font)
{ m_settingFontAndColor->writeFontText(font); }

void SettingSeptember::writeDefaultOtherQss(const QColor& color, QFont::Weight weight)
{ m_settingFontAndColor->writeOtherQss(color, weight); }

void SettingSeptember::writeDefaultSubQss(const QColor& color, QFont::Weight weight)
{ m_settingFontAndColor->writeSubQss(color, weight); }

void SettingSeptember::writeDefaultWidgetQss(const QColor& color, QFont::Weight weight)
{ m_settingFontAndColor->writeWidgetQss(color, weight); }

void SettingSeptember::writeDefaultPseudoQss(const QColor& color, QFont::Weight weight)
{ m_settingFontAndColor->writePseudoQss(color, weight); }

void SettingSeptember::writeDefaultPropertiesQss(const QColor& color, QFont::Weight weight)
{ m_settingFontAndColor->writePropertiesQss(color, weight); }

void SettingSeptember::writeDefaultCommentQss(const QColor& color, QFont::Weight weight)
{ m_settingFontAndColor->writeCommentQss(color, weight); }

void SettingSeptember::writeDefaultNumberQss(const QColor& color, QFont::Weight weight)
{ m_settingFontAndColor->writeNumberQss(color, weight); }

void SettingSeptember::writeDefaultWidthIndent(int indent)
{ m_settingEditing->writeWidthIndent(indent); }

void SettingSeptember::writeDefaultWidthTab(int tab)
{ m_settingEditing->writeWidthTab(tab); }

bool SettingSeptember::containsKey()
{
    if(m_settingApp->containsColorSettingSeptember() && m_settingApp->containsQssSettingSeptember())
        return true;
    return false;
}

QColor SettingSeptember::readBackgroundColor()
{ return m_settingFontAndColor->backgroundColor(); }

QColor SettingSeptember::readCurrentLineColor()
{ return m_settingFontAndColor->currentLineColor(); }

QColor SettingSeptember::readSearchTextColor()
{ return m_settingFontAndColor->searchTextColor(); }

QFont SettingSeptember::readFontText()
{ return m_settingFontAndColor->fontText(); }

QPair<QColor, QFont::Weight> SettingSeptember::readOtherQss()
{ return m_settingFontAndColor->otherQss(); }

QPair<QColor, QFont::Weight> SettingSeptember::readSubQss()
{ return m_settingFontAndColor->subQss(); }

QPair<QColor, QFont::Weight> SettingSeptember::readWidgetQss()
{ return m_settingFontAndColor->widgetQss(); }

QPair<QColor, QFont::Weight> SettingSeptember::readPseudoQss()
{ return m_settingFontAndColor->pseudoQss(); }

QPair<QColor, QFont::Weight> SettingSeptember::readPropertiesQss()
{ return m_settingFontAndColor->propertiesQss(); }

QPair<QColor, QFont::Weight> SettingSeptember::readCommentQss()
{ return m_settingFontAndColor->commentQss(); }

QPair<QColor, QFont::Weight> SettingSeptember::readNumberQss()
{ return m_settingFontAndColor->numberQss(); }

int SettingSeptember::readWidthIndent()
{ return m_settingEditing->widthIndent(); }

int SettingSeptember::readWidthTab()
{ return m_settingEditing->widthTab(); }

void SettingSeptember::addValueColor()
{ m_settingFontAndColor->readSettingColor(); }

void SettingSeptember::addValueQss()
{ m_settingFontAndColor->readSettingQss(); }

void SettingSeptember::addKey()
{ m_settingFontAndColor->readKey(); }

void SettingSeptember::readScheme()
{ m_settingFontAndColor->addScheme(); }

void SettingSeptember::readSettingEditing()
{ m_settingEditing->readSetting(); }

bool SettingSeptember::warningChangeFile()
{ return m_settingCommon->getState(); }

void SettingSeptember::selectSetting(QTreeWidgetItem* item)
{
    QString setting = item->text(0);
    QTreeWidgetItem* item1 = ui->treeSetting->topLevelItem(0);
    QTreeWidgetItem* item2 = ui->treeSetting->topLevelItem(1);
    if(setting == item1->child(0)->text(0))
    {
        ui->vLayoutSetting->removeWidget(m_currentSetting);
        m_currentSetting->setParent(nullptr);
        ui->vLayoutSetting->insertWidget(0, m_settingCommon);
        if(m_removeSpacer)
        {
            ui->vLayoutSetting->addItem(m_spacerSetting);
            m_removeSpacer = false;
        }
        m_currentSetting = m_settingCommon;
    }
    else if(setting == item2->child(0)->text(0))
    {
        ui->vLayoutSetting->removeWidget(m_currentSetting);
        m_currentSetting->setParent(nullptr);
        ui->vLayoutSetting->insertWidget(0, m_settingFontAndColor);
        ui->vLayoutSetting->removeItem(m_spacerSetting);
        m_currentSetting = m_settingFontAndColor;
        m_removeSpacer = true;
    }
    else if(setting == item2->child(1)->text(0))
    {
        ui->vLayoutSetting->removeWidget(m_currentSetting);
        m_currentSetting->setParent(nullptr);
        ui->vLayoutSetting->insertWidget(0, m_settingEditing);
        if(m_removeSpacer)
        {
            ui->vLayoutSetting->addItem(m_spacerSetting);
            m_removeSpacer = false;
        }
        m_currentSetting = m_settingEditing;
    }
}

void SettingSeptember::writeSetting()
{
    m_settingFontAndColor->writeSetting();
    m_settingCommon->writeState();
    m_settingEditing->writeSetting();
    emit settingSeptemberOK();
}

void SettingSeptember::closeEvent(QCloseEvent* event)
{
    m_settingFontAndColor->clearContainer();
    QDialog::closeEvent(event);
}
