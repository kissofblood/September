#ifndef OBSERVERCODEQSS_H
#define OBSERVERCODEQSS_H

#include <QObject>
#include <QStringList>
#include <QStringListModel>
#include <QString>
#include <QHash>
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <QHash>
#include <QMap>
#include <QVector>

#include <QDebug>

namespace qi = boost::spirit::qi;

class ObserverCodeQss : public QObject
{
    Q_OBJECT
public:
    ObserverCodeQss(const QStringList& properties, const QStringList& pseudo,
                    const QStringList& widgets,    const QStringList& sub,
                    const QStringList& other, QObject* parent = nullptr);
    ~ObserverCodeQss() override = default;

    void textParserHead(const QString& text);
    void textParserBody(const QString& text);
    QVector<int> checkingCodeQss(std::string& text, const QMap<std::string::iterator, int>& blockCh);

signals:
    void stringListModelChanged(QStringListModel* model);

private:
    class CheckingCodeQss : public qi::grammar<std::string::iterator, qi::space_type, std::string()>
    {
        using TypeRule = qi::rule<std::string::iterator, qi::space_type, std::string()>;
    public:
        CheckingCodeQss();
        ~CheckingCodeQss() = default;

    private:
        TypeRule m_expession,   m_header,   m_property;
        TypeRule m_body,        m_value,    m_function;
        TypeRule m_sub,         m_ignore,   m_selector;
    };

    QHash<QString, QStringListModel*> m_strListModel_;
    bool m_isTextParserHead = false;

};

#endif // OBSERVERCODEQSS_H
