#include "splitter.h"

Splitter::Splitter(QWidget* parent) : QSplitter(parent)
{ }

void Splitter::setHeight(int h)
{ this->moveSplitter(h, 1); }

void Splitter::setHideHandle(bool value)
{
    if(!value)
    {
        this->setHandleWidth(10);
        this->handle(1)->setEnabled(true);
    }
    else
    {
        this->moveSplitter(this->size().height(), 0);
        this->setHandleWidth(0);
        this->handle(1)->setEnabled(false);
    }
}

