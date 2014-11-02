#ifndef WIDGETSTYLE_H
#define WIDGETSTYLE_H

#include "qsskeywords.h"
#include "graphicswidget.h"
#include <QWidget>

#include <QtWidgets>

namespace Ui {
class WidgetStyle;
}

class WidgetStyle : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetStyle(QWidget* parent = nullptr);
    ~WidgetStyle() override;

private slots:
    void filterListWidget();
    void selectWidget();

private:
    Ui::WidgetStyle     *ui             = nullptr;
    QGraphicsScene      *m_scene        = new QGraphicsScene(this);

    QWidget* createWidget(const QString& name);
};

#endif // WIDGETSTYLE_H
