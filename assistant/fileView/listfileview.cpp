#include "listfileview.h"

ListFileView::ListFileView(QWidget* parent) : QListView(parent)
    , m_menu(Common::createMenuFileView())
{
    this->connect(m_menu, &QMenu::triggered, this, [this](QAction* action)
    {
        if(action->text() == "Закрыть")
        {
            QModelIndex index = this->currentIndex();
            if(index.isValid())
                emit clickedCloseFile(index.row());
        }
        else if(action->text() == "Дерево")
        {
            emit switchTree();
            action->setChecked(true);
            for(QAction* act : m_menu->actions())
                if(act->text() == "Режим просмотра")
                {
                    act->menu()->actions().back()->setChecked(false);
                    break;
                }
        }
    });
}

ListFileView::~ListFileView()
{ delete m_menu; }

void ListFileView::contextMenuEvent(QContextMenuEvent* event)
{
    if(this->currentIndex().isValid())
        m_menu->exec(event->globalPos());
}
