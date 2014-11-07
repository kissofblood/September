#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <QStringList>
#include <QString>
#include <QFile>
#include <QIODevice>
#include <QByteArray>

class KeyWords
{
public:
    KeyWords() = delete;
    KeyWords(const KeyWords&) = delete;
    KeyWords& operator =(const KeyWords&) = delete;
    ~KeyWords() = delete;

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

#endif // KEYWORDS_H
