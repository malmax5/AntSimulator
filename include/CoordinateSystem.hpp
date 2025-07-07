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

    QPointF worldToScreen(const QPointF& worldPos) const;
    QPointF screenToWorld(const QPointF& screenPos) const;

    void setZoom(qreal zoomFactor);
    void setOffset(const QPointF& offset);
    void setOffset(qreal xCord, qreal yCord);


    void moveOffset(const QPointF& dxy);
    void moveOffset(qreal dx, qreal dy);

    QPointF getOffset();
    qreal getZoom() const;
    qreal getWorldWidth();
    qreal getWorldHeight();
    qreal getWindowWidth();
    qreal getWindowHeight();

private:
    void updateOffset();

private:
    qreal worldWidth = 1.0;
    qreal worldHeight = 1.0;
    qreal windowWidth = 400.0;
    qreal windowHeight = 400.0;
    qreal zoom = 1.0;
    qreal zoomMin = 1;
    qreal zoomMax = 10;
    QPointF offset;
};
