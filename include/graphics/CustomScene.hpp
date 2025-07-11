#pragma once

#include <QGraphicsScene>

#include <QPainter>
#include <QRectF>
#include <QPixmap>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CustomScene(QObject* parent = nullptr);

protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;
};
