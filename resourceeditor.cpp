#include "resourceeditor.h"
#include "ui_resourceeditor.h"

ResourceEditor::ResourceEditor(QWidget* parent) : QWidget(parent)
    , ui(new Ui::ResourceEditor)
{
    ui->setupUi(this);
    ui->lnEditAlias->setEnabled(false);

    setEnableBtn(false);
    setEnableWgt(false);

    this->connect(ui->btnCreate,        &QPushButton::clicked, this, &ResourceEditor::createQrcOrRcc);
    this->connect(ui->btnAddItem,       &QPushButton::clicked, this, &ResourceEditor::addItem);
    this->connect(ui->btnRemove,        &QPushButton::clicked, this, &ResourceEditor::removeFile);
    this->connect(ui->btnAddImgItem,    &QPushButton::clicked, this, &ResourceEditor::addImgItem);
    this->connect(ui->btnRemoveItem,    &QPushButton::clicked, this, &ResourceEditor::removeItem);
    this->connect(ui->btnRegister,      &QPushButton::clicked, this, &ResourceEditor::registerFile);
    this->connect(ui->treeWgt,   &QTreeWidget::currentItemChanged,   this, &ResourceEditor::showImg);
    this->connect(ui->listWgt,   &QListWidget::currentItemChanged,   this, std::bind(&ResourceEditor::selectFile, this, std::placeholders::_1));
    this->connect(ui->treeWgt,   &QTreeWidget::itemSelectionChanged, this, &ResourceEditor::selectItem);
    this->connect(ui->lnEditPrefix, &QLineEdit::textEdited, this, &ResourceEditor::changeTextPrefix);
    this->connect(ui->lnEditAlias,  &QLineEdit::textEdited, this, &ResourceEditor::changeTextAlias);
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
    QBuffer* buff = new QBuffer(this);
    buff->setData(QByteArray("<RCC>\n</RCC>"));

    QListWidgetItem* item = new QListWidgetItem;
    item->setText(info.fileName());
    item->setToolTip(info.filePath());
    ui->listWgt->addItem(item);
    ui->listWgt->setCurrentRow(ui->listWgt->count() - 1);
    m_itemQrcAndRcc_.insert(item, { QList<QTreeWidgetItem*>(), buff });

    if(ui->listWgt->count() == 1)
        setEnableBtn(true);
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

    QString prefix = "/newPrefix" + QString::number(number.toInt() + 1);
    QListWidgetItem* curentPathFile = ui->listWgt->currentItem();
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWgt);
    item->setText(0, prefix);
    item->setExpanded(true);
    ui->treeWgt->setCurrentItem(item);
    m_itemQrcAndRcc_[curentPathFile].first.push_back(item);
    insertElementQrc(prefix);
    m_prevTextItem = prefix;

    if(ui->treeWgt->topLevelItemCount() == 1)
        setEnableWgt(true);
}

void ResourceEditor::addImgItem()
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
            insertElementQrc(item->text(0), str);
        }
    }
}

void ResourceEditor::removeFile()
{
    int row = ui->listWgt->currentRow();
    QListWidgetItem* item = ui->listWgt->takeItem(row);
    qDeleteAll(m_itemQrcAndRcc_[item].first);
    delete m_itemQrcAndRcc_[item].second;
    m_itemQrcAndRcc_.remove(item);
    delete item;

    if(ui->listWgt->count() == 0)
        setEnableBtn(false);
}

void ResourceEditor::removeItem()
{
    QTreeWidgetItem* item = ui->treeWgt->currentItem();
    if(item->parent() == nullptr)
    {
        QListWidgetItem* listItem = ui->listWgt->currentItem();
        auto iter = qFind(m_itemQrcAndRcc_[listItem].first.begin(), m_itemQrcAndRcc_[listItem].first.end(), item);
        m_itemQrcAndRcc_[listItem].first.erase(iter);
    }
    delete item;
    m_currentItem = ui->treeWgt->currentItem();

    if(ui->treeWgt->topLevelItemCount() == 0)
        setEnableWgt(false);
}

void ResourceEditor::showImg(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    QTreeWidgetItem* prevText = current;
    if(current == nullptr)
        return;

    bool value;
    if(prevText->parent() == nullptr)
    {
        ui->lblReview->setText("Просмотр");
        value = true;
    }
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
        value = false;
    }
    ui->lnEditPrefix->setEnabled(value);
    ui->lnEditAlias->setEnabled(!value);
    m_prevTextItem = prevText->text(0);
}

void ResourceEditor::selectFile(QListWidgetItem* item)
{
    forever if(ui->treeWgt->takeTopLevelItem(0) == nullptr)
        break;

    if(!m_itemQrcAndRcc_[item].first.isEmpty())
        ui->treeWgt->addTopLevelItems(m_itemQrcAndRcc_[item].first);
}

void ResourceEditor::selectItem()
{
    QTreeWidgetItem* item = ui->treeWgt->currentItem();
    if(item == nullptr)
    {
        ui->lnEditAlias->clear();
        ui->lnEditPrefix->clear();
    }
    else if(item->parent() == nullptr)
    {
        ui->lnEditAlias->clear();
        ui->lnEditPrefix->setText(item->text(0));
    }
    else
        ui->lnEditAlias->setText(item->text(1));
}

