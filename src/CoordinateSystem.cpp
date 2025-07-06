#include "../include/CoordinateSystem.hpp"

CoordinateSystem::CoordinateSystem(qreal width, qreal height)
    : worldWidth(width), worldHeight(height)
{

}

CoordinateSystem::CoordinateSystem(const QSize& size)
    : worldWidth(size.width()), worldHeight(size.height())
{
    
}

void CoordinateSystem::setWindowSize(qreal width, qreal height)
{
    windowWidth = width;
    windowHeight = height;
}

void CoordinateSystem::setWindowSize(const QSize& size)
{
    windowWidth = size.width();
    windowHeight = size.height();
}

QPointF CoordinateSystem::worldToScreen(const QPointF& logicPos) const
{
    return QPointF(logicPos.x() * worldWidth, logicPos.y() * worldHeight);
}

QPointF CoordinateSystem::screenToWorld(const QPointF& screenPos) const
{
    qreal cx = worldWidth / windowWidth;
    qreal cy = worldHeight / windowHeight; 
    return QPointF(screenPos.x() * cx, screenPos.y() * cy);
}
