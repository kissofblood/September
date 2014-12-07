#ifndef COMMON_H
#define COMMON_H

#include <QStringList>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QByteArray>
#include <QMenu>

class Common
{
public:
    Common() = delete;
    Common(const Common&) = delete;
    Common& operator =(const Common&) = delete;
    ~Common() = delete;

    static QStringList keyWordsFromFile(const QString& nameFile)
    {
        QStringList words;
        QFile file(":/keyWords/" + nameFile);
        if(file.open(QIODevice::ReadOnly))
            while(!file.atEnd())
            {
                QByteArray line = file.readLine();
                if(!line.isEmpty())
                    words.push_back(line.trimmed());
            }
        file.close();
        return words;
    }

    static QMenu* createMenuFileView()
    {
        static bool flag = true;
        static QMenu* menu = new QMenu;
        if(flag)
        {
            menu->addAction("Закрыть");
            menu->addAction("Копировать имя файла");
            menu->addSeparator();
            QMenu* view = menu->addMenu("Режим просмотра");
            view->addAction("Дерево")->setCheckable(true);
            QAction* list = view->addAction("Список");
            list->setCheckable(true);
            list->setChecked(true);
            QMenu* sort = menu->addMenu("Сортировать по");
            sort->addAction("Имени документа");
            sort->addAction("Пути к документа");
            flag = false;
        }
        return menu;
    }
};

#endif // COMMON_H
