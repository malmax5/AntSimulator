#include "../include/AntField.hpp"

#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>

AntField::AntField(AntColonyModel* antColonyModel, QWidget* parent)
    : antColonyModel(antColonyModel), QWidget(parent)
{
    bufferPixmap = QPixmap(QSize(antColonyModel->getWidth(), antColonyModel->getHeigth())); // !size
    bufferPixmap.fill(Qt::white);

    setFixedSize(antColonyModel->getWidth(), antColonyModel->getHeigth()); // !size
}

void AntField::redraw()
{
    update();
}

void AntField::addFood(const QPointF& pos)
{
    antColonyModel->addFood(pos);

    update();
}

void AntField::removeFood(const QPointF& pos)
{
    antColonyModel->removeFood(pos);

    update();
}

void AntField::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() > 0)
    {

    }
    else
    {

    }
}

void AntField::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    bufferPixmap = QPixmap(size());
    bufferPixmap.fill(Qt::white);

    QPainter painter(&bufferPixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.scale(scale, scale);

    const qreal pheromoneAlpha = 0.3;
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 0, 0, static_cast<int>(255 * pheromoneAlpha)));

    for (int x = 0; x < antColonyModel->getWidth(); x++) // !size
    {
        for (int y = 0; y < antColonyModel->getHeigth(); y++) // !size
        {
            qreal strength = antColonyModel->getPheromoneMap().getValue(x, y);

            if (strength > 0.1)
            {
                painter.drawEllipse(QPointF(x, y), scale * 2, scale * 2);
            }
        }
    }

    painter.setBrush(Qt::green);
    for (const auto& food : antColonyModel->getFoodStorage().getFoods())
    {
        painter.drawEllipse(food, scale * 5, scale * 5);
    }

    painter.setBrush(Qt::black);
    for (const auto& ant : antColonyModel->getAnts())
    {
        painter.drawEllipse(ant.position, scale * 3, scale * 3);
    }

    painter.setBrush(Qt::red);
    painter.drawEllipse(QPointF(width() / 2.0, height() / 2.0), 10, 10);

    QPainter thisPainter(this);
    thisPainter.drawPixmap(0, 0, bufferPixmap);
}
