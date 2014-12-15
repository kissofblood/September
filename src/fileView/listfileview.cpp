#include "listfileview.h"

ListFileView::ListFileView(QWidget* parent) : QListView(parent)
{
    QAction* close = m_menu->addAction("Закрыть");
    QAction* copy = m_menu->addAction("Копировать имя файла");
    m_menu->addSeparator();
    QMenu* sort = m_menu->addMenu("Сортировать по");
    sort->addAction("Имени документа");
    sort->addAction("Пути к документа");

    this->connect(close, &QAction::triggered, this, [this]()
    {
        QModelIndex index = this->currentIndex();
        if(index.isValid())
            emit clickedCloseFile(index.row());
    });
    m_settingKey->addItem("Список документов", close->text());
    m_settingKey->addItem("Список документов", copy->text());
}

void ListFileView::contextMenuEvent(QContextMenuEvent* event)
{
    if(this->currentIndex().isValid())
        m_menu->exec(event->globalPos());
}
