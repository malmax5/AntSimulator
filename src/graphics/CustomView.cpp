#include "../../include/graphics/CustomView.hpp"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QApplication>

void CustomView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        QPointF scenePos = mapToScene(event->pos());
        emit foodAddRequest(scenePos);
        return;
    }

    QGraphicsView::mousePressEvent(event);
}

void CustomView::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() && QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        qreal factor = (event->angleDelta().y() > 0) ? (1.0 + zoomDiff) : (1.0 - zoomDiff);
        qDebug() << currentZoom;
        if (currentZoom * factor < 1 || currentZoom * factor > 10)
        {
            
        }
        else
        {
            currentZoom *= factor;
            this->scale(factor, factor);
            event->accept();
        }

    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}
