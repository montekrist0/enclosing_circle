#include "item_point.h"

item_point::item_point() : QGraphicsItem()
{

}

item_point::~item_point() {

}

QRectF item_point::boundingRect() const
{
    return QRectF(-1,-1,2,2);
}

void item_point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::white,2,Qt::SolidLine));
    painter->drawPoint(0,0);
    //painter->drawEllipse(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

/*void item_point::item_point(const int &x, const int &y) {
    centrx=x;
    centry=y;
}*/
