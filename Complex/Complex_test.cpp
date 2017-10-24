#include <complex>
#include <iostream>

using namespace std;

int main()
{
    std::complex<double> alpha, beta(1, 2), gamma(3, 4);
    
    alpha = beta + gamma;
    cout << "beta" << beta << " + " << "gamma" << gamma << " = " << "alpha" << alpha << endl;
    
    alpha = beta * gamma;
    cout << "beta" << beta << " * " << "gamma" << gamma << " = " << "alpha" << alpha << endl;
}
