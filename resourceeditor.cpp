#include "resourceeditor.h"
#include "ui_resourceeditor.h"

ResourceEditor::ResourceEditor(QWidget* parent) : QWidget(parent)
    , ui(new Ui::ResourceEditor)
{
    ui->setupUi(this);
    ui->treeWgt->setEditTriggers(QAbstractItemView::AnyKeyPressed);

    setEnableBtnItem1(false);
    setEnableBtnItem2(false);

    this->connect(ui->btnCreate,        &QPushButton::clicked, this, &ResourceEditor::createQrcOrRcc);
    this->connect(ui->btnAddItem,       &QPushButton::clicked, this, &ResourceEditor::addItem);
    this->connect(ui->btnRemove,        &QPushButton::clicked, this, &ResourceEditor::removeFile);
    this->connect(ui->btnAddFileItem,   &QPushButton::clicked, this, &ResourceEditor::addFileItem);
    this->connect(ui->btnRemoveItem,    &QPushButton::clicked, this, &ResourceEditor::removeItem);
    this->connect(ui->treeWgt,          &QTreeWidget::itemChanged, this, std::bind(&ResourceEditor::correctTextItem, this, std::placeholders::_1));
    this->connect(ui->treeWgt,   &QTreeWidget::currentItemChanged, this, &ResourceEditor::showFile);
}

ResourceEditor::~ResourceEditor()
{ delete ui; }

void ResourceEditor::createQrcOrRcc()
{
    QString path = QFileDialog::getSaveFileName(this, "Новый файл ресурсов", QString(), "Файл ресурсов (*.qrc)");
    if(path.isEmpty())
        return;
    if(!path.contains(QRegExp(R"(.+\.qrc)")))
        path += ".qrc";

    for(int i = 0; i < ui->listWgt->count(); i++)
        if(ui->listWgt->item(0)->toolTip() == path)
        {
            ui->listWgt->setCurrentRow(i);
            return;
        }

    QFileInfo info(path);
//    QFile file(path);
//    if(file.open(QIODevice::WriteOnly))
//        file.close();
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(info.fileName());
    item->setToolTip(info.filePath());
    ui->listWgt->addItem(item);
    ui->listWgt->setCurrentRow(ui->listWgt->count() - 1);
    m_itemQrcAndRcc_.insert(item, QList<QTreeWidgetItem*>());

    if(ui->listWgt->count() == 1)
        setEnableBtnItem1(true);
}

void ResourceEditor::addItem()
{
    QString number;
    if(ui->treeWgt->topLevelItemCount() != 0)
        for(int i = ui->treeWgt->topLevelItemCount() - 1; i >= 0; i--)
        {
            QString prev = ui->treeWgt->topLevelItem(i)->text(0);
            int j = prev.length() - 1;
            if(prev[j].isNumber())
            {
                for(; j >= 0; j--)
                {
                    if(prev[j].isNumber())
                        number.insert(0, prev[j]);
                    else
                        break;
                }
                break;
            }
        }

    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWgt);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setText(0, "/newPrefix" + QString::number(number.toInt() + 1));
    item->setExpanded(true);
    ui->treeWgt->setCurrentItem(item);

    m_itemQrcAndRcc_[ui->listWgt->currentItem()].push_back(item);

    if(ui->treeWgt->topLevelItemCount() == 1)
        setEnableBtnItem2(true);
}

void ResourceEditor::addFileItem()
{
    QStringList path = QFileDialog::getOpenFileNames(this, "Добавить файл", QString(), "Image (*.png *.svg)");
    if(path.isEmpty())
        return;

    QTreeWidgetItem* item = ui->treeWgt->currentItem();
    if(item->parent() != nullptr)
        item = item->parent();

    for(QString& str : path)
    {
        bool flag = true;
        for(int i = 0; i < item->childCount(); i++)
            if(item->child(i)->text(0) == str)
            {
                flag = false;
                break;
            }
        if(flag)
        {
            QTreeWidgetItem* itemFile = new QTreeWidgetItem(item);
            itemFile->setText(0, str);
        }
    }
}

void ResourceEditor::removeFile()
{
    int row = ui->listWgt->currentRow();
    QListWidgetItem* item = ui->listWgt->takeItem(row);
    m_itemQrcAndRcc_.remove(item);
    delete item;

    if(ui->listWgt->count() == 0)
        setEnableBtnItem1(false);
}

void ResourceEditor::removeItem()
{
    QTreeWidgetItem* item = ui->treeWgt->currentItem();
    if(item->parent() == nullptr)
    {
        QListWidgetItem* listItem = ui->listWgt->currentItem();
        auto iter = qFind(m_itemQrcAndRcc_[listItem].begin(), m_itemQrcAndRcc_[listItem].end(), item);
        m_itemQrcAndRcc_[listItem].erase(iter);
    }
    delete item;
    m_currentItem = ui->treeWgt->currentItem();

    if(ui->treeWgt->topLevelItemCount() == 0)
        setEnableBtnItem2(false);
}

void ResourceEditor::correctTextItem(QTreeWidgetItem* item)
{
    if(item->text(0).isEmpty())
        item->setText(0, m_prevTextItem);
    else
    {
        m_prevTextItem = item->text(0);
        if(m_prevTextItem[0] != '/')
        {
            m_prevTextItem.insert(0, '/');
            item->setText(0, m_prevTextItem);
        }
    }
}

void ResourceEditor::showFile(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    QTreeWidgetItem* prevText = current;
    if(prevText->parent() == nullptr)
        ui->lblReview->setText("Просмотр");
    else
    {
        prevText = prevText->parent();

        QString path = current->text(0);
        if(QFileInfo(path).exists())
            ui->lblReview->setPixmap(QPixmap(path));
        else
        {
            QMessageBox::warning(this, "Warning", "Файла нет");
            removeItem();
            if(previous->parent() == nullptr && m_currentItem->parent() == nullptr)
                ui->treeWgt->setCurrentItem(previous);
            else
                ui->treeWgt->setCurrentItem(m_currentItem);
        }
    }
    m_prevTextItem = prevText->text(0);
}

void ResourceEditor::setEnableBtnItem1(bool value)
{
    ui->btnAddItem->setEnabled(value);
    ui->btnRemove->setEnabled(value);
    ui->btnRegister->setEnabled(value);
}

void ResourceEditor::setEnableBtnItem2(bool value)
{
    ui->btnAddFileItem->setEnabled(value);
    ui->btnRemoveItem->setEnabled(value);
}
