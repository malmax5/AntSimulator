#include "../../include/graphics/FoodItem.hpp"

FoodItem::FoodItem(const QPointF& pos, QGraphicsSvgItem* parent)
    : QGraphicsSvgItem(parent)
{
    setSharedRenderer(new QSvgRenderer(QString(":/icon_resources/resources/icons/food.svg")));
    if (!renderer()->isValid())
    {
        qWarning() << "Failed to load Food SVG";
    }

    QTransform baseTransform = QTransform();
    baseTransform.scale(scaleFactor, scaleFactor);
    baseTransform.translate(-boundingRect().width() / 2, -boundingRect().height() / 2);

    setTransform(baseTransform);
    setPos(pos);
    setZValue(2);
}