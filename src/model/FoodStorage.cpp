#include "../../include/model/FoodStorage.hpp"

void FoodStorage::addFood(const QPointF& pos)
{
    foods.append(pos);
}

void FoodStorage::removeFood(const QPointF& pos)
{
    foods.removeOne(pos);
}

QList<QPointF> FoodStorage::getFoods() const
{
    return foods;
}
