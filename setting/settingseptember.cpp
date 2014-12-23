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

    this->connect(ui->treeSetting, &QTreeWidget::itemClicked, std::bind(&SettingSeptember::selectSetting, this, std::placeholders::_1));
    this->connect(ui->btnOK, &QPushButton::clicked, this, &SettingSeptember::writeSetting);
    this->setWindowTitle("Настройка -- September");
}

SettingSeptember::~SettingSeptember()
{
    delete ui;
    delete m_settingCommon;
    delete m_settingSession;
    delete m_settingFontAndColor;
    delete m_settingEditing;
    delete m_spacerSetting;
}

SettingSeptember* SettingSeptember::instance(QWidget* parent)
{
    if(m_singleton == nullptr)
        m_singleton = new SettingSeptember(parent);
    return m_singleton;
}

void SettingSeptember::writeDefaultBackgroundColor(const QColor& background)
{ m_settingApp->writeBackgroundColorSettingSeptember(background); }

void SettingSeptember::writeDefaultCurrentLineColor(const QColor& currentLine)
{ m_settingApp->writeCurrentLineColorSettingSeptember(currentLine); }

void SettingSeptember::writeDefaultSearchTextColor(const QColor& searchText)
{ m_settingApp->writeSearchTextColorSettingSeptember(searchText); }

bool SettingSeptember::containsKey()
{ return m_settingApp->containsColorSettingSeptember(); }

QColor SettingSeptember::readBackgroundColor()
{ return m_settingApp->readBackgroundColorSettingSeptember(); }

QColor SettingSeptember::readCurrentLineColor()
{ return m_settingApp->readCurrentLineColorSettingSeptember(); }

QColor SettingSeptember::readSearchTextColor()
{ return m_settingApp->readSearchTextColorSettingSeptember(); }

void SettingSeptember::addColor()
{
    m_settingFontAndColor->setBackgroundColor(m_settingApp->readBackgroundColorSettingSeptember());
    m_settingFontAndColor->setCurrentLineColor(m_settingApp->readCurrentLineColorSettingSeptember());
    m_settingFontAndColor->setSearchTextColor(m_settingApp->readSearchTextColorSettingSeptember());
}

void SettingSeptember::selectSetting(QTreeWidgetItem* item)
{
    static bool removeSpacer = false;
    QString setting = item->text(0);
    QTreeWidgetItem* item1 = ui->treeSetting->topLevelItem(0);
    QTreeWidgetItem* item2 = ui->treeSetting->topLevelItem(1);
    if(setting == item1->child(0)->text(0))
    {
        ui->vLayoutSetting->removeWidget(m_currentSetting);
        m_currentSetting->setParent(nullptr);
        ui->vLayoutSetting->insertWidget(0, m_settingCommon);
        if(removeSpacer)
        {
            ui->vLayoutSetting->addItem(m_spacerSetting);
            removeSpacer = false;
        }
        m_currentSetting = m_settingCommon;
    }
    else if(setting == item1->child(1)->text(0))
    {
        ui->vLayoutSetting->removeWidget(m_currentSetting);
        m_currentSetting->setParent(nullptr);
        ui->vLayoutSetting->insertWidget(0, m_settingSession);
        if(removeSpacer)
        {
            ui->vLayoutSetting->addItem(m_spacerSetting);
            removeSpacer = false;
        }
        m_currentSetting = m_settingSession;
    }
    else if(setting == item2->child(0)->text(0))
    {
        ui->vLayoutSetting->removeWidget(m_currentSetting);
        m_currentSetting->setParent(nullptr);
        ui->vLayoutSetting->insertWidget(0, m_settingFontAndColor);
        ui->vLayoutSetting->removeItem(m_spacerSetting);
        m_currentSetting = m_settingFontAndColor;
        removeSpacer = true;
    }
    else if(setting == item2->child(1)->text(0))
    {
        ui->vLayoutSetting->removeWidget(m_currentSetting);
        m_currentSetting->setParent(nullptr);
        ui->vLayoutSetting->insertWidget(0, m_settingEditing);
        if(removeSpacer)
        {
            ui->vLayoutSetting->addItem(m_spacerSetting);
            removeSpacer = false;
        }
        m_currentSetting = m_settingEditing;
    }
}

void SettingSeptember::writeSetting()
{
    m_settingApp->writeBackgroundColorSettingSeptember(m_settingFontAndColor->backgroundColor());
    m_settingApp->writeCurrentLineColorSettingSeptember(m_settingFontAndColor->currentLineColor());
    m_settingApp->writeSearchTextColorSettingSeptember(m_settingFontAndColor->searchTextColor());
    emit settingSeptemberOK();
    this->close();
}
