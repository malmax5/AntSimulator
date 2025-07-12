#pragma once

#include <QPointF>
#include <QSize>

#include <QVector>
#include <QDataStream>

#include <cmath>
#include <algorithm>

struct PheromonePoint
{
    QPointF pos;
    qreal strength;
    qint64 timestamp;

    friend QDataStream& operator<<(QDataStream& out, const PheromonePoint& point)
    {
        out << point.pos
            << point.strength
            << point.timestamp;
        
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, PheromonePoint& point)
    {
        in >> point.pos
           >> point.strength
           >> point.timestamp;
        
        return in;
    }
};

class PheromoneMap
{
public:
    void addPheromone(const QPointF& worldPos, qreal strength);
    void evaporate();
    QPointF getDirection(const QPointF& worldPos, qreal radiusDetection) const;
    const QList<PheromonePoint>& getPheromonePoints() const;
    void clear();

    friend QDataStream& operator<<(QDataStream& out, const PheromoneMap& pheromoneMap)
    {
        out << pheromoneMap.points;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, PheromoneMap& pheromoneMap)
    {
        in >> pheromoneMap.points;
        return in;
    }

private:
    QList<PheromonePoint> points;
    qreal evaporateRate = 0.9;
    qreal maxDistance = 0.003;
};
