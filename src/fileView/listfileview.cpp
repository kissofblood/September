#include "listfileview.h"

ListFileView::ListFileView(QWidget* parent) : QListView(parent)
{   
    QAction* close = m_menu->addAction("Закрыть");
    QAction* copy = m_menu->addAction("Копировать имя файла");
    m_menu->addSeparator();
    QMenu* sort = m_menu->addMenu("Сортировать по");
    sort->addAction("Имени документа");
    sort->addAction("Пути к документа");

    auto readSettingKey = [close, copy, this]()
    {
        close->setShortcut(QKeySequence(m_settingKey->readKey(m_nameGroup, close->text())));
        copy->setShortcut(QKeySequence(m_settingKey->readKey(m_nameGroup, copy->text())));
    };

    m_settingKey->addValue(m_nameGroup, close->text());
    m_settingKey->addValue(m_nameGroup, copy->text());

    this->connect(close, &QAction::triggered, this, [this]()
    {
        QModelIndex index = this->currentIndex();
        if(index.isValid())
            emit clickedCloseFile(index.row());
    });
    this->connect(m_settingKey, &SettingKey::settingKeyOK, this, [this, readSettingKey]() { readSettingKey(); });

    m_settingKey->readScheme();
    if(m_settingKey->containsKey(m_nameGroup, close->text()))
        readSettingKey();
    else
    {
        m_settingKey->writeDefaultKey(m_nameGroup, close->text(), close->shortcut().toString());
        m_settingKey->writeDefaultKey(m_nameGroup, copy->text(), copy->shortcut().toString());
    }
}

void ListFileView::contextMenuEvent(QContextMenuEvent* event)
{
    if(this->currentIndex().isValid())
        m_menu->exec(event->globalPos());
}
