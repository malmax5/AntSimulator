#include "../include/CoordinateSystem.hpp"

CoordinateSystem::CoordinateSystem(qreal width, qreal height)
    : worldWidth(width), worldHeight(height),
      windowWidth(400.0), windowHeight(400.0),
      zoom(1.0), zoomMin(1.0), zoomMax(10.0),
      offset(0, 0)
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
    if (worldPos.isNull())
    {
        return QPointF();
    }

    qreal cx = windowWidth / worldWidth;
    qreal cy = windowHeight / worldHeight;

    qreal x = (worldPos.x() - offset.x()) * cx;
    qreal y = (worldPos.y() - offset.y()) * cy;
    return QPointF(x, y);
}

QPointF CoordinateSystem::screenToWorld(const QPointF& screenPos) const
{
    if (screenPos.isNull())
    {
        return QPointF();
    }

    qreal cx = worldWidth / windowWidth;
    qreal cy = worldHeight / windowHeight;

    qreal x = offset.x() + (screenPos.x() * cx) / zoom;
    qreal y = offset.y() + (screenPos.y() * cy) / zoom;
    return QPointF(x, y);
}

void CoordinateSystem::setZoom(qreal zoomFactor)
{
    zoom = qBound(zoomMin, zoomFactor, zoomMax);
    updateOffset();
}

void CoordinateSystem::setOffset(const QPointF& offset)
{
    if (offset.isNull())
    {
        return;
    }

    this->offset = offset;
    updateOffset();
}

void CoordinateSystem::setOffset(qreal xCord, qreal yCord)
{
    this->offset = QPointF(xCord, yCord);
    updateOffset();
}

void CoordinateSystem::updateOffset()
{
    qreal visibleWidth = worldWidth / zoom;
    qreal visibleHeight = worldHeight / zoom;

    qreal minOffsetX = qMin(0.0, worldWidth - visibleWidth);
    qreal maxOffsetX = qMax(0.0, worldWidth - visibleWidth);

    qreal minOffsetY = qMin(0.0, worldHeight - visibleHeight);
    qreal maxOffsetY = qMax(0.0, worldHeight - visibleHeight);

    offset.setX(qBound(minOffsetX, offset.x(), maxOffsetX));
    offset.setY(qBound(minOffsetY, offset.y(), maxOffsetY));
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
