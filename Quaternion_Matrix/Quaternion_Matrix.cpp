#include <iostream>
#include <algorithm>
//#include <math.h>
#include <string>
#include <complex>

//#define M_PI 3.141592

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

    // 共役転置の生成
    Matrix &conj();
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

// 共役転置行列の生成
template <typename T, int N>
Matrix<T, N> &Matrix<T, N>::conj()
{
    trans();
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            m[i][j] = std::conj(m[i][j]);
        }
    }
    return *this;
}

// 2x2の行列式の実装
template <typename T>
T det (const Matrix<T, 2> &a)
{
    return a(0, 0) * a(1, 1) - a(0, 1) * a(1, 0);
}

int main()
{
    Matrix<double, 2> a(0), b(1), c(2), d(3), e(0); // 代入値は対角行列の数値(1の時，単位行列になる)
    Matrix<complex<double>, 2> ca(1);
    //a.assign(1, 0, 0);
    
    a = c + d;
    cout << "行列和aは c + d = " << endl;
    cout << a(0, 0) << a(0, 1) << endl;
    cout << a(1, 0) << a(1, 1) << endl << endl;
    
    a.negative();
    cout << "aの和の逆元 = " << endl;
    cout << a(0, 0) << a(0, 1) << endl;
    cout << a(1, 0) << a(1, 1) << endl << endl;

    a = c * d;
    cout << "行列積 c * d = " << endl;
    cout << a(0, 0) << a(0, 1) << endl;
    cout << a(1, 0) << a(1, 1) << endl << endl;

    cout << "転置行列" << endl;
    e.assign(1, 0, 0);
    e.assign(2, 0, 1);
    e.assign(3, 1, 0);
    e.assign(4, 1, 1);
    cout << e(0, 0) << e(0, 1) << endl;
    cout << e(1, 0) << e(1, 1) << endl << endl;
    e.trans();
    cout << e(0, 0) << e(0, 1) << endl;
    cout << e(1, 0) << e(1, 1) << endl << endl;

    double det_e = det(e);
    cout << "eの行列式 = " << det_e << endl << endl;

    cout << "行列の要素を複素数(2元数)に" << endl;
    //ca(0, 0) = complex<double> (1, 2);
    //ca(0, 1) = complex<double> (3, 4);
    //ca(1, 0) = complex<double> (5, 6); 
    //ca(1, 1) = complex<double> (7, 8);
    ca.assign(complex<double>(1, 2), 0, 0);
    ca.assign(complex<double>(3, 4), 0, 1);
    ca.assign(complex<double>(5, 6), 1, 0);
    ca.assign(complex<double>(7, 8), 1, 1);
    cout << ca(0, 0) << ca(0, 1) << endl;
    cout << ca(1, 0) << ca(1, 1) << endl << endl;    

    cout << "上記の複素数行列を共役複素数に変換" << endl;
    ca.conj();
    cout << ca(0, 0) << ca(0, 1) << endl;
    cout << ca(1, 0) << ca(1, 1) << endl << endl;    
 
    // ベクトルの回転の実装
    double theta = 30 * (2 * M_PI / 360); // 回転角 1/6π
    Matrix<double, 2> rot; // 回転行列
    Matrix<double, 2> p, p_prime;
    p.assign(20, 0, 0);
    p.assign(30, 1, 0);
    rot.assign(+std::cos(theta), 0, 0);
    rot.assign(-std::sin(theta), 0, 1);
    rot.assign(+std::sin(theta), 1, 0);
    rot.assign(+std::cos(theta), 1, 1);
    p_prime = rot * p; // pをtheta度回した結果をp_primeに代入
    cout << "回転前の行列p = " << endl;
    cout << p(0, 0) << " " << p(0, 1) << endl;
    cout << p(1, 0) << " " << p(1, 1) << endl;
    cout << "回転行列T(theta) = " << endl;
    cout << rot(0, 0) << " " << rot(0, 1) << endl;
    cout << rot(1, 0) << " " << rot(1, 1) << endl;
    cout << "回転後の行列p_prime = " << endl;
    cout << p_prime(0, 0) << " " << p_prime(0, 1) << endl;
    cout << p_prime(1, 0) << " " << p_prime(1, 1) << endl;
    p_prime = rot * p_prime;
    cout << "もう一度回転させた行列p_prime = " << endl;
    cout << p_prime(0, 0) << " " << p_prime(0, 1) << endl;
    cout << p_prime(1, 0) << " " << p_prime(1, 1) << endl << endl;

    // 複素数による回転，複素平面(ガウス平面)による回転の捉え方
    theta = 30 * (2 * M_PI / 360); // 回転角 1/6π
    complex<double> u (std::cos(theta), std::sin(theta));
    complex<double> p_c(20.0, 30.0);
    complex<double> p_c_prime = u * p_c;
    cout << "位置を表す複素数 p_c" << endl;
    cout << p_c << endl;
    cout << "回転を表す複素数 u" << endl;
    cout << u << endl;
    cout << "回転後の位置を表す複素数 p_c_prime" << endl;
    cout << p_c_prime << endl;
    p_c_prime = u * p_c_prime;
    cout << "もう一度回転させた位置を表す複素数 p_c_prime" << endl;
    cout << p_c_prime << endl << endl;

    return 0;
}
