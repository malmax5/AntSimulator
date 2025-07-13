#include "../../include/graphics/CustomView.hpp"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>

CustomView::CustomView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(parent)
{
    setScene(scene);

    setViewportUpdateMode(FullViewportUpdate);
    setRenderHint(QPainter::SmoothPixmapTransform);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QPixmap bgImage(":/icon_resources/resources/icons/background.png");
    if(!bgImage.isNull())
    {
        QGraphicsPixmapItem* backgroundItem = scene->addPixmap(bgImage);
        backgroundItem->setZValue(-1);
        backgroundItem->setPos(-1, -1);
        
        backgroundItem->setScale(0.01);
    }

    fitInView(0, 0, 1, 1);
    centerOn(0.5, 0.5);
}

void CustomView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        QPointF scenePos = mapToScene(event->pos());
        qDebug() << scenePos;
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
        if (currentZoom * factor < 1.6 || currentZoom * factor > 10)
        {
            
        }
        else
        {
            currentZoom *= factor;
            qDebug() << currentZoom;
            setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
            this->scale(factor, factor);
            event->accept();
        }

    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}
