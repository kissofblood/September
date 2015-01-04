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
    this->connect(ui->btnCreateScheme,      &QPushButton::clicked, m_boxScheme, &BoxScheme::showBoxScheme);
    this->connect(ui->btnRemoveScheme,      &QPushButton::clicked, this, &SettingFontAndColor::deleteScheme);
    this->connect(ui->btnDefaultScheme,     &QPushButton::clicked, this, &SettingFontAndColor::setDefaultScheme);
    this->connect(ui->cmbOtherWeight,       &QComboBox::currentTextChanged, this, std::bind(&SettingFontAndColor::changeWeight, this));
    this->connect(ui->cmbPropertiesWeight,  &QComboBox::currentTextChanged, this, std::bind(&SettingFontAndColor::changeWeight, this));
    this->connect(ui->cmbPseudoWeight,      &QComboBox::currentTextChanged, this, std::bind(&SettingFontAndColor::changeWeight, this));
    this->connect(ui->cmbSubWeight,         &QComboBox::currentTextChanged, this, std::bind(&SettingFontAndColor::changeWeight, this));
    this->connect(ui->cmbWidgetWeight,      &QComboBox::currentTextChanged, this, std::bind(&SettingFontAndColor::changeWeight, this));
    this->connect(ui->cmbCommentWeight,     &QComboBox::currentTextChanged, this, std::bind(&SettingFontAndColor::changeWeight, this));
    this->connect(ui->cmbNumberWeight,      &QComboBox::currentTextChanged, this, std::bind(&SettingFontAndColor::changeWeight, this));
    this->connect(ui->cmbWidgetWeight,      &QComboBox::currentTextChanged, this, std::bind(&SettingFontAndColor::changeWeight, this));
    this->connect(ui->cmbScheme,            &QComboBox::currentTextChanged, this, &SettingFontAndColor::selectScheme);
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
    m_settingApp->writeFontTextSeptember(ui->cmbScheme->currentText(), font);
    m_settingApp->writeDefaultFontTextSeptember(font);
    ui->fontText->setCurrentFont(font);
}

