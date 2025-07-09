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
        qreal factor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
        qreal currentScale = this->transform().m11();
        if ((factor < 1 && currentScale < 0.1) || (factor > 1 && currentScale > 1000))
        {
            
        }
        else
        {
            this->scale(factor, factor);
            event->accept();
        }

    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}
