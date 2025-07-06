#pragma once

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QTimer>
#include <QMutex>

#include "model/AntColonyModel.hpp"

class AntSimulator : public QObject
{
    Q_OBJECT

public:
    explicit AntSimulator(AntColonyModel* antColonyModel, QObject* parent = nullptr);

public slots:
    void run();
    void start();
    void resume();
    void pause();
    void reset();
    void stop();

    void setAntCount(int count);
    void setSimulationSpeed(qreal speed);

signals:
    void updateCollectedFood(int count);
    void updateData();

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
    qreal moveStep = 0.01;
    qreal detectionRadius = 20.0;

    bool isRunning = false;
    bool isPaused = false;

    AntColonyModel* antColonyModel;

    QTimer* runTimer;
    QMutex mutex;
};
