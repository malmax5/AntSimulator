#include "../../include/model/AntColonyModel.hpp"

#include <QDebug>

AntColonyModel::AntColonyModel()
    : nestPosition(0.5, 0.5) // !
{

}

void AntColonyModel::setAnts(const QVector<Ant>& ants)
{
    this->ants = ants;
}

void AntColonyModel::addAnt(const Ant& ant)
{
    ants.append(ant);
}

void AntColonyModel::removeAnt(int index)
{
    ants.removeAt(index);
}

Ant& AntColonyModel::getAnt(int index)
{
    return ants[index];
}

QVector<Ant>& AntColonyModel::getAnts()
{
    return ants;
}

void AntColonyModel::setFoods(const FoodStorage& foods)
{
    this->foods = foods;
}

void AntColonyModel::addFood(const QPointF& pos)
{
    foods.addFood(pos);
}

void AntColonyModel::removeFood(const QPointF& pos)
{
    foods.removeFood(pos);
}

const FoodStorage& AntColonyModel::getFoodStorage() const
{
    return foods;
}

void AntColonyModel::addPheromone(const QPointF& pos, qreal strength)
{
    pheromoneMap.addPheromone(pos, strength);
}

void AntColonyModel::evaporatePheromones()
{
    pheromoneMap.evaporate();
}

QPointF AntColonyModel::getDiractionByPheromones(const QPointF& pos) const
{
    return pheromoneMap.getDirection(pos);
}

const PheromoneMap& AntColonyModel::getPheromoneMap()
{
    return pheromoneMap;
}

QPointF AntColonyModel::getNestPosition()
{
    return nestPosition;
}

void AntColonyModel::reset()
{
    ants.clear();
    foods.clear();
    pheromoneMap.clear();
}
