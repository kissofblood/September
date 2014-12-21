#include "settingseptember.h"
#include "ui_settingseptember.h"

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
