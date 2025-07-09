#pragma once

#include <QGraphicsEllipseItem>
#include <QColor>
#include <QPen>
#include <QPainter>

#include "../model/Ant.hpp"

class AntItem : public QGraphicsEllipseItem
{
public:
    explicit AntItem(const Ant& ant, QGraphicsItem* parent = nullptr);

    void updatePosition(const QPointF& newPos, bool hasFood);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    bool hasFood = false;
    QColor baseColor = Qt::black;
};

