#include "customscene.h"

CustomScene::CustomScene(QObject *parent) : QGraphicsScene()
{
    Q_UNUSED(parent);
}

CustomScene::~CustomScene(){}

void CustomScene::ClearVector() {
    X1.clear();
    Y1.clear();
}

void CustomScene::Add_to_Vector(int x, int y) {
    X1.push_back(x);
    Y1.push_back(y);
}

QVector<int> CustomScene::GetVectorX()
{
    return X1;
}

QVector<int> CustomScene::GetVectorY()
{
    return Y1;
}

void CustomScene::Set_Params_of_Circle(QPointF &&p, int &a)
{
    point = p;
    diametr = a;
}

void CustomScene::Diametr_Reset()
{
    diametr = 0;
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());
}

void CustomScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *click)
{
    this->update();
    emit signalDoubleClickCoordinate(click->scenePos());
}

void CustomScene::drawForeground(QPainter * painter, const QRectF & rect)
{
    painter->setPen(QPen(Qt::white,3,Qt::SolidLine));
    size_t size = X1.size();
    for (size_t i=0; i< size; i++) {
        painter->drawPoint(X1[i],Y1[i]);
    }
    if (diametr!=0) {
        painter->setPen(Qt::green);
        painter->drawEllipse(point,diametr/2,diametr/2);
    }
    Q_UNUSED(rect);
}






