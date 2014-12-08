#ifndef WIDGETSTYLE_H
#define WIDGETSTYLE_H

#include "assistant/common.h"
#include "assistant/graphicswidget.h"
#include "assistant/coreEditor/coreeditor.h"
#include <QWidget>
#include <algorithm>
#include <functional>
#include <QList>

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

    void setFocusLineEdit();
    QGraphicsScene* getScene() const;
    QGraphicsScene* createScene();
    void setScene(QGraphicsScene* scene);

public slots:
    void setStyleSheetWidget(const QString& style);

private slots:
    void filterListWidget();
    void selectWidget();
    void deleteWidget();
    void clearScene();

private:
    class WidgetScene : public QGraphicsScene
    {
    public:
        WidgetScene(qreal x, qreal y, qreal widht, qreal height, WidgetStyle* parent = nullptr);
        ~WidgetScene() override = default;

        void addItemWidget(GraphicsWidget* wgt);
        QList<GraphicsWidget*> getItemWidget() const;
        GraphicsWidget* removeWidget(GraphicsWidget* wgt);
        void clearWidget();

    private:
        WidgetStyle             *m_wgtStyle = nullptr;
        QGraphicsRectItem       *m_rectItem = nullptr;
        QPointF                 m_topLeftRect;
        Qt::MouseButton         m_mouseButton = Qt::NoButton;
        QList<GraphicsWidget*>  m_graphicsWgt_;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    };

    Ui::WidgetStyle             *ui             = nullptr;
    WidgetScene                 *m_scene        = new WidgetScene(0, 0, 5000, 5000, this);
    CoreEditor                  *m_editor       = nullptr;
    QList<GraphicsWidget*>      m_deleteGraphicsWgt_;

    QWidget* createWidget(const QString& name);
    QWidget* setLayoutWidget(const QVector<QWidget*>& vecWgt, const QSize& size);
    void distinguishRect(const QRectF& rect);
    bool containsWidget(const QPointF& point);
};

#endif // WIDGETSTYLE_H
