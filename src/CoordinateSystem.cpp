#include "../include/CoordinateSystem.hpp"

CoordinateSystem::CoordinateSystem(qreal width, qreal height)
    : worldWidth(width), worldHeight(height)
{

}

CoordinateSystem::CoordinateSystem(const QSize& size)
    : CoordinateSystem(size.width(), size.height())
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

QPointF CoordinateSystem::worldToScreen(const QPointF& worldPos) const
{
    qreal cx = windowWidth / worldWidth;
    qreal cy = windowHeight / worldHeight; 
    return QPointF((worldPos.x() * zoom - offset.x()) * cx,
                   (worldPos.y() * zoom - offset.y()) * cy);
}

QPointF CoordinateSystem::screenToWorld(const QPointF& screenPos) const
{
    qreal cx = worldWidth / windowWidth;
    qreal cy = worldHeight / windowHeight; 
    return QPointF((screenPos.x() * cx + offset.x()) * zoom,
                   (screenPos.y() * cy + offset.y()) * zoom);
}

void CoordinateSystem::setZoom(qreal zoomFactor)
{
    zoom = zoomFactor;
}

qreal CoordinateSystem::getZoom() const
{
    return zoom;
}

void CoordinateSystem::setOffset(const QPointF& offset)
{
    this->offset = offset;
}

void CoordinateSystem::moveOffset(const QPointF& dxy)
{
    offset += dxy;
}

void CoordinateSystem::moveOffset(qreal dx, qreal dy)
{
    offset += QPointF(dx, dy);
}
