#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "customscene.h"
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Slot(QPointF point);
    void Doubleclick(QPointF point);

private slots:
    void on_calc_button_clicked();

    void on_clear_button_clicked();

private:
    Ui::MainWindow *ui;
    CustomScene *scene;


};
#endif // MAINWINDOW_H
