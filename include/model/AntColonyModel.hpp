#pragma once

#include "Ant.hpp"
#include "FoodStorage.hpp"
#include "PheromoneMap.hpp"

class AntColonyModel
{
public:
    void addAnt(const Ant& ant);
    void removeAnt(int index);
    QVector<Ant>& getAnts();

    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);
    const QList<QPointF>& getFoods() const;

    void addPheromone(const QPointF& pos, qreal strength);
    void evaporatePheromones();
    QPointF getDiractionByPheromones();

private:
    QVector<Ant> ants;
    QList<QPointF> foods;
    PheromoneMap pheromoneMap;
};
