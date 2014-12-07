#include "treefileview.h"

TreeFileView::TreeFileView(QWidget* parent) : QTreeView(parent)
    , m_menu(Common::createMenuFileView())
{
    this->connect(m_menu, &QMenu::triggered, this, [this](QAction* action)
    {
        if(action->text() == "Список")
        {
            emit switchList();
            action->setChecked(true);
            for(QAction* act : m_menu->actions())
                if(act->text() == "Режим просмотра")
                {
                    act->menu()->actions().front()->setChecked(false);
                    break;
                }
        }
    });
}

void TreeFileView::contextMenuEvent(QContextMenuEvent* event)
{ m_menu->exec(event->globalPos()); }
