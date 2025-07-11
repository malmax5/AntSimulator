#pragma once

#include <QGraphicsSvgItem>
#include <QColor>
#include <QPen>
#include <QPainter>

#include "../model/Ant.hpp"

class AntItem : public QGraphicsSvgItem
{
public:
    explicit AntItem(const Ant& ant, QGraphicsSvgItem* parent = nullptr);

    void updatePosition(const QPointF& newPos, bool hasFood, const QPointF& targetPos);

    void rotateToTarget(const QPointF& targetPos);

private:
    qreal scaleFactor = 0.00002;

    bool hasFood = false;
    QColor baseColor = Qt::black;
};

