#include "../../include/graphics/PheromoneLayer.hpp"

PheromoneLayer::PheromoneLayer(const PheromoneMap& map, QGraphicsSvgItem* parent)
    : map(map), QGraphicsSvgItem(parent)
{
    renderer = new QSvgRenderer(QString(":/icon_resources/resources/icons/pheromone.svg"));

    if (!renderer->isValid())
    {
        qWarning() << "Failed to create Pheromone SVGRenderer";
    }
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
        qreal opacity = qBound(0.0, point.strength, 1.0);

        painter->setOpacity(opacity);
        qDebug() << "tyt";
        QRectF targetRect(point.pos.x() - 0.005,
                          point.pos.y() - 0.005,
                          0.01, 0.01);
        
        renderer->render(painter, targetRect);
    }
}
