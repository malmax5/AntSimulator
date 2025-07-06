#pragma once

#include <QPointF>
#include <QSize>

#include <QVector>

#include <cmath>
#include <algorithm>

class PheromoneMap
{
public:
    explicit PheromoneMap(int width = 100, int height = 100);

    void addPheromone(const QPointF& pos, qreal strength);
    void evaporate();
    QPointF getDirection(const QPointF& pos) const;
    qreal getValue(int x, int y) const;
    int getWidth();
    int getHeight();
    
    void clear();

private:
    qreal evaporateRate = 0.95;

    int width;
    int height;
    QVector<QVector<qreal>> map;

    inline int toIndexX(qreal x) const;
    inline int toIndexY(qreal y) const;
    inline bool isValid(int x, int y) const;
};
