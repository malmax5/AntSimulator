#include "../include/AntSimulator.hpp"

#include <cmath>

#include <QThread>
#include <QRandomGenerator>

#include <QDebug>

AntSimulator::AntSimulator(AntColonyModel* antColonyModel, QObject* parent)
    : QObject(parent), antColonyModel(antColonyModel)
{
    nestPosition = QPointF(200, 200); // heigth and width
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
        emit updateData();
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
        runTimer = nullptr;
    }

    antColonyModel->reset();

    emit updateData();
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
    antColonyModel->addFood(pos);
    emit updateData();
}

void AntSimulator::initializeAnts()
{   
    antColonyModel->getAnts().clear();
    antColonyModel->getAnts().reserve(antCount);

    for (int i = 0; i < antCount; i++)
    {
        Ant ant;

        int newX = nestPosition.x() + QRandomGenerator::global()->bounded(-5, 5);
        int newY = nestPosition.y() + QRandomGenerator::global()->bounded(-5, 5);

        if (newX < 0 || newY < 0 || newX > antColonyModel->getWidth() || newY > antColonyModel->getHeigth())
        {
            continue;
        }

        ant.position = nestPosition + QPointF(QRandomGenerator::global()->bounded(-5, 5),
                                              QRandomGenerator::global()->bounded(-5, 5));
        ant.target = getRandomDiraction();
        ant.hasFood = false;
        antColonyModel->addAnt(ant);
    }

    emit updateData();
}

void AntSimulator::moveAnts()
{
    for (int i = 0; i < antColonyModel->getAnts().size(); i++)
    {
        antColonyModel->getAnts()[i].target = antColonyModel->getDiractionByPheromones(antColonyModel->getAnts()[i].position);

        if (antColonyModel->getAnts()[i].hasFood)
        {
            returnToNest(antColonyModel->getAnts()[i]);
        }
        else if (searchForFood(antColonyModel->getAnts()[i]))
        {
            
        }
        else if (antColonyModel->getAnts()[i].target.isNull()) // if target null -> get random
        {
            antColonyModel->getAnts()[i].target = getRandomDiraction();
        }
        else // if not null -> dir from pheromone map
        {
            antColonyModel->addPheromone(antColonyModel->getAnts()[i].position, 1.0);
        }

        antColonyModel->getAnts()[i].position += antColonyModel->getAnts()[i].target * moveStep;
    }
}

bool AntSimulator::searchForFood(Ant& ant)
{
    //
    QPointF nearestFood;
    qreal minDistance = std::numeric_limits<qreal>::max();
    int maxDistance = 20;
    for (auto& foodPosition : antColonyModel->getFoods())
    {
        qreal distSq = QPointF::dotProduct(ant.position - foodPosition, ant.position - foodPosition);

        if ((maxDistance <= 0 || distSq < maxDistance * maxDistance) && distSq < minDistance)
        {
            minDistance = distSq;
            nearestFood = foodPosition;
        }
    }
    //
    if (!nearestFood.isNull())
    {
        ant.target = nearestFood - ant.position;
        antColonyModel->addPheromone(ant.position, 2.0);

        if (QPointF::dotProduct(ant.target, ant.target) < 1.0)
        {
            ant.hasFood = true;
            antColonyModel->removeFood(nearestFood);
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
    antColonyModel->evaporatePheromones();
}

QPointF AntSimulator::getRandomDiraction() const
{
    qreal angel = QRandomGenerator::global()->bounded(2 * M_PI);
    return QPointF(std::cos(angel), std::sin(angel));
}
