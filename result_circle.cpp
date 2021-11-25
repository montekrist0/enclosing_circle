#include "result_circle.h"



result_circle::result_circle() : QGraphicsItem()
{

}

result_circle::~result_circle(){

}

void result_circle::set_diametr(int D)
{
    diametr = D;
}

QRectF result_circle::boundingRect() const
{
    return QRectF(-diametr/2,-diametr/2,diametr,diametr);
}


void result_circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::green);
    painter->drawEllipse(boundingRect());
    //painter->setRenderHint(QPainter::Antialiasing,true);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

