#pragma once

#include <QPointF>

struct Ant
{
    QPointF position;
    QPointF target;
    bool hasFood;
    qreal pheromoneStrength;
};
