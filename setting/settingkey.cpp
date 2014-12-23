#include "settingkey.h"
#include "ui_settingkey.h"

SettingKey* SettingKey::m_singleton = nullptr;

SettingKey::SettingKey(QWidget* parent) : QDialog(parent),
    ui(new Ui::SettingKey)
{
    ui->setupUi(this);
    ui->grpScheme->setVisible(false);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({ "Действия", "Комбинация клавиш" });
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cmbGroup->addItem("Все");

    this->connect(ui->btnOk,        &QPushButton::clicked, this, &SettingKey::writeSetting);
    this->connect(ui->btnCancel,    &QPushButton::clicked, this, &SettingKey::clearContainer);
    this->connect(ui->btnCancel,    &QPushButton::clicked, this, &QDialog::close);
    this->connect(ui->btnDefault,   &QPushButton::clicked, this, &SettingKey::setDefaultScheme);
    this->connect(ui->btnDetails,   &QPushButton::clicked, this, &SettingKey::visibleGrpScheme);
    this->connect(ui->cmbGroup,     &QComboBox::currentTextChanged, this, &SettingKey::hideGroupRow);
    this->connect(ui->editSearch,   &QLineEdit::textChanged, this, &SettingKey::searchRow);
    this->connect(ui->tableWidget,  &QTableWidget::cellDoubleClicked, this, std::bind(&SettingKey::showBoxKey, this, std::placeholders::_1));
    this->connect(ui->btnCreateScheme, &QPushButton::clicked, m_boxScheme, &BoxScheme::showBoxScheme);
    this->connect(ui->btnDeleteScheme, &QPushButton::clicked, this, &SettingKey::deleteScheme);
    this->connect(ui->cmbScheme, &QComboBox::currentTextChanged, this, &SettingKey::selectScheme);
    this->setWindowTitle("Настройка комбинаций клавиш -- September");
}

SettingKey::~SettingKey()
{ delete ui; }

SettingKey* SettingKey::instance(QWidget* parent)
{
    if(m_singleton == nullptr)
        m_singleton = new SettingKey(parent);
    return m_singleton;
}

void SettingKey::readScheme()
{
    QStringList listScheme = m_settingApp->readSettingKey();
    if(listScheme.isEmpty())
    {
        ui->cmbScheme->addItem("Default");
        m_settingApp->writeSettingKey("Default", 0);
        m_scheme_.insert("Default", QVector<QPair<QString, QString>>());
    }
    else for(auto& scheme : listScheme)
    {
        if(ui->cmbScheme->findText(scheme) == -1)
            ui->cmbScheme->addItem(scheme);
        m_scheme_.insert(scheme, QVector<QPair<QString, QString>>());
    }
    ui->cmbScheme->setCurrentText(m_settingApp->readCurrentSettingKey());
}

void SettingKey::addValue(const QString& group, const QString& name)
{
    if(ui->cmbGroup->findText(group) == -1)
    {
        ui->cmbGroup->addItem(group);
        m_groupRow_.insert(group, QVector<int>());
    }
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(name));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem);
    m_groupRow_[group].push_back(ui->tableWidget->rowCount() - 1);
}

void SettingKey::addKey()
{
    for(int i = 0; i < ui->cmbScheme->count(); i++)
        for(int j = 0; j < ui->cmbGroup->count(); j++)
        {
            QString group = ui->cmbGroup->itemText(j);
            if(group != ui->cmbGroup->itemText(0))
                for(auto& row : m_groupRow_[group])
                {
                    QString scheme = ui->cmbScheme->itemText(i);
                    QString name = ui->tableWidget->item(row, 0)->text();
                    QString key = m_settingApp->readSettingKey(scheme, group, name);
                    if(scheme == ui->cmbScheme->currentText())
                        ui->tableWidget->item(row, 1)->setText(key);
                    m_scheme_[scheme].push_back({ name, key });
                }
        }
}

bool SettingKey::containsKey(const QString& group, const QString& name)
{ return m_settingApp->containsSettingKey(ui->cmbScheme->currentText(), group, name);  }

