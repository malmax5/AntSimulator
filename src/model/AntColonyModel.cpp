#include "../../include/model/AntColonyModel.hpp"

#include <QDebug>
#include <QMutexLocker>

AntColonyModel::AntColonyModel()
    : nestPosition(0.5, 0.5)
{
    
}

void AntColonyModel::setAnts(const QVector<Ant*>& ants)
{
    QMutexLocker locker(&dataMutex);
    this->ants = ants;
}

void AntColonyModel::clearAnts()
{
    ants.clear();
}

void AntColonyModel::addAnt(Ant* ant)
{
    QMutexLocker locker(&dataMutex);
    ants.append(ant);
}

void AntColonyModel::removeAnt(int index)
{
    if (index < 0 || index >= ants.size())
    {
        return;
    }

    QMutexLocker locker(&dataMutex);
    ants.removeAt(index);
}

Ant* AntColonyModel::getAnt(int index)
{
    if (index < 0 || index >= ants.size())
    {
        return nullptr;
    }

    QMutexLocker locker(&dataMutex);
    return ants[index];
}

const QVector<Ant*>& AntColonyModel::getAnts() const
{
    QMutexLocker locker(&dataMutex);
    return ants;
}

void AntColonyModel::setFoods(const FoodStorage& foods)
{
    QMutexLocker locker(&dataMutex);
    this->foods = foods;
}

void AntColonyModel::addFood(const QPointF& pos)
{
    QMutexLocker locker(&dataMutex);
    foods.addFood(pos);
}

void AntColonyModel::removeFood(const QPointF& pos)
{
    QMutexLocker locker(&dataMutex);
    foods.removeFood(pos);
}

FoodStorage& AntColonyModel::getFoodStorage()
{
    QMutexLocker locker(&dataMutex);
    return foods;
}

void AntColonyModel::setPheromones(PheromoneMap& pheromones)
{
    pheromoneMap = pheromones;
}

void AntColonyModel::addPheromone(const QPointF& pos, qreal strength)
{
    QMutexLocker locker(&dataMutex);
    pheromoneMap.addPheromone(pos, strength);
}

void AntColonyModel::evaporatePheromones()
{
    QMutexLocker locker(&dataMutex);
    pheromoneMap.evaporate();
}

QPointF AntColonyModel::getDiractionByPheromones(const QPointF& pos, qreal detectionRadius) const
{
    QMutexLocker locker(&dataMutex);
    return pheromoneMap.getDirection(pos, detectionRadius);
}

PheromoneMap& AntColonyModel::getPheromoneMap()
{
    QMutexLocker locker(&dataMutex);
    return pheromoneMap;
}

QPointF AntColonyModel::getNestPosition() const
{
    QMutexLocker locker(&dataMutex);
    return nestPosition;
}

void AntColonyModel::setNestPosition(const QPointF newPos)
{
    QMutexLocker locker(&dataMutex);
    nestPosition = newPos;
}

void AntColonyModel::reset()
{
    QMutexLocker locker(&dataMutex);
    ants.clear();
    foods.clear();
    pheromoneMap.clear();
}
