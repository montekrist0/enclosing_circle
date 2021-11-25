#ifndef RESULT_CIRCLE_H
#define RESULT_CIRCLE_H

#include <QGraphicsItem>
#include <QPainter>


class result_circle : public QGraphicsItem
{
public:
    result_circle();
    ~result_circle();
    void set_diametr(int D);
protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
private:

    int diametr=0;
};



#endif // RESULT_CIRCLE_H