void ResourceEditor::changeTextPrefix(const QString& text)
{
    QTreeWidgetItem* item = ui->treeWgt->currentItem();
    if(item == nullptr)
        return;
    if(item->parent() == nullptr)
    {
        if(text.isEmpty())
            item->setText(0, m_prevTextItem);
        else
        {
            m_prevTextItem = text;
            if(m_prevTextItem[0] != '/')
                m_prevTextItem.insert(0, '/');
            for(int i = 0; i < ui->treeWgt->topLevelItemCount(); i++)
                if(ui->treeWgt->topLevelItem(i)->text(0) == m_prevTextItem)
                {
                    m_prevTextItem.remove(m_prevTextItem.length() - 1, 1);
                    break;
                }

            replacePrefixQrc(item->text(0), m_prevTextItem);
        }
        item->setText(0, m_prevTextItem);
        ui->lnEditPrefix->setText(m_prevTextItem);
    }
}

void ResourceEditor::changeTextAlias(const QString& text)
{
    QTreeWidgetItem* item = ui->treeWgt->currentItem();
    if(item == nullptr)
        return;
    if(item->parent() != nullptr)
    {
        item->setText(1, text);
        QTreeWidgetItem* child = item->parent();
        for(int i = 0; i < child->childCount(); i++)
            if(child->child(i) != item)
                if(child->child(i)->text(1) == item->text(1))
                {
                    QString itemText = item->text(1);
                    itemText.remove(itemText.length() - 1, 1);
                    item->setText(1, itemText);
                    break;
                }
        ui->lnEditAlias->setText(item->text(1));
    }
}

void ResourceEditor::registerFile()
{
    for(int i = 0; i < ui->treeWgt->topLevelItemCount(); i++)
    {
        QTreeWidgetItem* itemParent = ui->treeWgt->topLevelItem(i);
        for(int j = 0; j < itemParent->childCount(); j++)
        {
            QTreeWidgetItem* itemChild = itemParent->child(j);
            if(!itemChild->text(1).isEmpty())
                insertAliasQrc(itemParent->text(0), itemChild->text(1), itemChild->text(0));
        }
    }

    for(auto i = m_itemQrcAndRcc_.begin(); i != m_itemQrcAndRcc_.end(); i++)
    {        
        QFile file(i.key()->toolTip());
        file.open(QIODevice::WriteOnly);
        QBuffer* buff = i.value().second;
        buff->open(QIODevice::ReadOnly);
        file.write(buff->readAll());
        file.close();
        buff->close();
    }
}

void ResourceEditor::setEnableBtn(bool value)
{
    ui->btnAddItem->setEnabled(value);
    ui->btnRemove->setEnabled(value);
    ui->btnRegister->setEnabled(value);
}

void ResourceEditor::setEnableWgt(bool value)
{
    ui->btnAddImgItem->setEnabled(value);
    ui->btnRemoveItem->setEnabled(value);
    ui->lnEditPrefix->setEnabled(value);
}

void ResourceEditor::insertElementQrc(const QString& prefix, const QString& node)
{
    QBuffer* buff = m_itemQrcAndRcc_[ui->listWgt->currentItem()].second;
    buff->open(QIODevice::ReadOnly);
    QDomDocument doc;
    doc.setContent(buff->readAll());
    buff->close();

    QDomElement dElement = doc.documentElement();
    QDomNode dNode = dElement.firstChild();
    bool parentNull = true;
    while(!dNode.isNull())
    {
        QDomElement element = dNode.toElement();
        if(element.attribute("prefix") == prefix)
        {
            QDomElement elementFile = doc.createElement("file");
            elementFile.appendChild(doc.createTextNode(node));
            element.appendChild(elementFile);
            parentNull = false;
            break;
        }
        dNode = dNode.nextSibling();
    }

    if(parentNull)
    {
        QDomElement elementPrefix = doc.createElement("qresource");
        elementPrefix.setAttribute("prefix", prefix);
        dElement.appendChild(elementPrefix);
    }
    buff->setData(doc.toString(4).toUtf8());
}

void ResourceEditor::insertAliasQrc(const QString& prefix, const QString& value, const QString& node)
{
    QBuffer* buff = m_itemQrcAndRcc_[ui->listWgt->currentItem()].second;
    buff->open(QIODevice::ReadOnly);
    QDomDocument doc;
    doc.setContent(buff->readAll());
    buff->close();

    QDomElement dElement = doc.documentElement();
    QDomNode dNode = dElement.firstChild();
    while(!dNode.isNull())
    {
        QDomElement element = dNode.toElement();
        if(element.attribute("prefix") == prefix)
        {
            QDomElement elementFile = doc.createElement("file");
            elementFile.setAttribute("alias", value);
            elementFile.appendChild(doc.createTextNode(node));
            element.appendChild(elementFile);
            break;
        }
        dNode = dNode.nextSibling();
    }
    buff->setData(doc.toString(4).toUtf8());
}

void ResourceEditor::replacePrefixQrc(const QString& oldPrefix, const QString& newPrefix)
{
    QBuffer* buff = m_itemQrcAndRcc_[ui->listWgt->currentItem()].second;
    buff->open(QIODevice::ReadOnly);
    QDomDocument doc;
    doc.setContent(buff->readAll());
    buff->close();

    QDomNode dNode = doc.documentElement().firstChild();
    while(!dNode.isNull())
    {
        if(dNode.isElement())
        {
            QDomElement element = dNode.toElement();
            if(element.attribute("prefix") == oldPrefix)
            {
                element.setAttribute("prefix", newPrefix);
                break;
            }
        }
        dNode = dNode.nextSibling();
    }
    buff->setData(doc.toString(4).toUtf8());
}
