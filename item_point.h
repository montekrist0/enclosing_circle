#ifndef ITEM_POINT_H
#define ITEM_POINT_H

#include <QGraphicsItem>
#include <QPainter>

class item_point : public QGraphicsItem
{
public:
    item_point();
    ~item_point();
    /*item_point(const int &x, const int &y);*/
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
/*
private:
    int centrx;
    int centry;*/
};

#endif // ITEM_POINT_H
