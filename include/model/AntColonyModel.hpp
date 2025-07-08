#pragma once

#include <QSize>
#include <QMutex>

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
    void setAnts(const QVector<Ant>& ants);
    void addAnt(const Ant& ant);
    void removeAnt(int index);
    Ant* getAnt(int index);
    QVector<Ant>& getAnts();

    void setFoods(const FoodStorage& foods);
    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);
    const FoodStorage& getFoodStorage() const;

    void addPheromone(const QPointF& pos, qreal strength);
    void evaporatePheromones();
    QPointF getDiractionByPheromones(const QPointF& pos, qreal detectionRadius) const;
    const PheromoneMap& getPheromoneMap();

    QPointF getNestPosition();

    void reset();

private:
    mutable QMutex dataMutex;
    QPointF nestPosition;
    QVector<Ant> ants;
    FoodStorage foods;
    PheromoneMap pheromoneMap;
};
