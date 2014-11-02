#include "viewwidgetui.h"

ViewWidgetUi::ViewWidgetUi(QWidget* parent) : QGraphicsView(parent)
{ }

void ViewWidgetUi::wheelEvent(QWheelEvent* event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->delta() > 0)
            this->scale(1.1, 1.1);
        else
            this->scale(1 / 1.1, 1 / 1.1);
    }
    QGraphicsView::wheelEvent(event);
}
