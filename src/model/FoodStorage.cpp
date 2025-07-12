#include "../../include/model/FoodStorage.hpp"

#include <cmath>

#include <QDebug>

void FoodStorage::addFood(const QPointF& pos)
{
    foods.append(pos);
}

void FoodStorage::removeFood(const QPointF& pos)
{
    foods.removeOne(pos);
}

void FoodStorage::clear()
{
    foods.clear();
}

int FoodStorage::foodCount()
{
    return foods.size();
}

QList<QPointF>& FoodStorage::getFoods()
{
    return foods;
}

QPointF FoodStorage::getNearestFood(QPointF position, qreal maxDistance) const
{
    QPointF nearestFood;
    qreal minDistance = std::numeric_limits<qreal>::max();
    for (auto& foodPosition : foods)
    {
        qreal distSq = QPointF::dotProduct(position - foodPosition, position - foodPosition);

        if ((maxDistance <= 0 || distSq < maxDistance * maxDistance) && distSq < minDistance)
        {
            minDistance = distSq;
            nearestFood = foodPosition;
        }
    }

    return nearestFood;
}
