#pragma once

#include <QObject>
#include <QPointF>
#include <QGraphicsScene>

#include <QSet>
#include <QHash>
#include <QMap>
#include <QPair>

#include "../model/AntColonyModel.hpp"
#include "../graphics/AntItem.hpp"
#include "../graphics/PheromoneLayer.hpp"

class SimulationVisualizer : public QObject
{
    Q_OBJECT

public:
    explicit SimulationVisualizer(QGraphicsScene* scene, AntColonyModel* model, QObject* parent = nullptr);

public slots:
    void updateVisualization();

private:
    void createNest();
    void updateAnts();
    void updateFood();
    void setPheromoneMap();

    QGraphicsScene* scene;
    AntColonyModel* model;
    PheromoneLayer* pheromoneLayer = nullptr;
    QMutex updateMutex;
    
    QGraphicsEllipseItem* nestItem = nullptr;
    QHash<int, AntItem*> antItems;
    QHash<QPair<qreal, qreal>, QGraphicsItem*> foodItems;
};