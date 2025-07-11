#pragma once

#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QPointF>

class FoodItem : public QGraphicsSvgItem
{
public:
    explicit FoodItem(const QPointF& pos, QGraphicsSvgItem* parent = nullptr);

private:
    qreal scaleFactor = 0.00002;
};
