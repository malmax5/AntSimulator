#include "../../include/model/AntColonyModel.hpp"

AntColonyModel::AntColonyModel()
    : heigth(400), width(400), pheromoneMap(400, 400)
{

}

AntColonyModel::AntColonyModel(int heigth, int width)
    : heigth(heigth), width(width), pheromoneMap(heigth, width)
{

}

AntColonyModel::AntColonyModel(int size)
    : AntColonyModel(size, size)
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

QVector<Ant>& AntColonyModel::getAnts()
{
    return ants;
}

void AntColonyModel::setFoods(const QList<QPointF>& foods)
{
    this->foods = foods;
}

void AntColonyModel::addFood(const QPointF& pos)
{
    foods.append(pos);
}

void AntColonyModel::removeFood(const QPointF& pos)
{
    foods.removeOne(pos);
}

const QList<QPointF>& AntColonyModel::getFoods() const
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

int AntColonyModel::getHeigth()
{
    return heigth;
}

int AntColonyModel::getWidth()
{
    return width;
}

void AntColonyModel::reset()
{
    ants.clear();
    foods.clear();
    pheromoneMap.clear();
}
