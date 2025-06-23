#include "../include/AntSimulator.hpp"

#include <cmath>

#include <QThread>
#include <QRandomGenerator>

AntSimulator::AntSimulator(QObject* parent)
    : QObject(parent), pheromoneMap(200, 200)
{
    nestPosition = QPointF(100, 100);
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
            emit updateData(ants);
            emit updateActivity(foodPositions.size());
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
    foodPositions.clear();
    pheromoneMap = PheromoneMap(200, 200);
    emit updateData(ants);
    emit updateActivity(foodPositions.size());
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

    for (int i = 0; i <= ants.size(); i++)
    {
        Ant ant;
        ant.position = nestPosition + QPointF(QRandomGenerator::global()->bounded(5, -5),
                                              QRandomGenerator::global()->bounded(5, -5));
        ant.target = getRandomDiraction();
        ant.hasFood = false;
        ants.append(ant);
    }
}

void AntSimulator::moveAnts()
{
    for (int i = 0; i < ants.size(); i++)
    {
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
    for (int i = 0; i < foodPositions.size(); i++)
    {
        if (QPointF::dotProduct(ant.position - foodPositions[i], ant.position - foodPositions[i]) < detectionRadius * detectionRadius)
        {
            ant.target = foodPositions[i] - ant.position;
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
