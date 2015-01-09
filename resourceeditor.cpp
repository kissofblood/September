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
    this->connect(ui->btnOpen,          &QPushButton::clicked, this, &ResourceEditor::openQrcOrRcc);
    this->connect(ui->btnAddItem,       &QPushButton::clicked, this, &ResourceEditor::addItem);
    this->connect(ui->btnRemove,        &QPushButton::clicked, this, &ResourceEditor::removeFile);
    this->connect(ui->btnAddImgItem,    &QPushButton::clicked, this, &ResourceEditor::addImgItem);
    this->connect(ui->btnRemoveItem,    &QPushButton::clicked, this, &ResourceEditor::removeItem);
    this->connect(ui->btnRegister,      &QPushButton::clicked, this, &ResourceEditor::registerFile);
    this->connect(ui->treeWgt,   &QTreeWidget::currentItemChanged,   this, std::bind(&ResourceEditor::showImg, this, std::placeholders::_1));
    this->connect(ui->listWgt,   &QListWidget::currentItemChanged,   this, std::bind(&ResourceEditor::selectFile, this, std::placeholders::_1));
    this->connect(ui->treeWgt,   &QTreeWidget::itemSelectionChanged, this, &ResourceEditor::selectItem);
    this->connect(ui->lnEditPrefix, &QLineEdit::textEdited, this, &ResourceEditor::changeTextPrefix);
    this->connect(ui->lnEditAlias,  &QLineEdit::textEdited, this, &ResourceEditor::changeTextAlias);
}

ResourceEditor::~ResourceEditor()
{
    delete ui;
    for(auto i = m_itemQrcAndRcc_.begin(); i != m_itemQrcAndRcc_.end(); i++)
    {
        qDeleteAll(i.value().first);
        delete i.value().second;
    }
}

void ResourceEditor::createQrcOrRcc()
{
    QString path = QFileDialog::getSaveFileName(this, "Новый файл ресурсов", m_pathHome, "Файл ресурсов (*.qrc)");
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
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(info.fileName());
    item->setToolTip(info.filePath());
    ui->listWgt->addItem(item);
    ui->listWgt->setCurrentRow(ui->listWgt->count() - 1);
    m_itemQrcAndRcc_.insert(item, { QList<QTreeWidgetItem*>(), new QResource });

    if(ui->listWgt->count() == 1)
        setEnableBtn(true);
}

void ResourceEditor::openQrcOrRcc()
{
    QStringList path = QFileDialog::getOpenFileNames(this, "Открыть файл", m_pathHome, "Image (*.qrc *.rcc)");
    if(path.isEmpty())
        return;

    setEnableBtn(true);
    for(QString& str : path)
    {
        QFileInfo infoFile(str);
        QListWidgetItem* itemList = new QListWidgetItem;
        itemList->setText(infoFile.fileName());
        itemList->setToolTip(infoFile.filePath());
        ui->listWgt->addItem(itemList);
        m_itemQrcAndRcc_.insert(itemList, { QList<QTreeWidgetItem*>(), new QResource });

        if(infoFile.fileName().contains(QRegExp(R"(.+\.qrc)")))
        {
            QFile file(infoFile.filePath());
            if(!file.open(QIODevice::ReadOnly))
            {
                file.close();
                continue;
            }

            QDomDocument doc;
            doc.setContent(&file);

            QDomElement dElement = doc.documentElement();
            QDomNode dNode = dElement.firstChild();
            while(!dNode.isNull())
            {
                QDomElement element = dNode.toElement();
                QTreeWidgetItem* itemParent = new QTreeWidgetItem;
                itemParent->setText(0, element.attribute("prefix"));
                m_itemQrcAndRcc_[itemList].first.push_back(itemParent);
                QDomNode nodeChild = element.firstChild();
                QTreeWidgetItem* itemChild = nullptr;
                while(!nodeChild.isNull())
                {
                    QDomElement elementChild = nodeChild.toElement();
                    QString alias = elementChild.attribute("alias");
                    if(!alias.isEmpty())
                        itemChild->setText(1, alias);
                    else
                    {
                        itemChild = new QTreeWidgetItem(itemParent);
                        parserPathImg(itemChild, ui->listWgt->item(ui->listWgt->count() - 1), infoFile.path() + '/' + elementChild.text());
                        itemChild->setText(0, elementChild.text());
                    }
                    nodeChild  = nodeChild.nextSibling();
                }
                dNode = dNode.nextSibling();
            }
            file.close();
        }
        ui->listWgt->setCurrentRow(ui->listWgt->count() - 1);
    }
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
    m_prevTextItem = prefix;

    if(ui->treeWgt->topLevelItemCount() == 1)
        setEnableWgt(true);
}

void ResourceEditor::addImgItem()
{
    QStringList path = QFileDialog::getOpenFileNames(this, "Добавить файл", m_pathHome, "Image (*.png *.svg)");
    if(path.isEmpty())
        return;

    QTreeWidgetItem* item = ui->treeWgt->currentItem();
    if(item->parent() != nullptr)
        item = item->parent();

    for(QString& str : path)
    {
        bool flag = true;
        for(int i = 0; i < item->childCount(); i++)
            if(item->child(i)->toolTip(0) == str)
            {
                flag = false;
                break;
            }
        if(flag)
        {
            QTreeWidgetItem* itemImg = new QTreeWidgetItem(item);
            parserPathImg(itemImg, ui->listWgt->currentItem(), str);
        }
    }
}

