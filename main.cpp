#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Построение описанной окружности вокруг точек, заданных двойным нажатием мыши");
    w.show();
    return a.exec();
}
