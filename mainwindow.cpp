#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <graphics.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyPaint *o_graph = new MyPaint;
    ui->gridLayout->addWidget(o_graph);
}

MainWindow::~MainWindow()
{
    delete ui;
}
