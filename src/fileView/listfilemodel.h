#ifndef LISTFILEMODEL_H
#define LISTFILEMODEL_H

#include "src/coreEditor/coreeditor.h"
#include <QObject>
#include <QAbstractListModel>
#include <QVariant>
#include <QModelIndex>
#include <QString>
#include <QGraphicsScene>
#include <QBuffer>
#include <QList>
#include <QFileInfo>
#include <tuple>

class ListFileModel : public QAbstractListModel
{
    using SceneStyle    = QGraphicsScene;
    using BufferUI      = QBuffer;
public:
    explicit ListFileModel(QObject* parent = nullptr);
    ~ListFileModel() override = default;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    void addItem(const QString& file, CoreEditor* coreEditor, SceneStyle* sceneStyle, BufferUI* sceneUI);
    void removeItem(int row);
    std::tuple<QFileInfo, CoreEditor*, SceneStyle*, BufferUI*> getItem(int row) const;
    QModelIndex getModelIndex(int row) const;

private:
    struct Item
    {
        QFileInfo       file;
        CoreEditor      *coreEditor = nullptr;
        SceneStyle      *sceneStyle = nullptr;
        BufferUI        *sceneUI    = nullptr;
    };
    QList<Item> m_item_;
};

#endif // LISTFILEMODEL_H
