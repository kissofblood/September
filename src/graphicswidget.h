#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QGraphicsItem>
#include <QWidget>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QKeyEvent>
#include <QGraphicsProxyWidget>
#include <QPointF>
#include <QSizeF>
#include <QBrush>
#include <QPen>
#include <QGraphicsColorizeEffect>
#include <QColor>
#include <QString>

class GraphicsWidget : public QGraphicsItem
{
public:
    GraphicsWidget(QWidget* wgt, const QPointF& point, QGraphicsItem* parent = nullptr);
    ~GraphicsWidget() override;

    QRectF boundingRect() const override;
    bool contains(const QPointF& point) const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* = nullptr) override;
    void selectWidget(bool value);
    QRectF boundingRectToScene();
    void setStyleSheet(const QString& styleSheet);

private:
    class Rect : public QGraphicsRectItem
    {
    public:
        explicit Rect(GraphicsWidget* parent = nullptr);
        ~Rect() override = default;

    private:
        GraphicsWidget      *m_rectWidget   = nullptr;
        Qt::MouseButton     m_mouseButton   = Qt::NoButton;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    };

    class ProxyWidget : public QGraphicsProxyWidget
    {
    public:
        ProxyWidget(GraphicsWidget* parent = nullptr);
        ~ProxyWidget() override = default;

    private:
        GraphicsWidget          *m_rectWidget   = nullptr;
        QPointF                 m_point;
        Qt::MouseButton         m_mouseButton   = Qt::NoButton;
        Qt::KeyboardModifier    m_keyboard      = Qt::NoModifier;

        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;
    };

    Rect    *m_rectTopLeft      = new Rect(this);
    Rect    *m_rectTopMid       = new Rect(this);
    Rect    *m_rectTopRight     = new Rect(this);
    Rect    *m_rectMidRight     = new Rect(this);
    Rect    *m_rectBottomRight  = new Rect(this);
    Rect    *m_rectBottomMid    = new Rect(this);
    Rect    *m_rectBottomLeft   = new Rect(this);
    Rect    *m_rectMidLeft      = new Rect(this);
    ProxyWidget *m_proxyWidget  = new ProxyWidget(this);
    QGraphicsColorizeEffect     *m_effect = new QGraphicsColorizeEffect;
    QRectF      m_rectWidget;
    bool        m_hideRect;

    void resizeRect(const QPointF& p, Rect* r);
    void setRect();
    void setVisibleRect(bool value);
    void moveRectWidget();
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
};

#endif // GRAPHICSWIDGET_H
