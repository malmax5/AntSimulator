#include "../include/AntSimulator.hpp"

#include <cmath>

#include <QThread>
#include <QRandomGenerator>

#include <QDebug>

AntSimulator::AntSimulator(AntColonyModel* antColonyModel, QObject* parent)
    : QObject(parent), antColonyModel(antColonyModel)
{
    
}

bool AntSimulator::isSimulationRunning() const
{
    return isRunning;
}

bool AntSimulator::isSimulationPaused() const
{
    return isPaused;
}

int AntSimulator::collectedFood() const
{
    return foodCollected;
}

qreal AntSimulator::getSimulationSpeed() const
{
    return simulationSpeed;
}

qreal AntSimulator::getAntCount() const
{
    return antCount;
}

void AntSimulator::setSimulationRunning(bool isRunning)
{
    this->isRunning = isRunning;
}

void AntSimulator::setSimulationPaused(bool isPaused)
{
    this->isPaused = isPaused;
}

void AntSimulator::setCollectedFood(int collectedFood)
{
    emit updateCollectedFood(foodCollected);
    this->foodCollected = collectedFood;
}

void AntSimulator::setGetSimulationSpeed(qreal simulationSpeed)
{
    this->simulationSpeed = simulationSpeed;
}

void AntSimulator::setGetAntCount(int antCount)
{
    this->antCount = antCount;
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
    initializeTimer();
}

void AntSimulator::resume()
{
    if (!isRunning || !isPaused)
    {
        return;
    }

    updateTimer();
    isPaused = false;
}

void AntSimulator::pause()
{
    if (!isRunning)
    {
        return;
    }

    if (isPaused)
    {
        return;
    }

    runTimer->stop();
    isPaused = true;
}

void AntSimulator::reset()
{
    stop();

    deleteTimer();

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
    updateTimer();
}

void AntSimulator::restore()
{
    if (isRunning)
    {
        if (!runTimer)
        {
            initializeTimer();
        }
        if (isPaused)
        {
            runTimer->stop();
        }
    }
}

void AntSimulator::initializeTimer()
{
    if (!runTimer)
    {
        runTimer = new QTimer(this);
        connect(runTimer, &QTimer::timeout, this, &AntSimulator::run);
        runTimer->start(100 / simulationSpeed);
    }
}

void AntSimulator::updateTimer()
{
    if (runTimer)
    {
        runTimer->stop();
        runTimer->start(100 / simulationSpeed);
    }
}

void AntSimulator::deleteTimer()
{
    if (runTimer)
    {
        runTimer->stop();
        disconnect(runTimer, &QTimer::timeout, this, &AntSimulator::run);
        runTimer->deleteLater();
        runTimer = nullptr;
    }
}

void AntSimulator::initializeAnts()
{   
    antColonyModel->clearAnts();

    for (int i = 0; i < antCount; i++)
    {
        Ant* ant = new Ant(i);

        qreal newX = antColonyModel->getNestPosition().x() + (QRandomGenerator::global()->generateDouble() * 2 - 1) * 0.001;
        qreal newY = antColonyModel->getNestPosition().y() + (QRandomGenerator::global()->generateDouble() * 2 - 1) * 0.001;

        newX = qBound(0.0, newX, 1.0);
        newY = qBound(0.0, newY, 1.0);

        ant->setLogicalPosition(QPointF(newX, newY));

        ant->setHasFood(false);
        antColonyModel->addAnt(ant);
    }

    emit updateData();
}

void AntSimulator::moveAnts()
{
    for (int i = 0; i < antCount; i++)
    {
        Ant* currAnt = antColonyModel->getAnt(i);
        QPointF antPos = currAnt->logicalPosition();
        QPointF antTarget = QPointF();

        antTarget = antColonyModel->getDiractionByPheromones(antPos, detectionRadius);

        if (currAnt->hasFood())
        {
            QPointF nestTarget = returnToNest(currAnt);

            if (nestTarget.isNull())
            {
                currAnt->setHasFood(false);
                foodCollected += 1;
                emit updateCollectedFood(foodCollected);
            }
            else
            {
                antTarget = nestTarget;
                antColonyModel->addPheromone(antPos, 1.0);
            }
        }
        else if (QPointF searchTarget = searchForFood(currAnt); !searchTarget.isNull())
        {
            qreal distance = std::sqrt(QPointF::dotProduct(searchTarget - antPos, searchTarget - antPos));

            if (distance < 0.003)
            {
                currAnt->setHasFood(true);
                antColonyModel->removeFood(searchTarget);
            }
            else
            {
                antTarget = searchTarget;
                antColonyModel->addPheromone(antPos, 2.0);
            }
        }
        else if (antTarget.isNull()) // if target null -> get random
        {
            antTarget = getRandomDiraction();
        }
        else // if not null -> dir from pheromone map
        {
            
        }

        QPointF target = antTarget - antPos;
        currAnt->setTarget(target);

        currAnt->setLogicalPosition(antPos + (target / std::sqrt(QPointF::dotProduct(target, target))) * moveStep);
    }
}

QPointF AntSimulator::searchForFood(const Ant* ant) const
{
    QPointF nearestFood = antColonyModel->getFoodStorage().getNearestFood(ant->logicalPosition(), detectionRadius); // !maxDistance

    if (!nearestFood.isNull())
    {
        return nearestFood;
    }

    return QPointF();
}

QPointF AntSimulator::returnToNest(const Ant* ant) const
{
    QPointF toNest = antColonyModel->getNestPosition() - ant->logicalPosition();
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
