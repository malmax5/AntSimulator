#pragma once

#include <QGraphicsSvgItem>
#include <QSvgRenderer>

#include <QPointF>

class NestItem : public QGraphicsSvgItem
{
public:
    explicit NestItem(const QPointF& pos, QGraphicsSvgItem* parent = nullptr);

private:
    qreal scaleFactor = 0.0001;
};
