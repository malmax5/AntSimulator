#include "../../include/graphics/CustomScene.hpp"

CustomScene::CustomScene(QObject* parent)
    : QGraphicsScene(parent)
{

}

void  CustomScene::drawBackground(QPainter* painter, const QRectF& rect)
{
    QPixmap bg(QString(":/icon_resources/resources/icons/background.png"));
    if (!bg.isNull())
    {
        painter->drawPixmap(rect, bg, bg.rect());
    }
}
