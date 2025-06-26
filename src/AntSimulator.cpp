#include "../include/AntSimulator.hpp"

#include <cmath>

#include <QThread>
#include <QRandomGenerator>

#include <QDebug>

AntSimulator::AntSimulator(QObject* parent)
    : QObject(parent), pheromoneMap(400, 400)
{
    nestPosition = QPointF(200, 200);
}

void AntSimulator::run()
{
    if (isRunning)
    {
        return;
    }

    isRunning = true;
    isPaused = false;

    initializeAnts();

    while (isRunning)
    {
        if (!isPaused)
        {
            moveAnts();
            evaporatePheromones();
            emit updateData(ants);
            emit updateActivity(foodStorage.foodCount());
        }

        QThread::msleep(static_cast<unsigned long>(100 / simulationSpeed));
    }
}

void AntSimulator::resume()
{
    isPaused = false;
}

void AntSimulator::pause()
{
    isPaused = true;
}

void AntSimulator::reset()
{
    ants.clear();
    foodStorage.clearFood();
    pheromoneMap = PheromoneMap(400, 400);
    emit updateData(ants);
    emit updateActivity(foodStorage.foodCount());
}

void AntSimulator::stop()
{
    isRunning = false;
}

void AntSimulator::setAntCount(int count)
{
    antCount = count;
    initializeAnts();
}

void AntSimulator::setSimulationSpeed(qreal speed)
{
    simulationSpeed = speed;
}

void AntSimulator::initializeAnts()
{
    
    ants.clear();
    ants.reserve(antCount);

    for (int i = 0; i < antCount; i++)
    {
        Ant ant;

        int newX = nestPosition.x() + QRandomGenerator::global()->bounded(-5, 5);
        int newY = nestPosition.y() + QRandomGenerator::global()->bounded(-5, 5);

        qDebug() << nestPosition.x() << " " << nestPosition.y();

        if (newX < 0 || newY < 0 || newX > 400 || newY > 400)
        {
            continue;
        }

        ant.position = nestPosition + QPointF(QRandomGenerator::global()->bounded(-5, 5),
                                              QRandomGenerator::global()->bounded(-5, 5));
        ant.target = getRandomDiraction();
        ant.hasFood = false;
        ants.append(ant);
    }

    emit updateData(ants);
}

void AntSimulator::moveAnts()
{
    for (int i = 0; i < ants.size(); i++)
    {
        ants[i].target = getRandomDiraction();

        ants[i].position += ants[i].target * moveStep;

        if (ants[i].hasFood)
        {
            returnToNest(ants[i]);
        }
        else
        {
            searchForFood(ants[i]);
        }
    }
}

void AntSimulator::searchForFood(Ant& ant)
{
    for (int i = 0; i < foodStorage.foodCount(); i++)
    {
        QPointF nearestFood = foodStorage.getNearestFood(ant.position, detectionRadius);
        if (!nearestFood.isNull())
        {
            ant.hasFood = true;
            foodStorage.removeFood(nearestFood);

            ant.target = nearestFood - ant.position;
            ant.target /= detectionRadius;
            pheromoneMap.addPheromone(ant.position, 1.0);
            return;
        }
    }

    ant.target = getRandomDiraction();
}

void AntSimulator::returnToNest(Ant& ant)
{
    ant.target = nestPosition - ant.position;
    qreal distance = std::sqrt(QPointF::dotProduct(ant.target, ant.target));

    if (distance < 2.0)
    {
        ant.hasFood = false;
        pheromoneMap.addPheromone(ant.position, 2.0);
    }
}

void AntSimulator::evaporatePheromones()
{
    pheromoneMap.evaporate();
}

QPointF AntSimulator::getRandomDiraction() const
{
    qreal angel = QRandomGenerator::global()->bounded(2 * M_PI);
    return QPointF(std::cos(angel), std::sin(angel));
}
