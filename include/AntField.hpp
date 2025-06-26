#pragma once

#include <QWidget>
#include <QPixmap>
#include <QVector>
#include <QPointF>

#include "model/Ant.hpp"
#include "model/FoodStorage.hpp"
#include "model/PheromoneMap.hpp"

class AntField : public QWidget
{
    Q_OBJECT

public:
    explicit AntField(QWidget* parent = nullptr);

    void redraw(const QVector<Ant>& ants);
    void addFood(const QPointF& pos);

protected:
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    QVector<Ant> currentAnts;
    FoodStorage foodPositions;
    PheromoneMap pheromoneMap;
    QPixmap bufferPixmap;

    qreal scale = 1.0;
};
