#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <QPair>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1280,640);
    scene = new CustomScene();

    //задаем отображаемые границы графической сцены на graphicsView
    ui->graphicsView->setSceneRect(ui->graphicsView->viewport()->geometry());
    //выравниваем сцену таким образом, чтобы ее центр (0;0) был слева внизу.
    ui->graphicsView->setAlignment((Qt::AlignLeft | Qt::AlignBottom));

    scene->setBackgroundBrush(Qt::black);
    ui->graphicsView->setScene(scene);

    ui->label->setText("Создано точек: 0");

    ui->graphicsView->scale(1,-1);
    ui->graphicsView->setMouseTracking(true);
    QPen whitepen(Qt::white);
    connect(scene, &CustomScene::signalTargetCoordinate, this, &MainWindow::Slot);
    connect(scene, &CustomScene::signalDoubleClickCoordinate, this, &MainWindow::Doubleclick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Slot(QPointF point)
{
    ui->label_2->setText("Координаты мыши\nна сцене\nотносительно левого\nнижнего угла:\nX=" +
                         QString::number(point.rx())+ " " + "Y="+ QString::number(point.ry())
                         );
}

void MainWindow::Doubleclick(QPointF point)
{
    scene->Add_to_Vector(point.rx(),point.ry());
    ui->label->setText("Создано точек:" + QString::number(scene->GetVectorX().size()));
}

//находим расстояние между двумя точками (оно же является диаметром описанной вокруг них окружности.
int DistanceBetweenPoints (int x1, int y1,int x2,int y2) {
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
//находим координаты центра описанной окружности вокруг двух точек
QPair <int,int> Center_of_Circle_with_2points(int x1,int y1,int x2,int y2) {
    return qMakePair((x1+x2)/2,(y1+y2)/2);
}

//функция, определяющая находится ли точка с координатами (х1;у1) внутри окружности
//с центром (centrx;centry) и диаметром diametr

bool InsideCircle (int x1,int y1,int centrx,int centry,int diametr) {
    return (DistanceBetweenPoints(x1,y1,centrx,centry)>diametr/2 ? false: true);
}

//функция, возвращающая пару значений Х и У - координаты центра описанной окружности по трем точкам.
QPair <int,int> Center_of_enclosing_circle(int x1,int y1,int x2,int y2,int x3,int y3) {
    int x12=0,x23=0,x31=0,y12=0,y23=0,y31=0,z1=0,z2=0,z3=0,zx=0,zy=0,z=0;
    x12=x1-x2;
    x23=x2-x3;
    x31=x3-x1;
    y12=y1-y2;
    y23=y2-y3;
    y31=y3-y1;
    z1=x1*x1+y1*y1;
    z2=x2*x2+y2*y2;
    z3=x3*x3+y3*y3;
    zx=y12*z3+y23*z1+y31*z2;
    zy=x12*z3+x23*z1+x31*z2;
    z=x12*y31-y12*x31;
    return {-zx/(2*z),zy/(2*z)};

}

void MainWindow::on_calc_button_clicked()
{
    QVector <int> X = scene->GetVectorX();
    QVector <int> Y = scene->GetVectorY();
    if (X.size()>1) {
        int D3 = DistanceBetweenPoints(X[0],Y[0],X[1],Y[1]);
        int centrx3 = Center_of_Circle_with_2points(X[0],Y[0],X[1],Y[1]).first;
        int centry3 = Center_of_Circle_with_2points(X[0],Y[0],X[1],Y[1]).second;
        size_t size = X.size();
        for (size_t i=2;i<size;i++ ) {
            if (InsideCircle(X[i],Y[i],centrx3,centry3,D3)) {
                continue;       //если текущая точка внутри окружности, то переходим к следующей точке
                }//
            else {              //если текуща точка Xi;Yi не внутри окружности, то ищем окружность,
                //                которая будет содержать в себе все предыдущие точки + текущую
                D3=DistanceBetweenPoints(X[0],Y[0],X[i],Y[i]);
                centrx3 = Center_of_Circle_with_2points(X[0],Y[0],X[i],Y[i]).first;
                centry3 = Center_of_Circle_with_2points(X[0],Y[0],X[i],Y[i]).second;
                for (size_t j=1;j<i;j++ ) {
                     //
                    if (InsideCircle(X[j],Y[j],centrx3,centry3,D3)) {
                        continue;
                    }
                    else {
                        D3=DistanceBetweenPoints(X[j],Y[j],X[i],Y[i]);
                        centrx3 = Center_of_Circle_with_2points(X[j],Y[j],X[i],Y[i]).first;
                        centry3 = Center_of_Circle_with_2points(X[j],Y[j],X[i],Y[i]).second;

                        for (size_t k=0;k<j;k++) {//2
                            if (InsideCircle(X[k],Y[k],centrx3,centry3,D3)) {
                                continue;
                            }
                            else {
                                centrx3=Center_of_enclosing_circle(X[i],Y[i],X[j],Y[j],X[k],Y[k]).first;
                                centry3=Center_of_enclosing_circle(X[i],Y[i],X[j],Y[j],X[k],Y[k]).second;
                                D3=2*DistanceBetweenPoints(X[i],Y[i], centrx3,centry3);
                            }
                        }
                    }
                }
            }
        }

        scene->Set_Params_of_Circle({double(centrx3),double(centry3)},D3);
        scene->update();

        ui->label_3->setText("Диаметр:" + QString::number(D3) + "\nЦентр Х=" + QString::number(centrx3)
                             + " Y=" + QString::number(centry3)
                             );
    }

    else if (X.size()==1) QMessageBox::critical(this,"Недостаточно точек для построения окружности", "Создана одна точка с координатами:\nХ=" + QString::number(X[0])
            + " Y=" + QString::number(Y[0]));

    else QMessageBox::critical(this,"Недостаточно точек для построения окружности", "Нет точек! Задайте как минимум 2 точки.");

}

void MainWindow::on_clear_button_clicked()
{
    scene->ClearVector();
    scene->Diametr_Reset();
    scene->update();

    ui->label->setText("Создано точек: "+ QString::number(scene->GetVectorX().size()));
    ui->label_3->setText("Диаметр: - \n Центр Х= - Y= -");
}
