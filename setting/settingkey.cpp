#include "settingkey.h"
#include "ui_settingkey.h"

SettingKey* SettingKey::m_singleton = nullptr;

SettingKey::SettingKey(QWidget* parent) : QDialog(parent),
    ui(new Ui::SettingKey)
{
    ui->setupUi(this);
   // ui->grpScheme->setVisible(false);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({ "Действия", "Комбинация клавиш" });
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cmbGroup->addItem("Все");
    ui->cmbScheme->addItem("Default");

    this->connect(ui->btnCancel,    &QPushButton::clicked, this, &QDialog::close);
    this->connect(ui->btnDetails,   &QPushButton::clicked, this, &SettingKey::visibleGrpScheme);
    this->connect(ui->cmbGroup,     &QComboBox::currentTextChanged, this, &SettingKey::hideGroupRow);
    this->connect(ui->editSearch,   &QLineEdit::textChanged, this, &SettingKey::searchRow);
    this->connect(ui->tableWidget,  &QTableWidget::cellDoubleClicked, this, std::bind(&SettingKey::showBoxKey, this, std::placeholders::_1));
    this->connect(ui->btnCreateScheme, &QPushButton::clicked, m_boxScheme, &BoxScheme::showBoxScheme);
    this->connect(ui->btnDeleteScheme, &QPushButton::clicked, this, &SettingKey::deleteScheme);
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

void SettingKey::addItem(const QString& group, const QString& name, const QString& key)
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
    if(text == "Все")
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
        if(currentGroup == "Все")
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
        ui->cmbScheme->removeItem(ui->cmbScheme->currentIndex());
    }
}

QString SettingKey::checkingItemKey(const QString& text)
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        if(i != ui->tableWidget->currentRow())
            if(ui->tableWidget->item(i, 1)->text() == text)
                return ui->tableWidget->item(i, 0)->text();
    return QString();
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
    if(m_button->text() == "Нет")
        m_settingKey->ui->tableWidget->item(m_row, 1)->setText(QString());
    else if(m_button->text() == "Назначить")
        m_settingKey->ui->tableWidget->item(m_row, 1)->setText(m_keyText);
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
    m_settingKey->ui->cmbScheme->addItem(scheme);
    m_settingKey->ui->cmbScheme->setCurrentIndex(countScheme);
    m_edit->clear();
    this->close();
}
