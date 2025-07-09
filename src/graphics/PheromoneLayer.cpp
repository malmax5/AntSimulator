#include "../../include/graphics/PheromoneLayer.hpp"

PheromoneLayer::PheromoneLayer(const PheromoneMap& map, QGraphicsItem* parent)
    : map(map), QGraphicsItem(parent)
{

}

QRectF PheromoneLayer::boundingRect() const
{
    return QRectF(0, 0, 1, 1);
}

void PheromoneLayer::paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget)
{
    painter->setPen(Qt::NoPen);

    for (const auto& point : map.getPheromonePoints())
    {
        painter->setBrush(QColor(255, 0, 0, point.strength * 50));
        painter->drawEllipse(point.pos, 0.001, 0.001);
    }
}
