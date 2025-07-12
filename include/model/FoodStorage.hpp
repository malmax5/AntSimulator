#pragma once

#include <QList>
#include <QPointF>
#include <QDataStream>

class FoodStorage
{
public:
    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);
    void clear();
    int foodCount();
    const QList<QPointF>& getFoods() const;
    QPointF getNearestFood(QPointF position, qreal maxDistance = 0.0) const;

    friend QDataStream& operator<<(QDataStream& out, const FoodStorage& foodStorage)
    {
        out << foodStorage.foods;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, FoodStorage& foodStorage)
    {
        in >> foodStorage.foods;
        return in;
    }

private:
    QList<QPointF> foods;
};
