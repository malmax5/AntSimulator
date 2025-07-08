#include "../include/AntField.hpp"

#include <QApplication>
#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QMouseEvent>

AntField::AntField(AntColonyModel* antColonyModel, QWidget* parent)
    : antColonyModel(antColonyModel), QWidget(parent)
{
    bufferPixmap = QPixmap(size());
    bufferPixmap.fill(Qt::white);
}

void AntField::redraw()
{
    update();
}

void AntField::addFood(const QPointF& pos)
{
    antColonyModel->addFood(coordinateSystem.screenToWorld(pos));

    update();
}

void AntField::removeFood(const QPointF& pos)
{
    antColonyModel->removeFood(pos);

    update();
}

void AntField::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
        {
            addFood(event->pos());
        }
        else
        {
            lastMousePos = event->pos();
        }
    }
}

void AntField::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
        {
            return;
        }
        
        QPointF delta = event->pos() - lastMousePos;

        coordinateSystem.moveOffset(
            -delta.x() / coordinateSystem.getWindowWidth() * coordinateSystem.getWorldWidth(),
            -delta.y() / coordinateSystem.getWindowHeight() * coordinateSystem.getWorldHeight()
        );

        lastMousePos = event->pos();
        update();
    }
}

void AntField::wheelEvent(QWheelEvent* event)
{
    if (!QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
    {
        return;
    }

    qreal oldZoom = coordinateSystem.getZoom();
    QPointF oldOffset = coordinateSystem.getOffset();
    QPointF cursorWorldPos = coordinateSystem.screenToWorld(event->position());

    if (event->angleDelta().y() > 0)
    {
        coordinateSystem.setZoom(coordinateSystem.getZoom() * 1.1);
    }
    else
    {
        coordinateSystem.setZoom(coordinateSystem.getZoom() / 1.1);
    }

    qreal zoomRatio = oldZoom / coordinateSystem.getZoom();
    QPointF newOffset(
        cursorWorldPos.x() - (cursorWorldPos.x() - oldOffset.x()) * zoomRatio,
        cursorWorldPos.y() - (cursorWorldPos.y() - oldOffset.y()) * zoomRatio
    );

    coordinateSystem.setOffset(newOffset);

    update();
}

void AntField::resizeEvent(QResizeEvent* event)
{
    coordinateSystem.setWindowSize(event->size());
}

void AntField::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    qreal zoom = coordinateSystem.getZoom();

    bufferPixmap = QPixmap(size());
    bufferPixmap.fill(Qt::white);

    QPainter painter(&bufferPixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.scale(zoom, zoom);

    const qreal pheromoneAlpha = 0.3;
    painter.setPen(Qt::NoPen);
    
    for (const auto& point : antColonyModel->getPheromoneMap().getPheromonePoints()) // !size
    {
        painter.setBrush(QColor(255, 0, 0, qMin(255, qMax(30, static_cast<int>(255 * pheromoneAlpha)))));
        painter.drawEllipse(coordinateSystem.worldToScreen(point.pos), zoom * 2, zoom * 2);
    }

    painter.setBrush(Qt::green);
    for (const auto& food : antColonyModel->getFoodStorage().getFoods())
    {
        painter.drawEllipse(coordinateSystem.worldToScreen(food), zoom * 5, zoom * 5);
    }

    painter.setBrush(Qt::black);
    for (const auto& ant : antColonyModel->getAnts())
    {
        painter.drawEllipse(coordinateSystem.worldToScreen(ant.logicalPosition), zoom * 3, zoom * 3);
    }

    painter.setBrush(Qt::red);
    painter.drawEllipse(coordinateSystem.worldToScreen(antColonyModel->getNestPosition()), zoom * 10, zoom * 10);

    QPainter thisPainter(this);
    thisPainter.drawPixmap(0, 0, bufferPixmap);
}
