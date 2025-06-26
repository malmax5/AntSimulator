#pragma once

#include <QList>

#include <QPointF>

class FoodStorage
{
public:
    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);
    void clearFood();
    int foodCount();
    QList<QPointF> getFoods() const;
    QPointF getNearestFood(QPointF position, qreal maxDistance = 0.0);

private:
    QList<QPointF> foods;
};
