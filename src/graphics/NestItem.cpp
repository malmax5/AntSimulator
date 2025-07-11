#include "../../include/graphics/NestItem.hpp"

NestItem::NestItem(const QPointF& pos, QGraphicsSvgItem* parent)
{
    setSharedRenderer(new QSvgRenderer(QString(":/icon_resources/resources/icons/nest.svg")));
    if (!renderer()->isValid())
    {
        qWarning() << "Failed to load Food SVG";
    }

    QTransform baseTransform = QTransform();
    baseTransform.scale(scaleFactor, scaleFactor);
    baseTransform.translate(-boundingRect().width() / 2, -boundingRect().height() / 2);

    setTransform(baseTransform);
    setPos(pos);
    setZValue(4);
}
