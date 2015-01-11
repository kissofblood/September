#ifndef COMMON_H
#define COMMON_H

#include <QStringList>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QByteArray>

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
};

#endif // COMMON_H
