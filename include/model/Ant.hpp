#pragma once

#include <QPointF>
#include <QDataStream>

struct Ant
{
    QPointF logicalPosition;
    QPointF target;
    bool hasFood;
    qreal pheromoneStrength;
    int id;

    friend QDataStream& operator<<(QDataStream& out, const Ant& ant)
    {
        out << ant.logicalPosition
            << ant.target
            << ant.hasFood
            << ant.pheromoneStrength
            << ant.id;
        
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Ant& ant)
    {
        in >> ant.logicalPosition
           >> ant.target
           >> ant.hasFood
           >> ant.pheromoneStrength
           >> ant.id;
        
        return in;
    }
};
