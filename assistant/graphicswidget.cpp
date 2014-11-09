#include "graphicswidget.h"

GraphicsWidget::GraphicsWidget(QWidget* wgt, QGraphicsItem* parent) : QGraphicsItem(parent)
    , m_rectWidget(3, 3, wgt->width() + 3, wgt->height() + 3)
{
    m_effect->setColor(QColor(103, 157, 205));
    m_effect->setStrength(0);
    m_proxyWidget->setWidget(wgt);
    m_proxyWidget->setPos(5, 5);
    m_proxyWidget->setGraphicsEffect(m_effect);

    m_rectTopLeft->setCursor(Qt::SizeFDiagCursor);
    m_rectTopMid->setCursor(Qt::SizeVerCursor);
    m_rectTopRight->setCursor(Qt::SizeBDiagCursor);
    m_rectMidRight->setCursor(Qt::SizeHorCursor);
    m_rectBottomRight->setCursor(Qt::SizeFDiagCursor);
    m_rectBottomMid->setCursor(Qt::SizeVerCursor);
    m_rectBottomLeft->setCursor(Qt::SizeBDiagCursor);
    m_rectMidLeft->setCursor(Qt::SizeHorCursor);

    setRect();
    setVisibleRect(false);
    this->setAcceptHoverEvents(true);
}

GraphicsWidget::~GraphicsWidget()
{ delete m_effect; }

QRectF GraphicsWidget::boundingRect() const
{ return { m_rectWidget.x() - 3, m_rectWidget.y() - 3, m_rectWidget.width() + 6, m_rectWidget.height() + 6 }; }

bool GraphicsWidget::contains(const QPointF& point) const
{ return this->mapToScene(boundingRect()).boundingRect().contains(point); }

void GraphicsWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if(m_hideRect)
    {
        painter->setPen(Qt::blue);
        painter->drawRect(m_rectWidget);
    }
}

void GraphicsWidget::selectWidget(bool value)
{
    if(value)
        m_effect->setStrength(1.0);
    else
        m_effect->setStrength(0);
}

QRectF GraphicsWidget::boundingRectToScene()
{ return this->mapToScene(boundingRect()).boundingRect(); }

void GraphicsWidget::setStyleSheet(const QString& styleSheet)
{ m_proxyWidget->widget()->setStyleSheet(styleSheet); }

void GraphicsWidget::resizeRect(const QPointF& p, Rect* r)
{
    QRectF rectWgt = m_rectWidget;
    if(r == m_rectTopLeft)
        rectWgt.setTopLeft(p);
    else if(r == m_rectTopMid)
        rectWgt.setTop(p.y());
    else if(r == m_rectTopRight)
        rectWgt.setTopRight(p);
    else if(r == m_rectMidRight)
        rectWgt.setRight(p.x());
    else if(r == m_rectBottomRight)
        rectWgt.setBottomRight(p);
    else if(r == m_rectBottomMid)
        rectWgt.setBottom(p.y());
    else if(r == m_rectBottomLeft)
        rectWgt.setBottomLeft(p);
    else if(r == m_rectMidLeft)
        rectWgt.setLeft(p.x());

    QSizeF sizeRectWidget = rectWgt.size();
    QSizeF sizeProxyWidget = m_proxyWidget->minimumSize();
    if(sizeRectWidget.width() > sizeProxyWidget.width() + 3
        && sizeRectWidget.height() > sizeProxyWidget.height() + 3)
    {
        this->prepareGeometryChange();
        m_rectWidget = rectWgt;
        QRectF rectProxyWgt(rectWgt.x() + 2, rectWgt.y() + 2, rectWgt.width() - 3, rectWgt.height() - 3);
        m_proxyWidget->setGeometry(rectProxyWgt);
        setRect();
    }
}

