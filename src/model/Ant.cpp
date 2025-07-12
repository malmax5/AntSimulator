#include "../../include/model/Ant.hpp"

Ant::Ant(QObject* parent)
    : Ant(-1, parent)
{

}

Ant::Ant(int id, QObject* parent)
    : QObject(parent)
{
    m_id = id;
}
    
QPointF Ant::logicalPosition() const
{
    QMutexLocker locker(&m_mutex);
    return m_logicalPosition;
}

QPointF Ant::target() const
{
    QMutexLocker locker(&m_mutex);
    return m_logicalPosition;
}

bool Ant::hasFood() const
{
    QMutexLocker locker(&m_mutex);
    return m_hasFood;
}

qreal Ant::pheromoneStrength() const
{
    QMutexLocker locker(&m_mutex);
    return m_pheromoneStrength;
}

int Ant::id() const
{
    QMutexLocker locker(&m_mutex);
    return m_id;
}


void Ant::setLogicalPosition(const QPointF& pos)
{
    QMutexLocker locker(&m_mutex);
    m_logicalPosition = pos;

    emit positionChanged();
}

void Ant::setTarget(const QPointF& newTarget)
{
    QMutexLocker locker(&m_mutex);
    m_target = newTarget;

    emit targetChanged();
}

void Ant::setHasFood(bool hasFood)
{
    QMutexLocker locker(&m_mutex);
    hasFood = hasFood;

    emit hasFoodChanged();
}

void Ant::setPheromoneStrength(qreal strength)
{
    QMutexLocker locker(&m_mutex);
    m_pheromoneStrength = strength;

    emit pheromoneStrengthChanged();
}

