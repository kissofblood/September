#include "listfilemodel.h"

ListFileModel::ListFileModel(QObject* parent) : QAbstractListModel(parent)
{ }

QVariant ListFileModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid() || index.row() >= m_item_.size())
        return QVariant();
    if(role == Qt::DisplayRole)
        return m_item_[index.row()].file;
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
    item.file = file;
    item.coreEditor = coreEditor;
    item.sceneStyle = sceneStyle;
    item.sceneUI = sceneUI;
    m_item_.replace(m_item_.size() - 1, item);
}

void ListFileModel::removeItem(int row)
{ removeRows(row, 1); }

std::tuple<CoreEditor*, ListFileModel::SceneStyle*, ListFileModel::BufferUI*> ListFileModel::getItem(int row) const
{
    if(row < m_item_.size())
        return std::make_tuple(m_item_[row].coreEditor, m_item_[row].sceneStyle, m_item_[row].sceneUI);
    return std::make_tuple(nullptr, nullptr, nullptr);
}

QModelIndex ListFileModel::getModelIndex(int row) const
{ return index(row, 0); }