void GraphicsWidget::setRect()
{
    m_rectTopLeft->setRect(m_rectWidget.left() - 3, m_rectWidget.top() - 3, 6, 6);
    m_rectTopMid->setRect(m_rectWidget.left() + m_rectWidget.width() / 2 - 3, m_rectWidget.top() - 3, 6, 6);
    m_rectTopRight->setRect(m_rectWidget.right() - 3, m_rectWidget.top() - 3, 6, 6);
    m_rectMidRight->setRect(m_rectWidget.right() - 3, m_rectWidget.top() + m_rectWidget.height() / 2 - 3, 6, 6);
    m_rectBottomRight->setRect(m_rectWidget.right() - 3, m_rectWidget.bottom() - 3, 6, 6);
    m_rectBottomMid->setRect(m_rectWidget.left() + m_rectWidget.width() / 2 - 3, m_rectWidget.bottom() - 3, 6, 6);
    m_rectBottomLeft->setRect(m_rectWidget.left() - 3, m_rectWidget.bottom() - 3, 6, 6);
    m_rectMidLeft->setRect(m_rectWidget.left() - 3, m_rectWidget.top() + m_rectWidget.height() / 2 - 3, 6, 6);
}

void GraphicsWidget::setVisibleRect(bool value)
{
    m_rectTopLeft->setVisible(value);
    m_rectTopMid->setVisible(value);
    m_rectTopRight->setVisible(value);
    m_rectMidRight->setVisible(value);
    m_rectBottomRight->setVisible(value);
    m_rectBottomMid->setVisible(value);
    m_rectBottomLeft->setVisible(value);
    m_rectMidLeft->setVisible(value);
    m_hideRect = value;
    this->update();
}

void GraphicsWidget::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    setVisibleRect(true);
    QGraphicsItem::hoverEnterEvent(event);
}

void GraphicsWidget::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    setVisibleRect(false);
    QGraphicsItem::hoverLeaveEvent(event);
}

GraphicsWidget::Rect::Rect(QGraphicsItem* parent) : QGraphicsRectItem(parent)
    , m_rectWidget(qgraphicsitem_cast<GraphicsWidget*>(parent))
{
    this->setBrush(QBrush(Qt::blue));
    this->setPen(QPen(Qt::blue));
}

void GraphicsWidget::Rect::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_mouseButton = Qt::LeftButton;
        m_rectWidget->resizeRect(event->pos(), this);
    }
    else
        m_mouseButton = Qt::NoButton;
}

void GraphicsWidget::Rect::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_mouseButton == Qt::LeftButton)
        m_rectWidget->resizeRect(event->pos(), this);
}

GraphicsWidget::ProxyWidget::ProxyWidget(QGraphicsItem* parent) : QGraphicsProxyWidget(parent)
  , m_rectWidget(qgraphicsitem_cast<GraphicsWidget*>(parent))
{ }

void GraphicsWidget::ProxyWidget::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier)
    {
        m_mouseButton = Qt::LeftButton;
        m_keyboard = Qt::ControlModifier;
        m_point = event->pos();
        this->setCursor(Qt::ClosedHandCursor);
    }
    else
    {
        m_mouseButton = Qt::NoButton;
        m_keyboard = Qt::NoModifier;
        QGraphicsProxyWidget::mousePressEvent(event);
    }
}

void GraphicsWidget::ProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_mouseButton == Qt::LeftButton && m_keyboard == Qt::ControlModifier)
    {
        QPointF result = event->pos() - m_point;
        m_rectWidget->moveBy(result.x(), result.y());
    }
    else
        QGraphicsProxyWidget::mouseMoveEvent(event);
}

void GraphicsWidget::ProxyWidget::keyPressEvent(QKeyEvent* event)
{
    if(event->modifiers() == Qt::ControlModifier)
        this->setCursor(Qt::OpenHandCursor);
    else
        QGraphicsProxyWidget::keyPressEvent(event);
}

void GraphicsWidget::ProxyWidget::keyReleaseEvent(QKeyEvent* event)
{
    this->setCursor(Qt::ArrowCursor);
    m_keyboard = Qt::NoModifier;
    QGraphicsProxyWidget::keyReleaseEvent(event);
}
