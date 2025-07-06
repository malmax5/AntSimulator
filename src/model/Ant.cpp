#include "../../include/model/Ant.hpp"

QPointF Ant::getScreenPosition(qreal windowWidth, qreal windowHeight) const
{
    return QPointF(logicalPosition.x() * windowWidth, logicalPosition.y() * windowHeight);
}
