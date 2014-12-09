#ifndef LISTFILEVIEW_H
#define LISTFILEVIEW_H

#include "assistant/common.h"
#include <QWidget>
#include <QListView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QStandardItemModel>

#include <QtWidgets>

class ListFileView : public QListView
{
    Q_OBJECT
public:
    explicit ListFileView(QWidget* parent = nullptr);
    ~ListFileView() override;

signals:
    void switchTree();
    void clickedCloseFile(int row);

private:
    QMenu       *m_menu     = nullptr;

    void contextMenuEvent(QContextMenuEvent* event) override;
};

#endif // LISTFILEVIEW_H
