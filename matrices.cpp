#include <matrices.h>
#include <QVector>
#include <QDebug>


void Matrix::init(int m, int n)
{
    _M = m;
    _N = n;
    matrix = QVector< QVector<double> >( m, QVector<double> (n) );
}

int Matrix::get_M()
{
    return _M;
}

int Matrix::get_N()
{
    return _N;
}

double Matrix::get_value(int m, int n)
{
    return matrix[m][n];
}

void Matrix::set_value(int m, int n, double v)
{
    matrix[m][n] = v;
}


// заполнение матрицы нулями
void Matrix::Zero()
{
    int m = this->get_M();
    int n = this->get_N();

    int i, j;

//#pragma omp parallel for shared(matrix)
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
             matrix[i][j] = 0;
}

// единичная матрица
void Matrix::E()
{
    int m = this->get_M();
    int n = this->get_N();

    this->Zero(); // можно и без this->

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (i == j)
                matrix[i][j] = 1;
}

// заполняет матрицу единицами
void Matrix::E2()
{
    int m = this->get_M();
    int n = this->get_N();

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 1;
}


void Matrix::set_all(Matrix B)
{
    int m = this->get_M();
    int n = this->get_N();
    // M и N у B должны быть равны m и n

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            set_value(i, j, B.get_value(i, j));
}

void Matrix::set_all(Matrix *B)
{
    int m = this->get_M();
    int n = this->get_N();
    // M и N у B должны быть равны m и n

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            set_value(i, j, B->get_value(i, j));
}

// возвращает копию матрицы A
Matrix Matrix::Cop()
{
    int m = this->get_M();
    int n = this->get_N();
    Matrix B;
    B.init(m, n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            B.set_value(i, j, matrix[i][j]);

    return B;
}

// транспонирование матрицы
Matrix Matrix::Transpose()
{
    int m = this->get_M();
    int n = this->get_N();
    Matrix B;
    B.init(n, m); // в другом порядке т.к матрица будет транспонированная

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            B.set_value(j, i, matrix[i][j]);

    return B;
}

// сложение матриц
Matrix Matrix::Add(Matrix B)
{
    int m = this->get_M();
    int n = this->get_N();
    Matrix C;
    C.init(m, n);

    if ( (m != B.get_M()) || (n != B.get_N()) )
        qDebug() << "Ошибка сложения матриц: не совпадение размерностей";

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            C.set_value( i, j, matrix[i][j] + B.get_value(i , j) );
    return C;
}

Matrix Matrix::Add(Matrix *B)
{
    int m = this->get_M();
    int n = this->get_N();
    Matrix C;
    C.init(m, n);

    if ( (m != B->get_M()) || (n != B->get_N()) )
        qDebug() << "Ошибка сложения матриц: не совпадение размерностей";

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            C.set_value( i, j, matrix[i][j] + B->get_value(i , j) );
    return C;
}


// вычитанние матриц
Matrix Matrix::Sub(Matrix B)
{
    int m = this->get_M();
    int n = this->get_N();
    Matrix C;
    C.init(m, n);

    if ( (m != B.get_M()) || (n != B.get_N()) )
        qDebug() << "Ошибка вычитания матриц: не совпадение размерностей";

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            C.set_value( i, j, matrix[i][j] - B.get_value(i , j) );
    return C;
}

Matrix Matrix::Sub(Matrix *B)
{
    int m = this->get_M();
    int n = this->get_N();
    Matrix C;
    C.init(m, n);

    if ( (m != B->get_M()) || (n != B->get_N()) )
        qDebug() << "Ошибка вычитания матриц: не совпадение размерностей";

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            C.set_value( i, j, matrix[i][j] - B->get_value(i , j) );
    return C;
}


// умножение матриц
Matrix Matrix::Mul(Matrix B)
{
    int m = this->get_M();
    int n = B.get_N();
    Matrix C;
    C.init(m, n);
    C.Zero();

    if ( this->get_N() != B.get_M() )
        qDebug() << "Ошибка умножения матриц: не совпадение размерностей";

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < this->get_N(); k++)
                C.set_value( i, j, C.get_value(i, j) + matrix[i][k] * B.get_value(k, j));
    return C;
}

Matrix Matrix::Mul(Matrix *B)
{
    int m = this->get_M();
    int n = B->get_N();
    Matrix C;
    C.init(m, n);
    C.Zero();

    if ( this->get_N() != B->get_M() )
        qDebug() << "Ошибка умножения матриц: не совпадение размерностей";

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < this->get_N(); k++)
                C.set_value( i, j, C.get_value(i, j) + matrix[i][k] * B->get_value(k, j));
    return C;
}

// домножение матрицы на число
Matrix Matrix::MulValue(double v)
{
    int m = this->get_M();
    int n = this->get_N();
    Matrix B;
    B.init(m, n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            B.set_value(i, j, matrix[i][j] * v);
    return B;
}

//вычисляет обратную матрицу
Matrix Matrix::Inverse()
{
    Matrix A;
    Matrix B;
    double sk, sz;

    int m = this->get_M();
    int n = this->get_N();

    A = this->Cop();
    B.init(m, n);
    B.Zero();

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (i == j)
                B.set_value(i, j, 1);
    for (int i = 0; i < m; i++) {
        sk = 1 / A.get_value(i, i);
        for (int j = 0; j < m; j++)
            if (i != j) {
            sz = sk * A.get_value(j, i);
            for (int k = 0; k < m; k++)
                A.set_value( j, k, A.get_value(j, k) - sz * A.get_value(i,k) );
            for (int k = 0; k < m; k++)
                B.set_value( j, k, B.get_value(j, k) - sz * B.get_value(i,k) );
            }
        for (int k = 0; k < m; k++)
            A.set_value(i, k, sk * A.get_value(i, k) );
        for (int k = 0; k < m; k++)
            B.set_value(i, k, sk * B.get_value(i, k) );
     }

    return B;
}
