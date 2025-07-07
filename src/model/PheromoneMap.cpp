#include "../../include/model/PheromoneMap.hpp"

#include <QDebug>
#include <QDateTime>

void PheromoneMap::addPheromone(const QPointF& worldPos, qreal strength)
{
    bool merged = false;

    for (auto& point : points)
    {
        qreal dx = point.pos.x() - worldPos.x();
        qreal dy = point.pos.y() - worldPos.y();
        qreal dist = std::sqrt(dx * dx + dy * dy);

        if (dist < maxDistance)
        {
            point.strength += strength;
            point.timestamp = QDateTime::currentMSecsSinceEpoch();
            merged = true;
            break;
        }
    }

    if (!merged)
    {
        points.append({worldPos, strength, QDateTime::currentMSecsSinceEpoch()});
    }
}

void PheromoneMap::evaporate()
{
    for (auto it = points.begin(); it != points.end();)
    {
        it->strength *= evaporateRate;

        if (it->strength < 0.01)
        {
            it = points.erase(it);
        }
        else
        {
            it++;
        }
    }
}

QPointF PheromoneMap::getDirection(const QPointF& worldPos) const
{
    QPointF totalForce(0, 0);
    qreal totalStrength = 0;

    for (const auto& point : points)
    {
        qreal dx = point.pos.x() - worldPos.x();
        qreal dy = point.pos.y() - worldPos.y();
        qreal dist = std::sqrt(dx * dx + dy * dy);

        if (dist < maxDistance)
        {
            qreal influence = point.strength / (dist * dist);
            totalForce.rx() += dx * influence;
            totalForce.ry() += dy * influence;
            totalStrength += influence;
        }
    }

    if (totalStrength > 0)
    {
        return totalForce / std::sqrt(QPointF::dotProduct(totalForce, totalForce));
    }

    return QPointF();
}

const QList<PheromonePoint>& PheromoneMap::getPheromonePoints() const
{
    return points;
}

void PheromoneMap::clear()
{
    points.clear();
}
