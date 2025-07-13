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

    bool isSimulationRunning() const;
    bool isSimulationPaused() const;
    int collectedFood() const;
    qreal getSimulationSpeed() const;
    qreal getAntCount() const;

    void setSimulationRunning(bool isRunning);
    void setSimulationPaused(bool isPaused);
    void setCollectedFood(int collectedFood);

public slots:
    void run();
    void start();
    void resume();
    void pause();
    void reset();
    void stop();
    void restore();

    void setAntCount(int count);
    void setSimulationSpeed(qreal speed);

signals:
    void updateCollectedFood(int count);
    void updateData();

private:
    void initializeTimer();
    void updateTimer();
    void deleteTimer();
    void initializeAnts();
    void moveAnts();
    QPointF searchForFood(const QPointF& pos) const;
    QPointF returnToNest(const QPointF& pos) const;
    void evaporatePheromones();
    QPointF getRandomDiraction() const;

private:
    int antCount = 10;
    int foodCollected = 0;
    qreal simulationSpeed = 1.0;
    qreal moveStep = 0.001;
    qreal detectionRadius = 0.03;

    bool isRunning = false;
    bool isPaused = false;

    AntColonyModel* antColonyModel;

    QTimer* runTimer = nullptr;
    QMutex mutex;
};
