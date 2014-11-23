#ifndef OBSERVERTEXT_H
#define OBSERVERTEXT_H

#include <QObject>
#include <QStringList>
#include <QStringListModel>
#include <QString>
#include <QHash>
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <QVector>

#include <QDebug>

namespace qi = boost::spirit::qi;

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
    QVector<int> checkingCodeQss(const QString& text);

signals:
    void stringListModelChanged(QStringListModel* model);

private:
    class CheckingCodesQss : public qi::grammar<std::string::iterator, qi::space_type, std::string()>
    {
        using TypeRule = qi::rule<std::string::iterator, qi::space_type, std::string()>;
    public:
        CheckingCodesQss();
        ~CheckingCodesQss() = default;

    private:
        TypeRule m_expession;
        TypeRule m_header;
        TypeRule m_property;
        TypeRule m_body;
        TypeRule m_value;
        TypeRule m_function;
        TypeRule m_sub;
        TypeRule m_ignore; //comment
        TypeRule m_pattern;
    };

    QHash<QString, QStringListModel*> m_strListModel_;
    bool m_isTextParserHead = false;
};

#endif // OBSERVERTEXT_H
