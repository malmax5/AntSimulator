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
    qreal visibleWidth = worldWidth / zoom;
    qreal visibleHeight = worldHeight / zoom;
    
    qreal x = (worldPos.x() - offset.x()) * (windowWidth / visibleWidth);
    qreal y = (worldPos.y() - offset.y()) * (windowHeight / visibleHeight);
    return QPointF(x, y);
}

QPointF CoordinateSystem::screenToWorld(const QPointF& screenPos) const
{
    qreal visibleWidth = worldWidth / zoom;
    qreal visibleHeight = worldHeight / zoom;
    
    qreal x = offset.x() + (screenPos.x() * visibleWidth / windowWidth);
    qreal y = offset.y() + (screenPos.y() * visibleHeight / windowHeight);
    return QPointF(x, y);
}

void CoordinateSystem::setZoom(qreal zoomFactor)
{
    zoom = qBound(zoomMin, zoomFactor, zoomMax);
    updateOffset();
}

void CoordinateSystem::setOffset(const QPointF& offset)
{
    qreal maxOffsetX = worldWidth * zoom - worldWidth;
    qreal maxOffsetY = worldHeight * zoom - worldHeight;

    this->offset.setX(qBound(0.0, offset.x(), maxOffsetX));
    this->offset.setY(qBound(0.0, offset.y(), maxOffsetY));
}

void CoordinateSystem::setOffset(qreal xCord, qreal yCord)
{
    qreal maxOffsetX = worldWidth * zoom - worldWidth;
    qreal maxOffsetY = worldHeight * zoom - worldHeight;

    this->offset.setX(qBound(0.0, xCord, maxOffsetX));
    this->offset.setY(qBound(0.0, yCord, maxOffsetY));
}

void CoordinateSystem::updateOffset()
{
    qreal maxOffsetX = worldWidth * zoom - worldWidth;
    qreal maxOffsetY = worldHeight * zoom - worldHeight;

    offset.setX(qBound(0.0, offset.x(), maxOffsetX));
    offset.setY(qBound(0.0, offset.y(), maxOffsetY));
}

void CoordinateSystem::moveOffset(const QPointF& dxy)
{
    setOffset(offset + dxy);
}

void CoordinateSystem::moveOffset(qreal dx, qreal dy)
{
    setOffset(offset + QPointF(dx, dy));
}

QPointF CoordinateSystem::getOffset()
{
    return offset;
}

qreal CoordinateSystem::getZoom() const
{
    return zoom;
}

qreal CoordinateSystem::getWorldWidth()
{
    return worldWidth;
}

qreal CoordinateSystem::getWorldHeight()
{
    return worldHeight;
}

qreal CoordinateSystem::getWindowWidth()
{
    return windowWidth;
}

qreal CoordinateSystem::getWindowHeight()
{
    return windowHeight;
}
