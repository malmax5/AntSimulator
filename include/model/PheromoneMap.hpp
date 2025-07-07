#pragma once

#include <QPointF>
#include <QSize>

#include <QVector>

#include <cmath>
#include <algorithm>

struct PheromonePoint
{
    QPointF pos;
    qreal strength;
    qreal timestamp;
};

class PheromoneMap
{
public:
    void addPheromone(const QPointF& worldPos, qreal strength);
    void evaporate();
    QPointF getDirection(const QPointF& pos) const;
    void clear();

private:
    QList<PheromonePoint> points;
    qreal evaporateRate = 0.95;
    qreal maxDistance = 0.1;
};
