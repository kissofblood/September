#ifndef OBSERVERCODEQSS_H
#define OBSERVERCODEQSS_H

#include <QObject>
#include <QStringList>
#include <QStringListModel>
#include <QString>
#include <QHash>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <string>
#include <functional>
#include <QHash>
#include <QMap>
#include <QVector>
#include <QTextBlock>

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

    void textParser(const QString& text);
    QVector<int> checkingCodeQss(std::string& text, QTextBlock& textBlock);
    void addAutoComplete(const QStringList& list);

signals:
    void stringListModelChanged(QStringListModel* model);

private:
    class CheckingCodeQss : public qi::grammar<std::string::iterator, qi::space_type>
    {
        using TypeRule = qi::rule<std::string::iterator, qi::space_type>;
    public:
        CheckingCodeQss(std::string::iterator first, std::string::iterator last);
        ~CheckingCodeQss() = default;

        std::string::iterator getIterator() const;

    private:
        TypeRule m_expession,   m_header,       m_property;
        TypeRule m_body,        m_value,        m_function;
        TypeRule m_sub,         m_comment,      m_selector;
        std::string::iterator   m_iterFirst;
        std::string::iterator   m_iterLast;

        void compareCh(const char& ch);
        void compareStr(const std::string& str);
    };

    QHash<QString, QStringListModel*> m_strListModel_;
};

#endif // OBSERVERCODEQSS_H
