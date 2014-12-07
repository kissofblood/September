#include "splitter.h"

Splitter::Splitter(QWidget* parent) : QSplitter(parent)
{ }

void Splitter::setHeight(int h)
{ this->moveSplitter(h, 1); }

void Splitter::setWidth(int w)
{ this->moveSplitter(w, 1); }

void Splitter::setVisibleHeightHandle(bool value)
{
    if(value)
    {
        this->setHandleWidth(10);
        this->handle(1)->setCursor(Qt::SplitVCursor);
        this->handle(1)->setEnabled(true);
    }
    else
    {
        qDebug()<<this->size();
        this->moveSplitter(this->size().height(), 0);
        this->setHandleWidth(0);
        this->handle(1)->setCursor(Qt::ArrowCursor);
        this->handle(1)->setEnabled(false);
    }
}

void Splitter::setVisibleWidthHandle(bool value)
{
    if(value)
    {
        this->setHandleWidth(10);
        this->handle(1)->setCursor(Qt::SplitHCursor);
        this->handle(1)->setEnabled(true);
    }
    else
    {
        this->moveSplitter(0, 1);
        this->setHandleWidth(0);
        this->handle(1)->setCursor(Qt::ArrowCursor);
        this->handle(1)->setEnabled(false);
    }
}

