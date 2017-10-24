#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>

using namespace std;

template <typename T, int N>

class Matrix
{
    private:
        T m[N][N];

    public:
        Matrix(T a = 0)
        {
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    m[i][j] = 0;
                }
            }
            for(int k=0;k<N;k++)
            {
                m[k][k] = a;
            }
        }

    T operator () (int i, int j) const
    {
        return m[i][j];
    }

    Matrix &assign (T a, int i, int j)
    {
        m[i][j] = a;
        return *this;
    }
    
    // 足し算代入
    Matrix &operator += (const Matrix &);

    // 和の逆元
    Matrix &negative();

    // 掛け算代入
    Matrix &operator *= (const Matrix &);

    // 転置行列の生成
    Matrix &trans();
};

// 足し算代入
/*
template <typename T, int N>
Matrix<T, N> &Matrix <T, N>::operator += (const Matrix &a)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            m[i][j] += a.m[i][j];
        }
    }
    return *this;
}
*/

// 足し算演算
template <typename T, int N>
Matrix<T, N> operator + (const Matrix<T, N> &a, const Matrix<T, N> &b)
{
    Matrix<T, N> r;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            r.assign(a(i, j) + b(i, j), i, j);
        }
    }
    return Matrix<T, N> (r);
}
template <typename T, int N>
Matrix<T, N> &Matrix<T, N>::operator += (const Matrix &a)
{
    return *this = *this + a;
}

// 和の逆元
template <typename T, int N>
Matrix <T, N> &Matrix <T, N>::negative()
{    
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(m[i][j] != 0)
                m[i][j] = -m[i][j];
        }
    }
    return *this;
}

// 掛け算
template <typename T, int N>
Matrix<T, N> operator * (const Matrix<T, N> &a, const Matrix<T, N> &b)
{
    Matrix<T, N> r;
    double n = 0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            for(int k=0;k<N;k++)
            {
                n += a(i, k) * b(k, j);
            }
            r.assign(n, i, j);
            n = 0;
        }
    }
    return Matrix<T, N> (r);
}
template <typename T, int N>
Matrix<T, N> &Matrix<T, N>::operator *= (const Matrix &a)
{
    return *this = *this * a;
}

// 転置行列の生成
template <typename T, int N>
Matrix<T, N> &Matrix<T, N>::trans()
{
    for(int i=0;i<N;i++)
    {
        for(int j=i+1;j<N;j++)
        {
            std::swap(m[i][j], m[j][i]);
        }
    }
    return *this;
}

int main()
{
    Matrix<double, 2> a(0), b(1), c(2), d(3), e(0); // 代入値は対角行列の数値(1の時，単位行列になる)
    //a.assign(1, 0, 0);
    
    a = c + d;

    cout << a(0, 0) << a(0, 1) << endl;
    cout << a(1, 0) << a(1, 1) << endl << endl;
    
    a.negative();

    cout << a(0, 0) << a(0, 1) << endl;
    cout << a(1, 0) << a(1, 1) << endl << endl;

    a = c * d;
    
    cout << a(0, 0) << a(0, 1) << endl;
    cout << a(1, 0) << a(1, 1) << endl << endl;

    e.assign(1, 0, 0);
    e.assign(2, 0, 1);
    e.assign(3, 1, 0);
    e.assign(4, 1, 1);
    cout << e(0, 0) << e(0, 1) << endl;
    cout << e(1, 0) << e(1, 1) << endl << endl;

    e.trans();
    cout << e(0, 0) << e(0, 1) << endl;
    cout << e(1, 0) << e(1, 1) << endl << endl;

    return 0;
}