void SettingKey::writeDefaultKey(const QString& group, const QString& name, const QString& key)
{
    QString scheme = ui->cmbScheme->currentText();
    m_settingApp->writeSettingKey(scheme, group, name, key);
    m_settingApp->writeDefaultSettingKey(scheme, group, name, key);
}

QString SettingKey::readKey(const QString& group, const QString& name)
{ return m_settingApp->readSettingKey(ui->cmbScheme->currentText(), group, name); }

void SettingKey::visibleGrpScheme()
{
    static bool visible = false;
    if(visible)
    {
        ui->grpScheme->setVisible(false);
        visible = false;
    }
    else
    {
        ui->grpScheme->setVisible(true);
        visible = true;
    }
}

void SettingKey::hideGroupRow(const QString& text)
{
    static QVector<int> rowHidden;
    if(text == ui->cmbGroup->itemText(0))
    {
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            ui->tableWidget->setRowHidden(i, false);
        rowHidden.clear();
    }
    else
    {
        for(auto& row : rowHidden)
            ui->tableWidget->setRowHidden(row, false);
        rowHidden.clear();

        for(auto i = m_groupRow_.begin(); i != m_groupRow_.end(); i++)
            if(i.key() != text)
                for(auto& row : i.value())
                {
                    ui->tableWidget->setRowHidden(row, true);
                    rowHidden.push_back(row);
                }
    }
    searchRow(ui->editSearch->text());
}

void SettingKey::searchRow(const QString& text)
{
    auto funRowHidden = [this, text](int row)
    {
        QString rowC1 = ui->tableWidget->item(row, 0)->text();
        QString rowC2 = ui->tableWidget->item(row, 1)->text();
        if(rowC1.contains(text, Qt::CaseInsensitive) || rowC2.contains(text, Qt::CaseInsensitive))
            ui->tableWidget->setRowHidden(row, false);
        else
            ui->tableWidget->setRowHidden(row, true);
    };

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QString currentGroup = ui->cmbGroup->currentText();
        if(currentGroup == ui->cmbGroup->itemText(0))
            funRowHidden(i);
        else for(auto& rowGroup : m_groupRow_[currentGroup])
            if(rowGroup == i)
                funRowHidden(i);
    }
}

void SettingKey::showBoxKey(int row)
{
    m_boxKey->setTextMessage(ui->tableWidget->item(row, 0)->text(), row);
    m_boxKey->show();
    m_boxKey->setFocus();
}

void SettingKey::deleteScheme()
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

void SettingKey::selectScheme(const QString& text)
{
    if(text == ui->cmbScheme->itemText(0))
        ui->btnDeleteScheme->setEnabled(false);
    else
        ui->btnDeleteScheme->setEnabled(true);
    int row = 0;
    for(auto i = m_scheme_[text].begin(); i != m_scheme_[text].end(); i++)
    {
        ui->tableWidget->item(row, 0)->setText(i->first);
        ui->tableWidget->item(row, 1)->setText(i->second);
        row += 1;
    }
}

void SettingKey::writeSetting()
{
    for(auto& schemeRemove : m_removeScheme_)
        m_settingApp->removeSettingKey(schemeRemove);
    for(auto i = m_scheme_.begin(); i != m_scheme_.end(); i++)
        for(auto j = m_groupRow_.begin(); j != m_groupRow_.end(); j++)
            for(auto& row : j.value())
                m_settingApp->writeSettingKey(i.key(), j.key(), i.value()[row].first, i.value()[row].second);
    m_settingApp->writeCurrentSettingKey(ui->cmbScheme->currentText());
    for(int i = 0; i < ui->cmbScheme->count(); i++)
        m_settingApp->writeSettingKey(ui->cmbScheme->itemText(i), i);
    clearContainer();
    emit settingKeyOK();
    this->close();
}

void SettingKey::clearContainer()
{
    ui->cmbScheme->clear();
    m_scheme_.clear();
    m_removeScheme_.clear();
}

