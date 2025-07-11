#pragma once

#include <QGraphicsView>

class CustomView : public QGraphicsView
{
    Q_OBJECT
public:
    using QGraphicsView::QGraphicsView;

signals:
    void foodAddRequest(QPointF scenePos);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    qreal zoomDiff = 0.1;
    qreal currentZoom = 1;
};
