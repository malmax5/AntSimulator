#pragma once

#include <QPointF>

struct Ant
{
    QPointF logicalPosition;
    QPointF target;
    bool hasFood;
    qreal pheromoneStrength;
};
