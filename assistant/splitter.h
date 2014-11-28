#ifndef SPLITTER_H
#define SPLITTER_H

#include <QWidget>
#include <QSplitter>

class Splitter : public QSplitter
{
public:
    explicit Splitter(QWidget* parent = nullptr);
    ~Splitter() override = default;

    void setHeight(int h);
    void setHideHandle(bool value);
};

#endif // SPLITTER_H
