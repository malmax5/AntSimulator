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
    FoodStorage& getFoodStorage();

    void addPheromone(const QPointF& pos, qreal strength);
    void evaporatePheromones();
    QPointF getDiractionByPheromones(const QPointF& pos, qreal detectionRadius) const;
    PheromoneMap& getPheromoneMap();

    QPointF getNestPosition();

    void reset();

    mutable QMutex dataMutex;
    
private:
    QPointF nestPosition;
    QVector<Ant> ants;
    FoodStorage foods;
    PheromoneMap pheromoneMap;
};
