#ifndef COMPLETERMODEL_H
#define COMPLETERMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <QtWidgets>

class CompleterModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CompleterModel(QObject* parent = nullptr);
    ~CompleterModel() override = default;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent) const override;

private:

};

#endif // COMPLETERMODEL_H
