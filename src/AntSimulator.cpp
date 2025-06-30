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
    if (!isRunning)
    {
        return;
    }

    if (!isPaused)
    {
        moveAnts();
        evaporatePheromones();
        emit updateData(ants, foodStorage, pheromoneMap);
    }
}

void AntSimulator::start()
{
    if(isRunning)
    {
        return;
    }

    isRunning = true;
    isPaused = false;

    initializeAnts();

    runTimer = new QTimer(this);
    connect(runTimer, &QTimer::timeout, this, &AntSimulator::run);
    runTimer->start(100 / simulationSpeed);
}

void AntSimulator::resume()
{
    isPaused = false;
}

void AntSimulator::pause()
{
    if (isPaused)
    {
        return;
    }

    isPaused = true;
}

void AntSimulator::reset()
{
    stop();

    if (runTimer)
    {
        runTimer->stop();
        disconnect(runTimer, &QTimer::timeout, this, &AntSimulator::run);
        delete runTimer;
    }

    ants.clear();
    foodStorage.clearFood();
    pheromoneMap = PheromoneMap(400, 400);

    emit updateData(ants, foodStorage, pheromoneMap);
}

void AntSimulator::stop()
{
    if (!isRunning)
    {
        return;
    }

    isRunning = false;
    isPaused = false;
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

void AntSimulator::addFood(const QPointF& pos)
{
    foodStorage.addFood(pos);
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

    emit updateData(ants, foodStorage, pheromoneMap);
}

void AntSimulator::moveAnts()
{
    for (int i = 0; i < ants.size(); i++)
    {
        ants[i].target = pheromoneMap.getDirection(ants[i].position);

        if (ants[i].hasFood)
        {
            returnToNest(ants[i]);
        }
        else if (searchForFood(ants[i]))
        {
            
        }
        else if (ants[i].target.isNull()) // if target null -> get random
        {
            ants[i].target = getRandomDiraction();
        }
        else // if not null -> dir from pheromone map
        {
            pheromoneMap.addPheromone(ants[i].position, 1.0);
        }

        ants[i].position += ants[i].target * moveStep;
    }
}

bool AntSimulator::searchForFood(Ant& ant)
{
    QPointF nearestFood = foodStorage.getNearestFood(ant.position, detectionRadius);

    if (!nearestFood.isNull())
    {
        ant.target = nearestFood - ant.position;
        pheromoneMap.addPheromone(ant.position, 2.0);

        if (QPointF::dotProduct(ant.target, ant.target) < 1.0)
        {
            ant.hasFood = true;
            foodStorage.removeFood(nearestFood);
            
            emit collectedFood(nearestFood);
        }
        
        ant.target /= std::sqrt(QPointF::dotProduct(ant.target, ant.target));

        return true;
    }

    return false;
}

void AntSimulator::returnToNest(Ant& ant)
{
    ant.target = nestPosition - ant.position;
    qreal distance = std::sqrt(QPointF::dotProduct(ant.target, ant.target));
    ant.target /= distance;

    if (distance < 1.0)
    {
        ant.hasFood = false;
        foodCollected += 1;

        emit updateCollectedFood(foodCollected);
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
