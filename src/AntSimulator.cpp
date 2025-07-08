#include "../include/AntSimulator.hpp"

#include <cmath>

#include <QThread>
#include <QRandomGenerator>

#include <QDebug>

AntSimulator::AntSimulator(AntColonyModel* antColonyModel, QObject* parent)
    : QObject(parent), antColonyModel(antColonyModel)
{

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
}

void AntSimulator::setSimulationSpeed(qreal speed)
{
    simulationSpeed = speed;
}

void AntSimulator::initializeAnts()
{   
    antColonyModel->getAnts().clear();
    antColonyModel->getAnts().reserve(antCount);

    for (int i = 0; i < antCount; i++)
    {
        Ant ant;

        qreal newX = antColonyModel->getNestPosition().x() + (QRandomGenerator::global()->generateDouble() * 2 - 1) * 0.001;
        qreal newY = antColonyModel->getNestPosition().y() + (QRandomGenerator::global()->generateDouble() * 2 - 1) * 0.001;

        newX = qBound(0.0, newX, 1.0);
        newY = qBound(0.0, newY, 1.0);

        ant.logicalPosition = QPointF(newX, newY);

        ant.hasFood = false;
        antColonyModel->addAnt(ant);
    }

    emit updateData();
}

void AntSimulator::moveAnts()
{
    for (int i = 0; i < antColonyModel->getAnts().size(); i++)
    {
        Ant* currAnt = antColonyModel->getAnt(i);

        if (!currAnt)
        {
            continue;
        }

        QPointF dirByPheromones = antColonyModel->getDiractionByPheromones(currAnt->logicalPosition, detectionRadius);
        currAnt->target = dirByPheromones;

        if (currAnt->hasFood)
        {
            returnToNest(*currAnt);
        }
        else if (searchForFood(*currAnt))
        {

        }
        else if (currAnt->target.isNull()) // if target null -> get random
        {
            currAnt->target = getRandomDiraction();
        }
        else // if not null -> dir from pheromone map
        {

        }

        currAnt->logicalPosition += (currAnt->target / std::sqrt(QPointF::dotProduct(currAnt->target, currAnt->target))) * moveStep;
    }
}

bool AntSimulator::searchForFood(Ant& ant)
{
    QPointF nearestFood = antColonyModel->getFoodStorage().getNearestFood(ant.logicalPosition, detectionRadius); // !maxDistance

    if (!nearestFood.isNull())
    {
        ant.target = nearestFood - ant.logicalPosition;
        antColonyModel->addPheromone(ant.logicalPosition, 2.0);

        if (std::sqrt(QPointF::dotProduct(ant.target, ant.target)) < 0.003)
        {
            ant.hasFood = true;
            antColonyModel->removeFood(nearestFood);
            emit updateData();
        }

        return true;
    }

    return false;
}

void AntSimulator::returnToNest(Ant& ant)
{
    ant.target = antColonyModel->getNestPosition() - ant.logicalPosition;
    qreal distance = std::sqrt(QPointF::dotProduct(ant.target, ant.target));

    antColonyModel->addPheromone(ant.logicalPosition, 1.0);

    if (distance < 0.003)
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
