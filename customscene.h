#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>


class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject *parent = nullptr);
    ~CustomScene();
    void ClearVector ();
    void Add_to_Vector(int x, int y);
    QVector <int> GetVectorX();
    QVector <int> GetVectorY();
    void Set_Params_of_Circle(QPointF &&p,int &a);
    void Diametr_Reset();

signals:
    // Сигнал для передачи координат положения курсора мыши
        void signalTargetCoordinate(QPointF point);
        void signalDoubleClickCoordinate(QPointF point);

protected:

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *click);


    void drawForeground(QPainter *painter, const QRectF &rect);

private:
    QPointF point;
    int diametr;
    QVector <int> X1;
    QVector <int> Y1;
};

#endif // CUSTOMSCENE_H
