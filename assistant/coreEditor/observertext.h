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
    ObserverText(const QStringList& icons,  const QStringList& properties,
                 const QStringList& pseudo, const QStringList& widgets,
                 const QStringList& sub,    const QStringList& other, QObject* parent = nullptr);
    ~ObserverText() override = default;

signals:
    void stringListModelChanged(QStringListModel* model);

public slots:
    void textParser(const QString& text);

private:
    QHash<QString, QStringListModel*> m_strListModel_;
};

#endif // OBSERVERTEXT_H
