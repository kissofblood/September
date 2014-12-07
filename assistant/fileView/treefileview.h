#ifndef TREEFILEVIEW_H
#define TREEFILEVIEW_H

#include "assistant/common.h"
#include <QWidget>
#include <QTreeView>
#include <QMenu>
#include <QContextMenuEvent>

#include <QDebug>

class TreeFileView : public QTreeView
{
    Q_OBJECT
public:
    explicit TreeFileView(QWidget* parent = nullptr);
    ~TreeFileView() override = default;

signals:
    void switchList();

private:
    QMenu   *m_menu = nullptr;

    void contextMenuEvent(QContextMenuEvent* event) override;
};

#endif // TREEFILEVIEW_H
