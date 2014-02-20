#include "linearprediction.h"
#include <QDebug>
/*  переопределённая система J * x = B может быть решена только с некоторым приближением
 */

linearPrediction::linearPrediction()
{
    step = 1;

    M = 50; // важно что бы M - N > N, то есть M > 2*N хотя даже если система недоопределённая строится вроде норм..
    N = 4;   // N не меньше 2

    _J.init(M - N, N);
    _a.init(N, 1);
    _b.init(M - N, 1);

    double stp = 0, stp2 = 0;

    for (int i = 0; i < M - N; i++) {
        stp = 0;
        for (int j = 0; j < N; j++) {               // шаг иксов = 1
            _J.set_value(i, j, myFun((stp2 + stp) /*i + j*/));
            stp += step;
        }
        stp2 += step;
    }

    stp = 0;
    for (int i = 0; i < M - N; i++) {
        _b.set_value(i, 0, myFun((N + stp) /*i*/));
        stp += step;
    }

    _A = _J.Transpose().Mul(_J);                       // [_A] * [_a] = [_B]
    _B = _J.Transpose().Mul(_b);
    _a = Gaus_Jordan_Method(_A, _B);

    // ниже тест
//    Matrix ss, sss, ssr;
//    ss.init(3, 3);
//    sss.init(3, 1);
//    ssr.init(3, 1);

//    ss.set_value(0, 0, 1);
//    ss.set_value(0, 1, 2);
//    ss.set_value(0, 2, 3);
//    ss.set_value(1, 0, 2);
//    ss.set_value(1, 1, 2);
//    ss.set_value(1, 2, 0);
//    ss.set_value(2, 0, 3);
//    ss.set_value(2, 1, 7);
//    ss.set_value(2, 2, 5);

//    sss.set_value(0, 0, 14);
//    sss.set_value(1, 0, 6);
//    sss.set_value(2, 0, 32);

//    ssr = Gaus_Jordan_Method(ss, sss);
//    int i = 0;

}

Matrix linearPrediction::Gaus_Jordan_Method(Matrix A, Matrix B)
{
    double need;
    double mul;
    double del;
    Matrix a;
    a.init(A.get_N(), 1);

    Matrix *X = new Matrix;
    X->init(A.get_N(), A.get_N() + 1);
    for (int i = 0; i < A.get_N(); i++)
        for(int j = 0; j < A.get_N() + 1; j++) {
            if (j == A.get_N())
                X->set_value(i, j, B.get_value(i, 0));
            else
                X->set_value(i, j, A.get_value(i, j));
        }

    for (int l = 0; l < A.get_N(); l++) {

        // перестановка строк по убыванию первых коэффициентов
        for (int k = l; k < A.get_N() - 1; k++) {  // или < N ?
            for (int i = l; i < A.get_N() - 1; i++) {
                    if ( X->get_value(i, l) < X->get_value(i + 1, l) ) // надо что бы больше по абсолютному значению
                        for (int j = l; j < A.get_N() + 1; j++) {
                            need = X->get_value(i, j);
                            X->set_value(i, j, X->get_value(i + 1, j));
                            X->set_value(i + 1, j, need);
                        }
            }
        }

        // деление строки на первый элемент строки
        del = X->get_value(l, l);
        if (del == 0) {
//            qDebug() << "могло быть деление на ноль! :)";
            continue;
        }
        for (int j = l; j < A.get_N() + 1; j++) {
            X->set_value(l, j, X->get_value(l, j) / del);
        }

        // вычитание строки из оставшихся с предворительным умножением
        for (int i = l; i < A.get_N() - 1; i++) {
            mul = X->get_value(i + 1, l);
            for (int j = l; j < A.get_N() + 1; j++) {
                X->set_value(i + 1, j, X->get_value(i + 1, j) - X->get_value(l, j) * mul);
            }
        }

    }

//---------
    double s;
    for (int i = X->get_N() - 1; i > 0; i--)
        if (X->get_value(i - 1, i - 1) != 0.0) {

            s = X->get_value(i - 1, X->get_N() - 1);
            for (int k = 1; k < X->get_N() - i; k++) {
                s -= X->get_value(i - 1, X->get_N() - 1 - k) * a.get_value(X->get_N() - 1 - k, 0);
            }
            a.set_value(i - 1, 0, s / X->get_value(i - 1, i - 1));
        } else
            a.set_value(i - 1, 0, 0);
//----------

    return a;
}

Matrix linearPrediction::prediction() {

    Matrix Y, stack;
    Y.init(M - N, 1);
    stack.init(1, N);

    for (int i = 0; i < N; i++) {
        stack.set_value(0, i, _J.get_value(0, i));
    }

    double s;

    for (int j = 0; j < M - N; j++) {
        s = 0;

        for (int i = 0; i < N; i++) {
                s += _a.get_value(i, 0) * stack.get_value(0, i);
        }
        Y.set_value(j, 0, s);

        for (int i = 0; i < N - 1; i++) {
                stack.set_value(0, i, stack.get_value(0, i + 1));
        }
        stack.set_value(0, N - 1, s);
    }

    return Y;
}

double linearPrediction::myFun(double x) {
    int low = 0, high = 5;
//    return qrand() % ((high + 1) - low) + low; // Random number between low and high
//    return cos(x/7)*sin(x/7);
//    return sin(x/3);
//    return x;
//    return (x * x - x) / 10;
    return sin(x) + 3*cos(x/4);
}

