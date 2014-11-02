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
    void deleteWidget();
    void clearScene();

private:
    class WidgetScene : public QGraphicsScene
    {
    public:
        WidgetScene(qreal x, qreal y, qreal widht, qreal height, QObject* parent = nullptr);
        ~WidgetScene() override = default;

    private:
        QGraphicsRectItem*  m_rectItem = nullptr;
        QPointF             m_topLeft;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    };

    Ui::WidgetStyle     *ui             = nullptr;
    WidgetScene         *m_scene        = nullptr;

    QWidget* createWidget(const QString& name);
};

#endif // WIDGETSTYLE_H
