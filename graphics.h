#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>

class MyPaint : public QWidget {

   Q_OBJECT // нужно когда используем сигналы

public:

    MyPaint(QWidget *parent = 0);
    ~MyPaint();

protected:
    void paintEvent(QPaintEvent * event); // обработчик события отрисовки
};

#endif // GRAPHICS_H
