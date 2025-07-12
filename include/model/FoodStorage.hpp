#pragma once

#include <QVector>
#include <QPointF>
#include <QDataStream>

#include <QDebug>

class FoodStorage
{
public:
    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);
    void clear();
    int foodCount();
    const QVector<QPointF>& getFoods() const;
    QPointF getNearestFood(QPointF position, qreal maxDistance = 0.0) const;

    friend QDataStream& operator<<(QDataStream& out, const FoodStorage& foodStorage)
    {
        int foodStorageSize = foodStorage.foods.size();
        out << foodStorageSize;
        for (const auto& food : foodStorage.foods)
        {
            qDebug() << "<< Food";
            out << food;
        }
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, FoodStorage& foodStorage)
    {
        int foodsSize;
        in >> foodsSize;
        for (int i = 0; i < foodsSize; i++)
        {
            QPointF food;
            in >> food;
            foodStorage.foods.append(food);
        }
        return in;
    }

private:
    QVector<QPointF> foods;
};
