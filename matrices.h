#ifndef MATRICES_H
#define MATRICES_H

#include <cmath>
#include <QVector>

class Matrix {

private:
    int _M, _N;

    QVector < QVector <double> >  matrix;

public:
    Matrix() {

    }
    ~Matrix(){
        matrix.clear();
    }

    void init(int m, int n);
    int get_M();
    int get_N();
    double get_value(int m, int n);
    void set_value(int m, int n, double v);
    void set_all(Matrix B);
    void set_all(Matrix *B);
    void Zero();
    void E();
    void E2();
    Matrix Cop();
    Matrix Transpose();
    Matrix Add(Matrix B);
    Matrix Sub(Matrix B);
    Matrix Mul(Matrix B);
    Matrix Add(Matrix *B);
    Matrix Sub(Matrix *B);
    Matrix Mul(Matrix *B);
    Matrix MulValue(double v);
    Matrix Inverse();
};

#endif // MATRICES_H
