#include <iostream>
#include <math.h>
#include <string>

template <typename T, int N>

class Matrix
{
    private:
        T m [N] [N];

    public:
        Matrix(T a = 0)
        {
            for(int i=0;i<N;i++)
            {
                for(int j=0;j<N;j++)
                {
                    m [i] [j] = 0;
                }
            }
            for(int k=0;k<N;k++)
            {
                m [k] [k] = a;
            }
        }

    T operator () (int i, int j) const
    {
        return m [i] [j];
    }

    Matrix &assign (T a, int i, int j)
    {
        m [i] [j] = a;
        return *this;
    }
    
    // 足し算代入
    Matrix &operator += (const Matrix &);

    // 和の逆元
    Matrix &negative();

    // 掛け算代入
    Matrix &operator *= (const Matrix &);
};

int main()
{
    Matrix<double, 2> a(0);
    a.assign(1, 0, 0);
    
    return 0;
}