void SettingFontAndColor::writeOtherQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writeOtherQssSeptember(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultOtherQssSeptember(color, weight);
    ui->btnOtherColor->setPalette(QPalette(color));
    ui->cmbOtherWeight->setCurrentIndex(ui->cmbOtherWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writePropertiesQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writePropertiesQssSeptember(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultPropertiesQssSeptember(color, weight);
    ui->btnPropertiesColor->setPalette(QPalette(color));
    ui->cmbPropertiesWeight->setCurrentIndex(ui->cmbPropertiesWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writePseudoQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writePseudoQssSeptember(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultPseudoQssSeptember(color, weight);
    ui->btnPseudoColor->setPalette(QPalette(color));
    ui->cmbPseudoWeight->setCurrentIndex(ui->cmbPseudoWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writeSubQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writeSubQssSeptember(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultSubQssSeptember(color, weight);
    ui->btnSubColor->setPalette(QPalette(color));
    ui->cmbSubWeight->setCurrentIndex(ui->cmbSubWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writeWidgetQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writeWidgetQssSeptember(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultWidgetQssSeptember(color, weight);
    ui->btnWidgetColor->setPalette(QPalette(color));
    ui->cmbWidgetWeight->setCurrentIndex(ui->cmbWidgetWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writeCommentQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writeCommentQssSeptember(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultCommentQssSeptember(color, weight);
    ui->btnCommentColor->setPalette(QPalette(color));
    ui->cmbCommentWeight->setCurrentIndex(ui->cmbCommentWeight->findData(static_cast<int>(weight)));
}

void SettingFontAndColor::writeNumberQss(const QColor& color, QFont::Weight weight)
{
    m_settingApp->writeNumberQssSeptember(ui->cmbScheme->currentText(), color, weight);
    m_settingApp->writeDefaultNumberQssSeptember(color, weight);
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
    if(!m_settingApp->containsColorSettingSeptember())
        return;

    QString scheme = ui->cmbScheme->currentText();
    ui->btnColorBackground->setPalette(QPalette(m_settingApp->readBackgroundColorSettingSeptember(scheme)));
    ui->btnColorCurrentLine->setPalette(QPalette(m_settingApp->readCurrentLineColorSettingSeptember(scheme)));
    ui->btnColorSearchText->setPalette(QPalette(m_settingApp->readSearchTextColorSettingSeptember(scheme)));
    ui->fontText->setCurrentFont(m_settingApp->readFontTextSeptember(scheme));
}

void SettingFontAndColor::readSettingQss()
{
    if(!m_settingApp->containsQssSettingSeptember())
        return;

    QPair<QColor, QFont::Weight> pair;
    QString scheme = ui->cmbScheme->currentText();
    pair = m_settingApp->readOtherQssSeptember(scheme);
    ui->btnOtherColor->setPalette(QPalette(pair.first));
    ui->cmbOtherWeight->setCurrentIndex(ui->cmbOtherWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readPropertiesQssSeptember(scheme);
    ui->btnPropertiesColor->setPalette(QPalette(pair.first));
    ui->cmbPropertiesWeight->setCurrentIndex(ui->cmbPropertiesWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readPseudoQssSeptember(scheme);
    ui->btnPseudoColor->setPalette(QPalette(pair.first));
    ui->cmbPseudoWeight->setCurrentIndex(ui->cmbPseudoWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readSubQssSeptember(scheme);
    ui->btnSubColor->setPalette(QPalette(pair.first));
    ui->cmbSubWeight->setCurrentIndex(ui->cmbSubWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readWidgetQssSeptember(scheme);
    ui->btnWidgetColor->setPalette(QPalette(pair.first));
    ui->cmbWidgetWeight->setCurrentIndex(ui->cmbWidgetWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readCommentQssSeptember(scheme);
    ui->btnCommentColor->setPalette(QPalette(pair.first));
    ui->cmbCommentWeight->setCurrentIndex(ui->cmbCommentWeight->findData(static_cast<int>(pair.second)));
    pair = m_settingApp->readNumberQssSeptember(scheme);
    ui->btnNumberColor->setPalette(QPalette(pair.first));
    ui->cmbNumberWeight->setCurrentIndex(ui->cmbNumberWeight->findData(static_cast<int>(pair.second)));
}

void SettingFontAndColor::writeSetting()
{
    for(auto& schemeRemove : m_removeScheme_)
        m_settingApp->removeSchemeSettingSeptember(schemeRemove);
    m_settingApp->writeCurrentSchemeSettingSeptember(ui->cmbScheme->currentText());
    for(int i = 0; i < ui->cmbScheme->count(); i++)
        m_settingApp->writeSchemeSettingSeptember(ui->cmbScheme->itemText(i), i);

    for(auto i = m_scheme_.begin(); i != m_scheme_.end(); i++)
    {
        m_settingApp->writeBackgroundColorSettingSeptember(i.key(), i.value().background);
        m_settingApp->writeCurrentLineColorSettingSeptember(i.key(), i.value().currentLine);
        m_settingApp->writeSearchTextColorSettingSeptember(i.key(), i.value().searchText);
        m_settingApp->writeFontTextSeptember(i.key(), i.value().fontText);
        m_settingApp->writeOtherQssSeptember(i.key(), i.value().qssOther.first, i.value().qssOther.second);
        m_settingApp->writePropertiesQssSeptember(i.key(), i.value().qssProperties.first, i.value().qssProperties.second);
        m_settingApp->writePseudoQssSeptember(i.key(), i.value().qssPseudo.first, i.value().qssPseudo.second);
        m_settingApp->writeSubQssSeptember(i.key(), i.value().qssSub.first, i.value().qssSub.second);
        m_settingApp->writeWidgetQssSeptember(i.key(), i.value().qssWidget.first, i.value().qssWidget.second);
        m_settingApp->writeCommentQssSeptember(i.key(), i.value().qssComment.first, i.value().qssComment.second);
        m_settingApp->writeNumberQssSeptember(i.key(), i.value().qssNumber.first, i.value().qssNumber.second);
    }
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

void SettingFontAndColor::clearContainer()
{
    ui->cmbScheme->clear();
    m_scheme_.clear();
    m_removeScheme_.clear();
}

void SettingFontAndColor::amendColorEdit()
{
    QPushButton* btn = qobject_cast<QPushButton*>(this->sender());
    QColor color = QColorDialog::getColor(btn->palette().color(QPalette::Button), this);
    if(!color.isValid())
        return;

    btn->setPalette(QPalette(color));
    QString scheme = ui->cmbScheme->currentText();
    if(btn->objectName() == ui->btnColorBackground->objectName())
        m_scheme_[scheme].background = color;
    else if(btn->objectName() == ui->btnColorCurrentLine->objectName())
        m_scheme_[scheme].currentLine = color;
    else if(btn->objectName() == ui->btnColorSearchText->objectName())
        m_scheme_[scheme].searchText = color;
    else if(btn->objectName() == ui->btnOtherColor->objectName())
        m_scheme_[scheme].qssOther.first = color;
    else if(btn->objectName() == ui->btnPropertiesColor->objectName())
        m_scheme_[scheme].qssProperties.first = color;
    else if(btn->objectName() == ui->btnPseudoColor->objectName())
        m_scheme_[scheme].qssPseudo.first = color;
    else if(btn->objectName() == ui->btnSubColor->objectName())
        m_scheme_[scheme].qssSub.first = color;
    else if(btn->objectName() == ui->btnWidgetColor->objectName())
        m_scheme_[scheme].qssWidget.first = color;
    else if(btn->objectName() == ui->btnCommentColor->objectName())
        m_scheme_[scheme].qssComment.first = color;
    else if(btn->objectName() == ui->btnNumberColor->objectName())
        m_scheme_[scheme].qssNumber.first = color;
}

void SettingFontAndColor::deleteScheme()
{
    if(QMessageBox::Ok == QMessageBox::information(this,
                          "Вопрос -- September",
                          "Удалить схему \"" + ui->cmbScheme->currentText() + "\"",
                          QMessageBox::Ok, QMessageBox::Cancel))
    {
        QString scheme = ui->cmbScheme->currentText();
        m_removeScheme_.push_back(scheme);
        m_scheme_.remove(scheme);
        ui->cmbScheme->removeItem(ui->cmbScheme->currentIndex());
    }
}

void SettingFontAndColor::changeWeight()
{
    if(m_scheme_.isEmpty())
        return;

    QString scheme = ui->cmbScheme->currentText();
    QComboBox* cmb = qobject_cast<QComboBox*>(this->sender());
    int weight = cmb->currentData().toInt();
    if(cmb->objectName() == ui->cmbOtherWeight->objectName())
        m_scheme_[scheme].qssOther.second = static_cast<QFont::Weight>(weight);
    else if(cmb->objectName() == ui->cmbPropertiesWeight->objectName())
        m_scheme_[scheme].qssProperties.second = static_cast<QFont::Weight>(weight);
    else if(cmb->objectName() == ui->cmbPseudoWeight->objectName())
        m_scheme_[scheme].qssPseudo.second = static_cast<QFont::Weight>(weight);
    else if(cmb->objectName() == ui->cmbSubWeight->objectName())
        m_scheme_[scheme].qssSub.second = static_cast<QFont::Weight>(weight);
    else if(cmb->objectName() == ui->cmbWidgetWeight->objectName())
        m_scheme_[scheme].qssWidget.second = static_cast<QFont::Weight>(weight);
    else if(cmb->objectName() == ui->cmbCommentWeight->objectName())
        m_scheme_[scheme].qssComment.second = static_cast<QFont::Weight>(weight);
    else if(cmb->objectName() == ui->cmbNumberWeight->objectName())
        m_scheme_[scheme].qssNumber.second = static_cast<QFont::Weight>(weight);
}

void SettingFontAndColor::selectScheme(const QString& scheme)
{
    if(m_scheme_.isEmpty())
        return;

    if(scheme == ui->cmbScheme->itemText(0))
        ui->btnRemoveScheme->setEnabled(false);
    else
        ui->btnRemoveScheme->setEnabled(true);

    ui->btnColorBackground->setPalette(QPalette(m_scheme_[scheme].background));
    ui->btnColorCurrentLine->setPalette(QPalette(m_scheme_[scheme].currentLine));
    ui->btnColorSearchText->setPalette(QPalette(m_scheme_[scheme].searchText));
    ui->fontText->setCurrentFont(m_scheme_[scheme].fontText);
    ui->btnOtherColor->setPalette(QPalette(m_scheme_[scheme].qssOther.first));
    ui->cmbOtherWeight->setCurrentIndex(ui->cmbOtherWeight->findData(static_cast<int>(m_scheme_[scheme].qssOther.second)));
    ui->btnPropertiesColor->setPalette(QPalette(m_scheme_[scheme].qssProperties.first));
    ui->cmbPropertiesWeight->setCurrentIndex(ui->cmbPropertiesWeight->findData(static_cast<int>(m_scheme_[scheme].qssProperties.second)));
    ui->btnPseudoColor->setPalette(QPalette(m_scheme_[scheme].qssPseudo.first));
    ui->cmbPseudoWeight->setCurrentIndex(ui->cmbPseudoWeight->findData(static_cast<int>(m_scheme_[scheme].qssPseudo.second)));
    ui->btnSubColor->setPalette(QPalette(m_scheme_[scheme].qssSub.first));
    ui->cmbSubWeight->setCurrentIndex(ui->cmbSubWeight->findData(static_cast<int>(m_scheme_[scheme].qssSub.second)));
    ui->btnWidgetColor->setPalette(QPalette(m_scheme_[scheme].qssWidget.first));
    ui->cmbWidgetWeight->setCurrentIndex(ui->cmbWidgetWeight->findData(static_cast<int>(m_scheme_[scheme].qssWidget.second)));
    ui->btnCommentColor->setPalette(QPalette(m_scheme_[scheme].qssComment.first));
    ui->cmbCommentWeight->setCurrentIndex(ui->cmbCommentWeight->findData(static_cast<int>(m_scheme_[scheme].qssComment.second)));
    ui->btnNumberColor->setPalette(QPalette(m_scheme_[scheme].qssNumber.first));
    ui->cmbNumberWeight->setCurrentIndex(ui->cmbNumberWeight->findData(static_cast<int>(m_scheme_[scheme].qssNumber.second)));
}

void SettingFontAndColor::setDefaultScheme()
{
    QString scheme = ui->cmbScheme->itemText(0);
    m_scheme_[scheme].background = m_settingApp->readDefaultBackgroundColorSettingSeptember();
    m_scheme_[scheme].currentLine = m_settingApp->readDefaultCurrentLineColorSettingSeptember();
    m_scheme_[scheme].searchText = m_settingApp->readDefaultSearchTextColorSettingSeptember();
    m_scheme_[scheme].fontText = m_settingApp->readDefaultFontTextSeptember();
    m_scheme_[scheme].qssOther = m_settingApp->readDefaultOtherQssSeptember();
    m_scheme_[scheme].qssProperties = m_settingApp->readDefaultPropertiesQssSeptember();
    m_scheme_[scheme].qssPseudo = m_settingApp->readDefaultPseudoQssSeptember();
    m_scheme_[scheme].qssSub = m_settingApp->readDefaultSubQssSeptember();
    m_scheme_[scheme].qssWidget = m_settingApp->readDefaultWidgetQssSeptember();
    m_scheme_[scheme].qssComment = m_settingApp->readDefaultCommentQssSeptember();
    m_scheme_[scheme].qssNumber = m_settingApp->readDefaultNumberQssSeptember();
    selectScheme(scheme);
}

void SettingFontAndColor::addNameScheme(const QString& scheme)
{
    ui->cmbScheme->addItem(scheme);
    auto iterRemove = qFind(m_removeScheme_.begin(), m_removeScheme_.end(), scheme);
    if(iterRemove != m_removeScheme_.end())
        m_removeScheme_.erase(iterRemove);
    m_scheme_.insert(scheme, FontAndColor());
    m_scheme_[scheme].background = backgroundColor();
    m_scheme_[scheme].currentLine = currentLineColor();
    m_scheme_[scheme].searchText = searchTextColor();
    m_scheme_[scheme].fontText = fontText();
    m_scheme_[scheme].qssOther = otherQss();
    m_scheme_[scheme].qssProperties = propertiesQss();
    m_scheme_[scheme].qssPseudo = pseudoQss();
    m_scheme_[scheme].qssSub = subQss();
    m_scheme_[scheme].qssWidget = widgetQss();
    m_scheme_[scheme].qssComment = commentQss();
    m_scheme_[scheme].qssNumber = numberQss();
    ui->cmbScheme->setCurrentText(scheme);
}

void SettingFontAndColor::addScheme()
{
    QStringList listScheme = m_settingApp->readSchemeSettingSeptember();
    if(listScheme.isEmpty())
    {
        ui->cmbScheme->addItem("Default");
        m_settingApp->writeSchemeSettingSeptember("Default", 0);
        m_scheme_.insert("Default", FontAndColor());
    }
    else for(auto& scheme : listScheme)
    {
        if(ui->cmbScheme->findText(scheme) == -1)
            ui->cmbScheme->addItem(scheme);
        m_scheme_.insert(scheme, FontAndColor());
    }
    ui->cmbScheme->setCurrentText(m_settingApp->readCurrentSchemeSettingSeptember());
    if(ui->cmbScheme->count() == 1)
        ui->btnRemoveScheme->setEnabled(false);
}

void SettingFontAndColor::readKey()
{
    for(int i = 0; i < ui->cmbScheme->count(); i++)
    {
        QString scheme = ui->cmbScheme->itemText(i);
        m_scheme_[scheme].background = m_settingApp->readBackgroundColorSettingSeptember(scheme);
        m_scheme_[scheme].currentLine = m_settingApp->readCurrentLineColorSettingSeptember(scheme);
        m_scheme_[scheme].searchText = m_settingApp->readSearchTextColorSettingSeptember(scheme);
        m_scheme_[scheme].fontText = m_settingApp->readFontTextSeptember(scheme);
        m_scheme_[scheme].qssOther = m_settingApp->readOtherQssSeptember(scheme);
        m_scheme_[scheme].qssProperties = m_settingApp->readPropertiesQssSeptember(scheme);
        m_scheme_[scheme].qssPseudo = m_settingApp->readPseudoQssSeptember(scheme);
        m_scheme_[scheme].qssSub = m_settingApp->readSubQssSeptember(scheme);
        m_scheme_[scheme].qssWidget = m_settingApp->readWidgetQssSeptember(scheme);
        m_scheme_[scheme].qssComment = m_settingApp->readCommentQssSeptember(scheme);
        m_scheme_[scheme].qssNumber = m_settingApp->readNumberQssSeptember(scheme);
    }
}

SettingFontAndColor::BoxScheme::BoxScheme(SettingFontAndColor* parent) : QDialog(parent)
    , m_setting(parent)
{
    QHBoxLayout* boxBtn = new QHBoxLayout;
    boxBtn->addStretch(1);
    boxBtn->addWidget(m_btnOk);
    boxBtn->addWidget(m_btnCancel);

    QVBoxLayout* boxV = new QVBoxLayout;
    boxV->addWidget(new QLabel("Название новой схемы:"));
    boxV->addWidget(m_edit);
    boxV->addItem(boxBtn);
    this->setLayout(boxV);
    this->setWindowTitle("Название новой схемы -- September");
    this->connect(m_btnCancel,  &QPushButton::clicked, m_edit, &QLineEdit::clear);
    this->connect(m_btnCancel,  &QPushButton::clicked, this, &QDialog::close);
    this->connect(m_btnOk,      &QPushButton::clicked, this, &BoxScheme::newScheme);
}

void SettingFontAndColor::BoxScheme::showBoxScheme()
{
    m_edit->setText("Новая схема");
    m_edit->selectAll();
    this->show();
}

void SettingFontAndColor::BoxScheme::newScheme()
{
    QString scheme = m_edit->text();
    int countScheme = m_setting->ui->cmbScheme->count();
    for(int i = 0; i < countScheme; i++)
        if(scheme == m_setting->ui->cmbScheme->itemText(i))
        {
            for(int j = countScheme - 1; j >= 0; j--)
            {
                QString str = m_setting->ui->cmbScheme->itemText(j);
                if(str.contains(scheme))
                {
                    scheme += "_" + QString::number(str.remove(0, scheme.length() + 1).toInt() + 1);
                    break;
                }
            }
            break;
        }
    m_setting->addNameScheme(scheme);
    m_edit->clear();
    this->close();
}
