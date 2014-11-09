#ifndef WIDGETSTYLE_H
#define WIDGETSTYLE_H

#include "assistant/keywords.h"
#include "assistant/graphicswidget.h"
#include "septembereditor.h"
#include <QWidget>
#include <algorithm>
#include <functional>

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
        WidgetStyle         *m_wgtStyle = nullptr;
        QGraphicsRectItem   *m_rectItem = nullptr;
        QPointF             m_topLeftRect;
        Qt::MouseButton     m_mouseButton = Qt::NoButton;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    };

    Ui::WidgetStyle             *ui             = nullptr;
    WidgetScene                 *m_scene        = nullptr;
    SeptemberEditor             *m_editor       = nullptr;
    QVector<GraphicsWidget*>    m_graphicsWgt_;
    QVector<GraphicsWidget*>    m_deleteGraphicsWgt_;

    QWidget* createWidget(const QString& name);
    void distinguishRect(const QRectF& rect);
    bool containsWidget(const QPointF& point);
};

#endif // WIDGETSTYLE_H
