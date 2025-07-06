#pragma once

#include <QSize>

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
    Ant& getAnt(int index);
    QVector<Ant>& getAnts();

    void setFoods(const FoodStorage& foods);
    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);
    const FoodStorage& getFoodStorage() const;

    void addPheromone(const QPointF& pos, qreal strength);
    void evaporatePheromones();
    QPointF getDiractionByPheromones(const QPointF& pos) const;
    const PheromoneMap& getPheromoneMap();

    QPointF getNestPosition();

    void resize(const QSize& size);
    
    void reset();

private:
    int heigth;
    int width;

    QPointF nestPosition;
    QVector<Ant> ants;
    FoodStorage foods;
    PheromoneMap pheromoneMap;
};
