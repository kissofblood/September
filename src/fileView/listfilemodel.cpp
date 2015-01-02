#include "listfilemodel.h"

ListFileModel::ListFileModel(QObject* parent) : QAbstractListModel(parent)
{ }

QVariant ListFileModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid() || index.row() >= m_item_.size())
        return QVariant();
    if(role == Qt::DisplayRole)
        return m_item_[index.row()].file.fileName();
    else if(role == Qt::ToolTipRole)
        return m_item_[index.row()].file.filePath();
    return QVariant();
}

int ListFileModel::rowCount(const QModelIndex&) const
{ return m_item_.size(); }

QModelIndex ListFileModel::index(int row, int column, const QModelIndex& parent) const
{
    if(!this->hasIndex(row, column, parent))
        return QModelIndex();
    return this->createIndex(row, column);
}

bool ListFileModel::insertRows(int row, int count, const QModelIndex& parent)
{
    if(row <= m_item_.size())
    {
        this->beginInsertRows(parent, row, row + count - 1);
        for(int i = row; i < row + count; i++)
            m_item_.insert(row, Item());
        this->endInsertRows();
        return true;
    }
    return false;
}

bool ListFileModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if(row < m_item_.size())
    {
        this->beginRemoveRows(parent, row, row + count - 1);
        for(int i = row; i < row + count; i++)
            m_item_.removeAt(i);
        this->endRemoveRows();
    }
    return false;
}

void ListFileModel::addItem(const QString& file, CoreEditor* coreEditor, ListFileModel::SceneStyle* sceneStyle, ListFileModel::BufferUI* sceneUI)
{
    insertRows(m_item_.size(), 1);
    Item item;
    item.file.setFile(file);
    item.coreEditor = coreEditor;
    item.sceneStyle = sceneStyle;
    item.sceneUI = sceneUI;
    m_item_.replace(m_item_.size() - 1, item);
}

void ListFileModel::removeItem(int row)
{ removeRows(row, 1); }

std::tuple<QFileInfo, CoreEditor*, ListFileModel::SceneStyle*, ListFileModel::BufferUI*> ListFileModel::getItem(int row) const
{
    if(row < m_item_.size())
        return std::make_tuple(m_item_[row].file, m_item_[row].coreEditor, m_item_[row].sceneStyle, m_item_[row].sceneUI);
    return std::make_tuple(QFileInfo(), nullptr, nullptr, nullptr);
}

QModelIndex ListFileModel::getModelIndex(int row) const
{ return index(row, 0); }

int ListFileModel::containsFile(const QString& file)
{
    for(int i = 0; i < m_item_.size(); i++)
        if(m_item_[i].file.filePath() == file)
            return i;
    return -1;
}

void ListFileModel::replaceFile(const QString& oldFile, const QString& newFile)
{
    for(auto& item : m_item_)
        if(item.file.filePath() == oldFile)
        {
            item.file.setFile(newFile);
            break;
        }
}

void ListFileModel::changeTextTrue(int row)
{
    if(row < m_item_.size())
        m_item_[row].changeText = true;
}

QList<QPair<QFileInfo, CoreEditor*>> ListFileModel::getIsChangedText()
{
    QList<QPair<QFileInfo, CoreEditor*>> list;
    for(auto& item : m_item_)
        if(item.changeText)
            list.push_back({ item.file, item.coreEditor });
    return qMove(list);
}

void ListFileModel::changeTextFalse(CoreEditor* editor)
{
    for(auto& item : m_item_)
        if(item.coreEditor == editor)
            item.changeText = false;
}
