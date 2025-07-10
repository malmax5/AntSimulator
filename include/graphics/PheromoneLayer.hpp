#pragma once

#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QPainter>
#include <QPen>
#include <QColor>

#include "../model/PheromoneMap.hpp"

class PheromoneLayer : public QGraphicsSvgItem
{
public:
    explicit PheromoneLayer(const PheromoneMap& map, QGraphicsSvgItem* parent = nullptr);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget) override;

private:
    QSvgRenderer* renderer;
    const PheromoneMap& map;
};
