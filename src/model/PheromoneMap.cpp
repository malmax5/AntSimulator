#include "../../include/model/PheromoneMap.hpp"

#include <QDebug>
#include <QDateTime>

PheromonePoint::PheromonePoint(QObject* parent)
    : QObject(parent)
{

}

QPointF PheromonePoint::pos() const
{
    QMutexLocker locker(&m_mutex);
    return m_pos;
}

qreal PheromonePoint::strength() const
{
    QMutexLocker locker(&m_mutex);
    return m_strength;
}

qint64 PheromonePoint::timestamp() const
{
    QMutexLocker locker(&m_mutex);
    return m_timestamp;
}

void PheromonePoint::setPos(const QPointF& pos)
{
    QMutexLocker locker(&m_mutex);
    m_pos = pos;

    emit posChanged(pos);
}

void PheromonePoint::setStrength(qreal strength)
{
    QMutexLocker locker(&m_mutex);
    m_strength = strength;

    emit streangthChanged(strength);
}

void PheromonePoint::setTimestamp(qint64 timestamp)
{
    QMutexLocker locker(&m_mutex);
    m_timestamp = timestamp;

    emit timestampChanged(timestamp);
}

void PheromoneMap::addPheromone(const QPointF& worldPos, qreal strength)
{
    bool merged = false;

    for (auto& point : points)
    {
        qreal dx = point->pos().x() - worldPos.x();
        qreal dy = point->pos().y() - worldPos.y();
        qreal dist = std::sqrt(dx * dx + dy * dy);

        if (dist < maxDistance)
        {
            point->setStrength(qMax(strength, point->strength()));
            point->setTimestamp(QDateTime::currentMSecsSinceEpoch());
            merged = true;
            break;
        }
    }

    if (!merged)
    {
        PheromonePoint* newPoint = new PheromonePoint;
        newPoint->setPos(worldPos);
        newPoint->setStrength(strength);
        newPoint->setTimestamp(QDateTime::currentMSecsSinceEpoch());

        points.append(newPoint);
    }
}

void PheromoneMap::evaporate()
{
    for (auto it = points.begin(); it != points.end();)
    {
        (*it)->setStrength((*it)->strength() * evaporateRate);

        if ((*it)->strength() < 0.01)
        {
            it = points.erase(it);
        }
        else
        {
            it++;
        }
    }
}

QPointF PheromoneMap::getDirection(const QPointF& worldPos, qreal radiusDetection) const
{
    QPointF totalForce(0, 0);
    qreal totalStrength = 0;

    for (const auto& point : points)
    {
        qreal dx = point->pos().x() - worldPos.x();
        qreal dy = point->pos().y() - worldPos.y();
        qreal dist = std::sqrt(dx * dx + dy * dy);

        if (dist > radiusDetection)
        {
            continue;
        }

        qreal influence = point->strength() / (dist * dist);
        totalForce.rx() += dx * influence;
        totalForce.ry() += dy * influence;
        totalStrength += influence;
    }

    if (totalStrength > 0)
    {
        return totalForce / std::sqrt(QPointF::dotProduct(totalForce, totalForce));
    }

    return QPointF();
}

const QList<PheromonePoint*>& PheromoneMap::getPheromonePoints() const
{
    return points;
}

void PheromoneMap::clear()
{
    points.clear();
}
