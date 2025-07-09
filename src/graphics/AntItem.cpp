#include "../../include/graphics/AntItem.hpp"

AntItem::AntItem(const Ant& ant, QGraphicsItem* parent)
    : QGraphicsEllipseItem(-0.005, -0.005, 0.01, 0.01, parent)
{
    setPos(ant.logicalPosition);
    setBrush(baseColor);
    setPen(Qt::NoPen);
    setZValue(10);
    hasFood = ant.hasFood;
}

QRectF AntItem::boundingRect() const
{
    return QRectF(-0.005, -0.005, 0.01, 0.01);
}

void AntItem::updatePosition(const QPointF& newPos, bool hasFood)
{
    this->hasFood = hasFood;
    setPos(newPos);
}

void AntItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::NoPen);

    if (hasFood)
    {
        painter->setBrush(Qt::blue);
    }
    else
    {
        painter->setBrush(baseColor);
    }

    painter->drawEllipse(rect());
}
