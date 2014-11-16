#ifndef OBSERVERTEXT_H
#define OBSERVERTEXT_H

#include <QObject>
#include <QStringList>
#include <QStringListModel>
#include <QString>
#include <QHash>

class ObserverText : public QObject
{
    Q_OBJECT
public:
    ObserverText(const QStringList& properties, const QStringList& pseudo,
                 const QStringList& widgets,    const QStringList& sub,
                 const QStringList& other, QObject* parent = nullptr);
    ~ObserverText() override = default;

    void textParserHead(const QString& text);
    void textParserBody(const QString& text);

signals:
    void stringListModelChanged(QStringListModel* model);

private:
    QHash<QString, QStringListModel*> m_strListModel_;
    bool m_isTextParserHead = false;
};

#endif // OBSERVERTEXT_H
