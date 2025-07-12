#pragma once

#include <QGraphicsView>

class CustomView : public QGraphicsView
{
    Q_OBJECT
public:
    using QGraphicsView::QGraphicsView;
    explicit CustomView(QWidget* parent);

signals:
    void foodAddRequest(QPointF scenePos);

protected:
    // void drawBackground(QPainter* painter, const QRectF& rect) override;
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    qreal zoomDiff = 0.1;
    qreal currentZoom = 1;
};
