#pragma once

#include "Ant.hpp"
#include "FoodStorage.hpp"
#include "PheromoneMap.hpp"

class AntColonyModel
{
public:
    AntColonyModel();
    explicit AntColonyModel(int heigth, int weigth);
    explicit AntColonyModel(int size);

public:
    int getHeigth();
    int getWidth();

    void setAnts(const QVector<Ant>& ants);
    void addAnt(const Ant& ant);
    void removeAnt(int index);
    QVector<Ant>& getAnts();

    void setFoods(const QList<QPointF>& foods);
    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);
    const QList<QPointF>& getFoods() const;

    void addPheromone(const QPointF& pos, qreal strength);
    void evaporatePheromones();
    QPointF getDiractionByPheromones(const QPointF& pos) const;
    const PheromoneMap& getPheromoneMap();

    void reset();

private:
    int heigth;
    int width;

    QVector<Ant> ants;
    QList<QPointF> foods;
    PheromoneMap pheromoneMap;
};
