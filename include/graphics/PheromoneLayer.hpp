#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QColor>

#include "../model/PheromoneMap.hpp"

class PheromoneLayer : public QGraphicsItem
{
public:
    explicit PheromoneLayer(const PheromoneMap& map, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget) override;

private:
    const PheromoneMap& map;
};
