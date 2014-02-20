#include "mainwindow.h"
#include <QApplication>
#include <QTime> // для рандома
#include <linearprediction.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTime  time = QTime::currentTime();
    qsrand((uint)time.msec());
    MainWindow w;
    w.show();
  //  linearPrediction *o = new linearPrediction;

    return a.exec();
}
