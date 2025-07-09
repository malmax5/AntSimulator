#include "../../include/graphics/AntItem.hpp"

AntItem::AntItem(const Ant& ant, QGraphicsItem* parent)
    : QGraphicsEllipseItem(-2, -2, 4, 4, parent)
{
    setPos(ant.logicalPosition);
    setBrush(baseColor);
    setPen(Qt::NoPen);
    setZValue(10);
    hasFood = ant.hasFood;
}

void AntItem::updatePosition(const QPointF& newPos, bool hasFood)
{
    this->hasFood = hasFood;
    setPos(newPos);
}

void AntItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
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
