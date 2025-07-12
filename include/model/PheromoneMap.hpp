#pragma once

#include <QObject>

#include <QPointF>
#include <QSize>

#include <QMutex>
#include <QMutexLocker>

#include <QVector>
#include <QDataStream>

#include <cmath>
#include <algorithm>

class PheromonePoint : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY posChanged)
    Q_PROPERTY(qreal strength READ strength WRITE setStrength NOTIFY streangthChanged)
    Q_PROPERTY(qint64 timestamp READ timestamp WRITE setTimestamp NOTIFY timestampChanged)

public:
    explicit PheromonePoint(QObject* parent = nullptr);

    QPointF pos() const;
    qreal strength() const;
    qint64 timestamp() const;

    void setPos(const QPointF& pos);
    void setStrength(qreal strength);
    void setTimestamp(qint64 timestamp);

    friend QDataStream& operator<<(QDataStream& out, const PheromonePoint& point)
    {
        out << point.m_pos
            << point.m_strength
            << point.m_timestamp;
        
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, PheromonePoint& point)
    {
        in >> point.m_pos
           >> point.m_strength
           >> point.m_timestamp;
        
        return in;
    }

signals:
    void posChanged(const QPointF& pos);
    void streangthChanged(qreal strength);
    void timestampChanged(qint64 timestamp);

public:
    mutable QMutex m_mutex;
private:
    QPointF m_pos;
    qreal m_strength;
    qint64 m_timestamp;
};

class PheromoneMap
{
public:
    void addPheromone(const QPointF& worldPos, qreal strength);
    void evaporate();
    QPointF getDirection(const QPointF& worldPos, qreal radiusDetection) const;
    const QList<PheromonePoint*>& getPheromonePoints() const;
    void clear();

    friend QDataStream& operator<<(QDataStream& out, const PheromoneMap& pheromoneMap)
    {
        out << pheromoneMap.points.size();
        for (const auto& point : pheromoneMap.points)
        {
            out << *point;
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, PheromoneMap& pheromoneMap)
    {
        int pointsSize;
        in >> pointsSize;

        for (int i = 0; i < pointsSize; i++)
        {
            PheromonePoint* point = new PheromonePoint;
            in >> *point;
            pheromoneMap.points.append(point);
        }

        return in;
    }

private:
    QVector<PheromonePoint*> points;
    qreal evaporateRate = 0.9;
    qreal maxDistance = 0.003;
};
