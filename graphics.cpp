#include <graphics.h>
#include <linearprediction.h>
#include <math.h>
#include <QPainter>
#include <QDebug>

MyPaint::MyPaint(QWidget *parent) // конструктор класса MyPaint наследник QWidget
    : QWidget(parent)
{
}

MyPaint::~MyPaint()
{
}

void MyPaint::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
    QPoint *firstP = new QPoint;        // начальная точка
    QPoint *secondP = new QPoint;   // конечная точка

    int recSizeX = 450, recSizeY = 350;  // размер прямоугольника в котором рисуем
    double multiplyX; // масштаб оси X (*)
    double multiplyY; // масштаб оси Y (*)
    int intervalXleft;      // начало оси X
    int intervalXRight;   // конец оси X
    double step = 0.1; // шаг по оси X
    int relX = 10, relY = 200; // начало оси X (менять relY) и Y относительно прямоугольника в котором рисуем

//  рисуем фоновый прямоугольник в котором рисуем
    painter.setBrush(QColor(36, 36, 48));
    painter.setPen(QPen(Qt::blue, 1));
    painter.drawRect(0, 0, recSizeX, recSizeY);

// выбираем цвет для осей
    painter.setPen(QPen(Qt::gray, 1));

// рисуем оси X и Y
    // x
   painter.drawLine(QPointF(0, relY), QPointF(recSizeX, relY));
    // y
     painter.drawLine(QPointF(relX, 0), QPointF(relX, recSizeY));

    multiplyX = 10;
    multiplyY = 20;
    painter.setPen(QPen(QColor("#9240D5"), 1));        // цвет построенной функции

    intervalXleft = 0;
    intervalXRight = 40;

    linearPrediction *o_lin= new linearPrediction;
    Matrix y;

    y = o_lin->prediction();

//    firstP->setX(relX + intervalXleft * multiplyX);
//    firstP->setY(relY -  o_lin->myFun(intervalXleft)* multiplyY);

//    for (double i = intervalXleft + 1; i <= intervalXRight; i+=step) {
//        secondP->setX(relX + i * multiplyX);
//        secondP->setY(relY -  o_lin->myFun(i) * multiplyY);
//        painter.drawLine(*firstP, *secondP);
//        *firstP = *secondP;
//    }
    firstP->setX(relX + intervalXleft * multiplyX);
    firstP->setY(relY -  o_lin->myFun(intervalXleft)* multiplyY);

    for (double i = intervalXleft + o_lin->step; i <= intervalXRight; i+= 0.1 /*i+=o_lin->step*/) {
        secondP->setX(relX + i * multiplyX);
        secondP->setY(relY -  o_lin->myFun(i) * multiplyY);
        painter.drawLine(*firstP, *secondP);
        *firstP = *secondP;
    }
//---------рисуем восстановленные точки----------

    painter.setPen(QPen(Qt::red, 3));
    int k = 0;
//    for (double i = 0; /*k*/ i < o_lin->M - o_lin->N; i++/*= step*/) {
//        secondP->setX(relX + (o_lin->N + i) * multiplyX);
//        secondP->setY(relY -  y.get_value(/*k*/i, 0) * multiplyY);
//        painter.drawPoint(*secondP);
////        k++;
//    }
    for (double i = 0; i < o_lin->M - o_lin->N ; i+= o_lin->step) {
        secondP->setX(relX + (o_lin->N + k) * multiplyX);
        secondP->setY(relY -  y.get_value(i, 0) * multiplyY);
        painter.drawPoint(*secondP);
        k += o_lin->step;
    }

    // ---- ищем ошибку -------
    double S = 0;
    k = 0;
    for (double i = 0; i < o_lin->M - o_lin->N; i++) {
       S += pow(o_lin->myFun(k) - y.get_value(i, 0), 2);
//       qDebug() << "myF" << k << myFunction(i);
//       qDebug() << "ret" << i << y.get_value(i, 0);
       k += o_lin->step;
    }
    qDebug() << pow(S, 0.5) / (o_lin->M - o_lin->N);

}
