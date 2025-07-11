#include "../../include/graphics/AntItem.hpp"

#include <QSvgRenderer>

AntItem::AntItem(const Ant& ant, QGraphicsSvgItem* parent)
    : QGraphicsSvgItem(parent)
{
    setSharedRenderer(new QSvgRenderer(QString(":/icon_resources/resources/icons/ant.svg")));
    if (!renderer()->isValid())
    {
        qWarning() << "Failed to load Ant SVG";
    }

    QRectF bounds = boundingRect();
    QTransform baseTransform = QTransform();
    baseTransform.scale(scaleFactor, scaleFactor);
    baseTransform.translate(-bounds.width() / 2, -bounds.height() / 2);

    setTransform(baseTransform);

    updatePosition(ant.logicalPosition, ant.hasFood, ant.target);
    setZValue(3);
}

void AntItem::updatePosition(const QPointF& newPos, bool hasFood, const QPointF& targetPos)
{
    this->hasFood = hasFood;

    setPos(newPos);

    if (!targetPos.isNull())
    {
        rotateToTarget(targetPos);
    }
}

void AntItem::rotateToTarget(const QPointF& targetPos)
{
    QPointF currentCenter = pos();
    QPointF direction = targetPos;

    qreal angleRad = qAtan2(direction.y(), direction.x());
    qreal degrees = qRadiansToDegrees(angleRad) + 90;

    QRectF bounds = boundingRect();
    QTransform rotateTransform = QTransform();
    rotateTransform.scale(scaleFactor, scaleFactor);
    rotateTransform.rotate(degrees);
    rotateTransform.translate(-bounds.width() / 2, -bounds.height() / 2);

    setTransform(rotateTransform);    
}
