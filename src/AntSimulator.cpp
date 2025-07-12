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
        runTimer->deleteLater();
        runTimer = nullptr;
    }

    antColonyModel->reset();
    foodCollected = 0;

    emit updateData();
    emit updateCollectedFood(foodCollected);
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
        ant.id = i;

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
        QPointF antTarget = QPointF();

        if (!currAnt)
        {
            continue;
        }

        antTarget = antColonyModel->getDiractionByPheromones(currAnt->logicalPosition, detectionRadius);

        if (currAnt->hasFood)
        {
            QPointF nestTarget = returnToNest(*currAnt);

            if (nestTarget.isNull())
            {
                currAnt->hasFood = false;
                foodCollected += 1;
                emit updateCollectedFood(foodCollected);
            }
            else
            {
                antTarget = nestTarget;
                antColonyModel->addPheromone(currAnt->logicalPosition, 1.0);
            }
        }
        else if (QPointF searchTarget = searchForFood(*currAnt); !searchTarget.isNull())
        {
            qreal distance = std::sqrt(QPointF::dotProduct(searchTarget - currAnt->logicalPosition, searchTarget - currAnt->logicalPosition));

            if (distance < 0.003)
            {
                currAnt->hasFood = true;
                antColonyModel->removeFood(searchTarget);
            }
            else
            {
                antTarget = searchTarget;
                antColonyModel->addPheromone(currAnt->logicalPosition, 2.0);
            }
        }
        else if (antTarget.isNull()) // if target null -> get random
        {
            antTarget = getRandomDiraction();
        }
        else // if not null -> dir from pheromone map
        {
        }

        currAnt->target = antTarget - currAnt->logicalPosition;

        currAnt->logicalPosition += (currAnt->target / std::sqrt(QPointF::dotProduct(currAnt->target, currAnt->target))) * moveStep;
    }
}

QPointF AntSimulator::searchForFood(Ant& ant)
{
    QPointF nearestFood = antColonyModel->getFoodStorage().getNearestFood(ant.logicalPosition, detectionRadius); // !maxDistance

    if (!nearestFood.isNull())
    {
        return nearestFood;
    }

    return QPointF();
}

QPointF AntSimulator::returnToNest(Ant& ant)
{
    QPointF toNest = antColonyModel->getNestPosition() - ant.logicalPosition;
    qreal distance = std::sqrt(QPointF::dotProduct(toNest, toNest));

    if (distance < 0.003)
    {
        return QPointF();
    }

    return antColonyModel->getNestPosition();
}

void AntSimulator::evaporatePheromones()
{
    antColonyModel->evaporatePheromones();
}

QPointF AntSimulator::getRandomDiraction() const
{
    qreal angle = QRandomGenerator::global()->bounded(2 * M_PI);
    
    qreal dx = (std::cos(angle) + 1.0) / 2.0;
    qreal dy = (std::sin(angle) + 1.0) / 2.0;
    
    return QPointF(dx, dy);
}
