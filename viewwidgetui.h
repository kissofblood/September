#ifndef VIEWWIDGETUI_H
#define VIEWWIDGETUI_H

#include <QWidget>
#include <QtWidgets>

class ViewWidgetUi : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ViewWidgetUi(QWidget* parent = nullptr);
    ~ViewWidgetUi() override = default;

private:
    void wheelEvent(QWheelEvent* event) override;
};

#endif // VIEWWIDGETUI_H