void SettingKey::setDefaultScheme()
{
    QString scheme = ui->cmbScheme->itemText(0);
    for(auto i = m_groupRow_.begin(); i != m_groupRow_.end(); i++)
        for(auto& row : i.value())
            m_scheme_[scheme][row].second = m_settingApp->readDefaultSettingKey(scheme, i.key(), m_scheme_[scheme][row].first);
    ui->cmbScheme->setCurrentIndex(0);
    if(ui->cmbScheme->count() == 1)
        selectScheme(ui->cmbScheme->currentText());
}

QString SettingKey::checkingItemKey(const QString& text)
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        if(i != ui->tableWidget->currentRow())
            if(ui->tableWidget->item(i, 1)->text() == text)
                return ui->tableWidget->item(i, 0)->text();
    return QString();
}

void SettingKey::addNameScheme(const QString& scheme)
{
    ui->cmbScheme->addItem(scheme);
    int count = ui->cmbScheme->count() - 1;
    ui->cmbScheme->setCurrentIndex(count);
    QVector<QPair<QString, QString>> vecRow;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        ui->tableWidget->item(i, 1)->setText(QString());
        vecRow.push_back({ ui->tableWidget->item(i, 0)->text(), ui->tableWidget->item(i, 1)->text() });
    }
    auto iterRemove = qFind(m_removeScheme_.begin(), m_removeScheme_.end(), scheme);
    if(iterRemove != m_removeScheme_.end())
        m_removeScheme_.erase(iterRemove);
    m_scheme_.insert(scheme, vecRow);
}

void SettingKey::addItemTable(const QString& group, const QString& name, const QString& key)
{
    if(ui->cmbGroup->findText(group) == -1)
    {
        ui->cmbGroup->addItem(group);
        m_groupRow_.insert(group, QVector<int>());
    }
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(name));
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(key));
    m_groupRow_[group].push_back(ui->tableWidget->rowCount() - 1);
}

void SettingKey::closeEvent(QCloseEvent*)
{ clearContainer(); }

void SettingKey::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape)
        this->close();
}

SettingKey::BoxKey::BoxKey(SettingKey* parent) : QDialog(parent)
    , m_settingKey(parent)
{
    QHBoxLayout* boxButton = new QHBoxLayout;
    boxButton->addStretch(1);
    boxButton->addWidget(m_button);
    boxButton->addWidget(m_cancel);

    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(m_lblPressKey);
    box->addWidget(m_lblMessage);
    box->addItem(boxButton);
    this->setLayout(box);
    this->setWindowTitle("Назначение клавиш");
    this->connect(m_button, &QPushButton::clicked, this, &BoxKey::funButton);
    this->connect(m_cancel, &QPushButton::clicked, this, &QDialog::close);

    m_lblPressKey->setVisible(false);
}

void SettingKey::BoxKey::setTextMessage(const QString& text, int row)
{
    m_button->setText("Нет");
    m_lblPressKey->setVisible(false);
    m_lblMessage->setText("Нажмите клавишу (или сочетание) для: <b>"+ text + "</b>");
    m_row = row;
}

void SettingKey::BoxKey::funButton()
{
    QString scheme = m_settingKey->ui->cmbScheme->currentText();
    QString rowText = m_settingKey->ui->tableWidget->item(m_row, 0)->text();
    if(m_button->text() == "Нет")
    {
        m_settingKey->ui->tableWidget->item(m_row, 1)->setText(QString());
        for(auto i = m_settingKey->m_scheme_[scheme].begin(); i != m_settingKey->m_scheme_[scheme].end(); i++)
            if(i->first == rowText)
            {
                i->second = QString();
                break;
            }
    }
    else if(m_button->text() == "Назначить")
    {
        m_settingKey->ui->tableWidget->item(m_row, 1)->setText(m_keyText);
        for(auto i = m_settingKey->m_scheme_[scheme].begin(); i != m_settingKey->m_scheme_[scheme].end(); i++)
            if(i->first == rowText)
            {
                i->second = m_keyText;
                break;
            }
    }
    this->close();
}