void ResourceEditor::removeFile()
{
    int row = ui->listWgt->currentRow();
    QListWidgetItem* item = ui->listWgt->takeItem(row);
    qDeleteAll(m_itemQrcAndRcc_[item].first);
    QResource* res = m_itemQrcAndRcc_[item].second;
    if(res->unregisterResource(res->fileName()))
        emit removeRcc();
    delete res;
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

void ResourceEditor::showImg(QTreeWidgetItem* item)
{
    QTreeWidgetItem* prevText = item;
    if(item == nullptr)
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

        QString path = item->toolTip(0);
        if(QFileInfo(path).exists())
            ui->lblReview->setPixmap(QPixmap(path));
        else
            ui->lblReview->setText("Просмотр");
        value = false;
    }
    ui->lnEditPrefix->setEnabled(value);
    ui->lnEditAlias->setEnabled(!value);
    m_prevTextItem = prevText->text(0);
}

void ResourceEditor::selectFile(QListWidgetItem* item)
{
    auto setEnableButton = [this](bool value)
    {
        ui->btnAddItem->setEnabled(value);
        ui->btnAddImgItem->setEnabled(value);
        ui->btnRemoveItem->setEnabled(value);
    };

    if(item == nullptr)
    {
        ui->lblRegister->setText("Не зарегистрирован");
        return;
    }
    if(item->text().contains(QRegExp(R"(.+\.qrc)")))
        setEnableButton(true);
    else
        setEnableButton(false);

    forever if(ui->treeWgt->takeTopLevelItem(0) == nullptr)
        break;

    if(!m_itemQrcAndRcc_[item].first.isEmpty())
        ui->treeWgt->addTopLevelItems(m_itemQrcAndRcc_[item].first);

    QResource* res = m_itemQrcAndRcc_[item].second;
    if(res->fileName().isEmpty())
        ui->lblRegister->setText("Не зарегистрирован");
    else
        ui->lblRegister->setText("Зарегистрирован");
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
    for(auto iter = m_itemQrcAndRcc_.begin(); iter != m_itemQrcAndRcc_.end(); iter++)
    {
        QString xmlOut;
        QXmlStreamWriter stream(&xmlOut);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
            xmlOut.remove("<?xml version=\"1.0\"?>");
            stream.writeStartElement("RCC");
                for(QTreeWidgetItem* itemParent : iter.value().first)
                {
                    stream.writeStartElement("qresource");
                        stream.writeAttribute("prefix", itemParent->text(0));
                        for(int j = 0; j < itemParent->childCount(); j++)
                        {
                            QTreeWidgetItem* itemChild = itemParent->child(j);
                            stream.writeTextElement("file", itemChild->text(0));
                            if(!itemChild->text(1).isEmpty())
                            {
                                stream.writeStartElement("file");
                                    stream.writeAttribute("alias", itemChild->text(1));
                                    stream.writeDTD(itemChild->text(0));
                                    xmlOut.remove(xmlOut.lastIndexOf('>') + 1, 1);
                                stream.writeEndElement();
                                xmlOut.remove(xmlOut.lastIndexOf('<') - 1, 1);
                            }
                        }
                    stream.writeEndElement();
                }
            stream.writeEndElement();
        stream.writeEndDocument();

        QFileInfo infoFile(iter.key()->toolTip());
        QFile file(infoFile.absoluteFilePath());
        file.open(QIODevice::WriteOnly);
        file.write(xmlOut.toUtf8());
        file.close();

        QResource* res = iter.value().second;
        if(infoFile.filePath().contains(QRegExp(R"(.+\.qrc)")))
        {
            QString pathRcc = infoFile.path() + '/' + infoFile.fileName().remove("qrc") + "rcc";
            m_process->start("rcc --binary " + infoFile.absoluteFilePath() +
                             " -o " + pathRcc);
            if(m_process->waitForFinished())
            {
                res->setFileName(pathRcc);
                res->registerResource(res->fileName());
                ui->lblRegister->setText("Зарегистрирован");
            }
        }
        else
        {
            res->setFileName(infoFile.filePath());
            res->registerResource(res->fileName());
            ui->lblRegister->setText("Зарегистрирован");
        }
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

void ResourceEditor::parserPathImg(QTreeWidgetItem* treeItem, QListWidgetItem* listItem, const QString& pathImg)
{
    QFileInfo infoFile(listItem->toolTip());
    QFileInfo infoImg(pathImg);
    QString path = infoImg.path();
    if(path == infoFile.path())
        treeItem->setText(0, infoImg.fileName());
    else
    {
        forever
        {
            path = path.left(path.lastIndexOf('/'));
            if(path == infoFile.path())
                break;
        }
        treeItem->setText(0, infoImg.filePath().remove(path + '/'));
    }
    treeItem->setToolTip(0, infoImg.absoluteFilePath());
}
