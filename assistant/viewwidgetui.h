#ifndef VIEWWIDGETUI_H
#define VIEWWIDGETUI_H

#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>

class ViewWidgetUi : public QGraphicsView
{
public:
    explicit ViewWidgetUi(QWidget* parent = nullptr);
    ~ViewWidgetUi() override = default;

private:
    void wheelEvent(QWheelEvent* event) override;
};

#endif // VIEWWIDGETUI_H
