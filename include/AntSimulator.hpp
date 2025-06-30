#pragma once

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QTimer>
#include <QMutex>

#include "model/Ant.hpp"
#include "model/FoodStorage.hpp"
#include "model/PheromoneMap.hpp"

class AntSimulator : public QObject
{
    Q_OBJECT

public:
    explicit AntSimulator(QObject* parent = nullptr);

public slots:

    void run();
    void start();
    void resume();
    void pause();
    void reset();
    void stop();

    void setAntCount(int count);
    void setSimulationSpeed(qreal speed);

    void addFood(const QPointF& pos);

signals:
    void updateData(const QVector<Ant>& ants, const FoodStorage& foodStorage, const PheromoneMap& pheromoneMap);
    void updateCollectedFood(int count);
    void collectedFood(QPointF foodPosition);

private:
    void initializeAnts();
    void moveAnts();
    bool searchForFood(Ant& ant);
    void returnToNest(Ant& ant);
    void evaporatePheromones();
    QPointF getRandomDiraction() const;

private:
    int antCount = 10;
    int foodCollected = 0;
    qreal simulationSpeed = 1.0;
    qreal moveStep = 1.0;
    qreal detectionRadius = 20.0;

    bool isRunning = false;
    bool isPaused = false;

    QVector<Ant> ants;
    PheromoneMap pheromoneMap;
    FoodStorage foodStorage;
    QPointF nestPosition;

    QTimer* runTimer;
    QMutex mutex;
};
