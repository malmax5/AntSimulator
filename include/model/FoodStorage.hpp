#pragma once

#include <QList>
#include <QPointF>

class FoodStorage
{
public:
    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);
    void clear();
    int foodCount();
    QList<QPointF>& getFoods();
    QPointF getNearestFood(QPointF position, qreal maxDistance = 0.0) const;

private:
    QList<QPointF> foods;
};
