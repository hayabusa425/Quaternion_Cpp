#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Quaternion
{
    private:
        double q[4]; // w, x, y ,z の各成分を配列で保持する

    public:
        // コンストラクタ
        Quaternion(double w = 0,  double x = 0, double y = 0, double z = 0)
        {
            q[0] = w;
            q[1] = x;
            q[2] = y;
            q[3] = z;
        }

        // アクセッサ(constバージョンと非constバージョンの2種類)
        double operator [] (int i) const
        {
            return q[i];
        }
        double &operator [] (int i)
        {
            return q[i];
        }

        // クォータニオンの表示文字列
        void display_quaternion()
        {
            cout << "(" << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3] << ")" << endl;
        }

        // 足し算
        Quaternion &operator += (const Quaternion &);
        
        // 和の逆元(単項マイナス)
        Quaternion &negative();

        // 掛け算
        Quaternion &operator *= (const Quaternion &);

        // 積の逆元(逆クォータニオン)
        Quaternion &inverse();
};

// 足し算
Quaternion operator + (const Quaternion &a, const Quaternion &b)
{
    Quaternion r(0, 0, 0, 0);
    r[0] = a[0] + a[0];
    r[1] = a[1] + b[1];
    r[2] = a[2] + b[2];
    r[3] = a[3] + b[3];
    return Quaternion(r);
}
Quaternion &Quaternion::operator += (const Quaternion &a)
{
    return *this = *this + a;
}

// 和の逆元
Quaternion &Quaternion::negative()
{
    for(int i=0;i<4;i++){
        q[i] = -q[i];
    }
    return *this;
}

// 掛け算代入
Quaternion operator * (const Quaternion &a, const Quaternion &b)
{
    Quaternion r(0, 0, 0, 0);
    r[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
    r[1] = a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2];
    r[2] = a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1];
    r[3] = a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0];
    return Quaternion(r);
}
Quaternion &Quaternion::operator *= (const Quaternion &a)
{
    return *this = *this * a;
}

// 積の単位元
const Quaternion QUAT_UNIT = Quaternion(1.0, 0.0, 0.0, 0.0);


// 共役クォータニオン
Quaternion conj(const Quaternion &a)
{
    return Quaternion(a[0], -a[1], -a[2], -a[3]);
}

// クォータニオンのノルム
double norm(const Quaternion &a)
{
    return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3]);
}

// 積の逆元(逆クォータニオン)
Quaternion &Quaternion::inverse()
{
    double n = norm(*this) * norm(*this);
    q[0] /= n;
    for(int i=1;i<4;i++)
    {
        q[i] /= -n;
    }
    return *this;
}

// ゼロクォータニオン
const Quaternion QUAT_ZERO = Quaternion(0.0, 0.0, 0.0, 0.0);

int main()
{
    Quaternion a, b(1, 2, 3, 4), c(5, 6, 7, 8);
    double n;

    cout << "/* クォータニオンのテスト演算 */" << endl;

    // 足し算のテスト演算
    a = b + c;
    cout << "(1, 2, 3, 4) + (5, 6, 7, 8) = ";
    a.display_quaternion();

    // 和の逆元のテスト演算
    b.negative();
    cout << "(1, 2, 3, 4)の和の逆元は";
    b.display_quaternion();
    b.negative();

    // 掛け算のテスト演算
    a = b * c;
    cout << "(1, 2, 3, 4) * (5, 6, 7, 8) = ";
    a.display_quaternion();

    // 積の単位元のテスト演算
    a = b * QUAT_UNIT;
    cout << "(1, 2, 3, 4) * 1 = ";
    a.display_quaternion();
    a = QUAT_UNIT * b;
    cout << "1 * (1, 2, 3, 4) = ";
    a.display_quaternion();

    // 共役クォータニオンのテスト演算
    a = conj(b);
    cout << "(1, 2, 3, 4)の共役クォータニオンは";
    a.display_quaternion();

    // クォータニオンのノルムのテスト演算
    n = norm(b);
    cout << "(1, 2, 3, 4)のノルムは " << n << endl;
    
    // 積の逆元のテスト演算(逆クォータニオン)
    a = b.inverse();
    cout << "(1, 2, 3, 4)の積の逆元(逆クォータニオン)は ";
    a.display_quaternion();
    b.inverse();

    // ゼロクォータニオンのテスト演算
    a = b * QUAT_ZERO;
    cout << "(1, 2, 3, 4) * 0 = ";
    a.display_quaternion();
    a = QUAT_ZERO * b;
    cout << "0 * (1, 2, 3, 4) = ";
    a.display_quaternion();

    cout << "/* クォータニオンのテスト演算" << endl;

    return 0;
}
