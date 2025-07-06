#pragma once

#include <QtCore>
#include <QPointF>
#include <QSize>

class CoordinateSystem
{
public:
    CoordinateSystem(qreal width = 1.0, qreal height = 1.0);
    CoordinateSystem(const QSize& size);

    void setWindowSize(qreal width, qreal height);
    void setWindowSize(const QSize& size);

    QPointF worldToScreen(const QPointF& logicPos) const;
    QPointF screenToWorld(const QPointF& screenPos) const;

private:
    qreal worldWidth = 1.0;
    qreal worldHeight = 1.0;
    qreal windowWidth = 400.0;
    qreal windowHeight = 400.0;
};
