#pragma once

#include <QList>

#include <QPointF>

class FoodStorage
{
public:
    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);
    QList<QPointF> getFoods() const;

private:
    QList<QPointF> foods;
};
