#pragma once

#include <QWidget>
#include <QPixmap>
#include <QVector>
#include <QPointF>

#include "model/AntColonyModel.hpp"

class AntField : public QWidget
{
    Q_OBJECT

public:
    explicit AntField(AntColonyModel* antColonyModel, QWidget* parent = nullptr);

    void redraw();

public slots:
    void addFood(const QPointF& pos);
    void removeFood(const QPointF& pos);

protected:
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

private:
    AntColonyModel* antColonyModel;
    QPixmap bufferPixmap;

    qreal scale = 1.0;
};
