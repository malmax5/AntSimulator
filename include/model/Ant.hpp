#pragma once

#include <QObject>
#include <QPointF>
#include <QDataStream>
#include <QMutex>
#include <QMutexLocker>

#include <QDebug>

class Ant : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPointF logicalPosition READ logicalPosition WRITE setLogicalPosition NOTIFY positionChanged)
    Q_PROPERTY(QPointF target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(bool hasFood READ hasFood WRITE setHasFood NOTIFY hasFoodChanged)
    Q_PROPERTY(qreal pheromoneStrength READ pheromoneStrength WRITE setPheromoneStrength NOTIFY pheromoneStrengthChanged)

public:
    explicit Ant(QObject* parent = nullptr);
    explicit Ant(int id, QObject* parent = nullptr);

    QPointF logicalPosition() const;
    QPointF target() const;
    bool hasFood() const;
    qreal pheromoneStrength() const;
    int id() const;

    void setLogicalPosition(const QPointF& pos);
    void setTarget(const QPointF& newTarget);
    void setHasFood(bool hasFood);
    void setPheromoneStrength(qreal strength);

    friend QDataStream& operator<<(QDataStream& out, const Ant& ant)
    {
        QMutexLocker locker(&ant.m_mutex);
        out << ant.m_logicalPosition
            << ant.m_target
            << ant.m_hasFood
            << ant.m_pheromoneStrength;
        
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Ant& ant)
    {
        QMutexLocker locker(&ant.m_mutex);
        in >> ant.m_logicalPosition
           >> ant.m_target
           >> ant.m_hasFood
           >> ant.m_pheromoneStrength;
        
        return in;
    }

signals:
    void positionChanged();
    void targetChanged();
    void hasFoodChanged();
    void pheromoneStrengthChanged();

public:
    mutable QMutex m_mutex;

private:
    QPointF m_logicalPosition;
    QPointF m_target;
    bool m_hasFood = false;
    qreal m_pheromoneStrength = 1.0;
    int m_id;
};
