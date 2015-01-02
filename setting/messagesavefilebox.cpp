#include "messagesavefilebox.h"
#include "ui_messagesavefilebox.h"

MessageSaveFileBox::MessageSaveFileBox(QWidget* parent) : QDialog(parent),
    ui(new Ui::MessageSaveFileBox)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->verticalHeader()->setVisible(false);

    this->connect(ui->btnSelectAll, &QPushButton::clicked,      this, &MessageSaveFileBox::selectAll);
    this->connect(ui->tableWidget,  &QTableWidget::itemClicked, this, std::bind(&MessageSaveFileBox::enableBtnSave, this));
    this->connect(ui->btnCancel,    &QPushButton::clicked,      this, &QDialog::close);
    this->connect(ui->btnSave,      &QPushButton::clicked,      this, &MessageSaveFileBox::saveFile);
    this->connect(ui->btnReject,    &QPushButton::clicked,      this, &MessageSaveFileBox::clickedReject);
    this->setWindowTitle("Сохранить документ -- September");
}

MessageSaveFileBox::~MessageSaveFileBox()
{ delete ui; }

void MessageSaveFileBox::appendChangeFile(const QList<QPair<QFileInfo, CoreEditor*>>& list)
{
    m_item_.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels({ "Документ", "Расположен" });
    for(auto& pair : list)
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        QTableWidgetItem* item = new QTableWidgetItem(pair.first.fileName());
        item->setCheckState(Qt::Checked);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, item);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(pair.first.filePath()));
        m_item_.push_back(pair.second);
    }
}

void MessageSaveFileBox::selectAll()
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem* item = ui->tableWidget->item(i, 0);
        item->setCheckState(Qt::Checked);
    }
    ui->btnSave->setEnabled(true);
}

void MessageSaveFileBox::enableBtnSave()
{
    bool enable = false;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        if(ui->tableWidget->item(i, 0)->checkState() == Qt::Checked)
        {
            enable = true;
            break;
        }
    ui->btnSave->setEnabled(enable);
}

void MessageSaveFileBox::saveFile()
{
    QList<QPair<QFileInfo, CoreEditor*>> list;
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        if(ui->tableWidget->item(i, 0)->checkState() == Qt::Checked)
            list.push_back({ ui->tableWidget->item(i, 1)->text(), m_item_[i] });
    emit clickedSaveFile(list);
}