void SettingKey::BoxKey::keyPressEvent(QKeyEvent* event)
{
    auto keyF = [this](int key)
    {
        bool flag = false;
        switch(key)
        {
        case Qt::Key_F1: m_keyText += "F1"; flag = true; break;
        case Qt::Key_F2: m_keyText += "F2"; flag = true; break;
        case Qt::Key_F3: m_keyText += "F3"; flag = true; break;
        case Qt::Key_F4: m_keyText += "F4"; flag = true; break;
        case Qt::Key_F5: m_keyText += "F5"; flag = true; break;
        case Qt::Key_F6: m_keyText += "F6"; flag = true; break;
        case Qt::Key_F7: m_keyText += "F7"; flag = true; break;
        case Qt::Key_F8: m_keyText += "F8"; flag = true; break;
        case Qt::Key_F9: m_keyText += "F9"; flag = true; break;
        case Qt::Key_F10: m_keyText += "F10"; flag = true; break;
        case Qt::Key_F11: m_keyText += "F11"; flag = true; break;
        case Qt::Key_F12: m_keyText += "F12"; flag = true; break;
        }
        return flag;
    };

    auto keyModifier = [this, keyF](int key)
    {
        bool flag = false;
        switch(key)
        {
        case Qt::Key_1: m_keyText += '1'; flag = true; break;
        case Qt::Key_2: m_keyText += '2'; flag = true; break;
        case Qt::Key_3: m_keyText += '3'; flag = true; break;
        case Qt::Key_4: m_keyText += '4'; flag = true; break;
        case Qt::Key_5: m_keyText += '5'; flag = true; break;
        case Qt::Key_6: m_keyText += '6'; flag = true; break;
        case Qt::Key_7: m_keyText += '7'; flag = true; break;
        case Qt::Key_8: m_keyText += '8'; flag = true; break;
        case Qt::Key_9: m_keyText += '9'; flag = true; break;
        case Qt::Key_0: m_keyText += 'O'; flag = true; break;
        case Qt::Key_Q: m_keyText += 'Q'; flag = true; break;
        case Qt::Key_W: m_keyText += 'W'; flag = true; break;
        case Qt::Key_E: m_keyText += 'E'; flag = true; break;
        case Qt::Key_R: m_keyText += 'R'; flag = true; break;
        case Qt::Key_T: m_keyText += "T"; flag = true; break;
        case Qt::Key_Y: m_keyText += 'Y'; flag = true; break;
        case Qt::Key_U: m_keyText += 'U'; flag = true; break;
        case Qt::Key_I: m_keyText += 'I'; flag = true; break;
        case Qt::Key_O: m_keyText += 'O'; flag = true; break;
        case Qt::Key_P: m_keyText += 'P'; flag = true; break;
        case Qt::Key_A: m_keyText += 'A'; flag = true; break;
        case Qt::Key_S: m_keyText += 'S'; flag = true; break;
        case Qt::Key_D: m_keyText += 'D'; flag = true; break;
        case Qt::Key_F: m_keyText += 'F'; flag = true; break;
        case Qt::Key_G: m_keyText += 'G'; flag = true; break;
        case Qt::Key_H: m_keyText += 'H'; flag = true; break;
        case Qt::Key_J: m_keyText += 'J'; flag = true; break;
        case Qt::Key_K: m_keyText += 'K'; flag = true; break;
        case Qt::Key_L: m_keyText += 'L'; flag = true; break;
        case Qt::Key_Z: m_keyText += 'Z'; flag = true; break;
        case Qt::Key_X: m_keyText += 'X'; flag = true; break;
        case Qt::Key_C: m_keyText += 'C'; flag = true; break;
        case Qt::Key_V: m_keyText += 'V'; flag = true; break;
        case Qt::Key_B: m_keyText += 'B'; flag = true; break;
        case Qt::Key_N: m_keyText += 'N'; flag = true; break;
        case Qt::Key_M: m_keyText += 'M'; flag = true; break;
        case Qt::Key_Space: m_keyText += "Space";   flag = true; break;
        case Qt::Key_Up:    m_keyText += "Up";      flag = true; break;
        case Qt::Key_Left:  m_keyText += "Left";    flag = true; break;
        case Qt::Key_Down:  m_keyText += "Down";    flag = true; break;
        case Qt::Key_Right: m_keyText += "Right";   flag = true; break;
        case Qt::Key_Escape: m_keyText += "Esc";    flag = true; break;
        case Qt::Key_Plus: m_keyText += '+'; flag = true; break;
        case Qt::Key_Minus: m_keyText += '-'; flag = true; break;
        default: flag = keyF(key); break;
        }
        return flag;
    };

    m_keyText.clear();
    bool flag1 = false;
    bool flag2 = true;
    switch(event->modifiers())
    {
    case Qt::ShiftModifier:
        m_keyText += "Shift+";
        flag1 = keyModifier(event->key());
        flag2 = false;
        break;
    case Qt::ControlModifier:
        m_keyText += "Ctrl+";
        flag1 = keyModifier(event->key());
        flag2 = false;
        break;
    case Qt::AltModifier:
        m_keyText += "Alt+";
        flag1 = keyModifier(event->key());
        flag2 = false;
        break;
    case Qt::MetaModifier:
        m_keyText += "Meta+";
        flag1 = keyModifier(event->key());
        flag2 = false;
        break;
    case Qt::ShiftModifier | Qt::ControlModifier:
        m_keyText += "Shift+Ctrl+";
        flag1 = keyModifier(event->key());
        flag2 = false;
        break;
    case Qt::ShiftModifier | Qt::AltModifier:
        m_keyText += "Shift+Alt+";
        flag1 = keyModifier(event->key());
        flag2 = false;
        break;
    case Qt::ShiftModifier | Qt::MetaModifier:
        m_keyText += "Shift+Meta";
        flag1 = keyModifier(event->key());
        flag2 = false;
        break;
    case Qt::ControlModifier | Qt::AltModifier:
        m_keyText += "Ctrl+Alt+";
        flag1 = keyModifier(event->key());
        flag2 = false;
        break;
    case Qt::ControlModifier | Qt::MetaModifier:
        m_keyText += "Ctrl+Meta+";
        flag1 = keyModifier(event->key());
        flag2 = false;
        break;
    case Qt::AltModifier | Qt::MetaModifier:
        m_keyText += "Alt+Meta+";
        flag1 = keyModifier(event->key());
        flag2 = false;
        break;
    }

    if(flag2)
        flag1 = keyF(event->key());

    if(flag1)
    {
        m_lblPressKey->setVisible(true);
        m_lblPressKey->setText("Клавиша или сочетание: <b>" + m_keyText + "</b>");
        QString rowText = m_settingKey->checkingItemKey(m_keyText);
        if(!rowText.isEmpty())
            m_lblMessage->setText("Предупреждение: клавиша уже назначена для: <b>" + rowText + "</b>");
        m_button->setText("Назначить");
    }
}

SettingKey::BoxScheme::BoxScheme(SettingKey* parent) : QDialog(parent)
    , m_settingKey(parent)
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

void SettingKey::BoxScheme::showBoxScheme()
{
    m_edit->setText("Новая схема");
    m_edit->selectAll();
    this->show();
}

void SettingKey::BoxScheme::newScheme()
{
    QString scheme = m_edit->text();
    int countScheme = m_settingKey->ui->cmbScheme->count();
    for(int i = 0; i < countScheme; i++)
        if(scheme == m_settingKey->ui->cmbScheme->itemText(i))
        {
            for(int j = countScheme - 1; j >= 0; j--)
            {
                QString str = m_settingKey->ui->cmbScheme->itemText(j);
                if(str.contains(scheme))
                {
                    scheme += "_" + QString::number(str.remove(0, scheme.length() + 1).toInt() + 1);
                    break;
                }
            }
            break;
        }
    m_settingKey->addNameScheme(scheme);
    m_edit->clear();
    this->close();
}
