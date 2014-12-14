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
    void setWidth(int w);
    void setVisibleHeightHandle(bool value);
    void setVisibleWidthHandle(bool value);
};

#endif // SPLITTER_H
