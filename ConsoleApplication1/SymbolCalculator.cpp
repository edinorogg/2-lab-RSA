#include "SymbolCalculator.h"
#include <stdexcept>
bool SymbolCalculator::check(long const& a, long const& p) {
        if ((a < 0) || (a > p))
            throw std::invalid_argument("a должно быть положительным числом и меньше p.");
        else {
            return true;
        }
}
long long SymbolCalculator::legendre_symbol(long a, long p){
    //cout << "a is " << a << endl;
    //cout << "p is " << p << endl;
    check(a, p);
    if (p <= 0 || (p % 2 == 0 && p != 2)) {
        throw std::invalid_argument("p должно быть простым числом или 2");
    }
    a = a % p;
    if (a < 0) {
        a += p; // приводим a к положительному значению в диапазоне [0, p)
    }
    if (a == 0) {
        return 0;
    }
    if (a == 1) {
        return 1;
    }
    if (a % 2 == 0) {
        return legendre_symbol(a / 2, p) * pow(-1, (p * p - 1) / 8);
    }
    else {
        return legendre_symbol(p % a, a) * pow(-1, (a - 1) * (p - 1) / 4);
    }
}
;
long long SymbolCalculator::jacobi_symbol(long a, long n) {
    if (n <= 0 || n % 2 == 0) {
        throw std::invalid_argument("n должно быть нечетным положительным числом");
    }
    if (n == 1) {
        return 1;
    }
    a = a % n;
    if (a < 0) {
        a += n; // приводим a к положительному значению в диапазоне [0, n)
    }
    if (a == 0) {
        return 0;
    }
    if (a == 1) {
        return 1;
    }
    if (a % 2 == 0) {
        return jacobi_symbol(a / 2, n) * pow(-1, (n * n - 1) / 8);
    }
    else {
        if (a % 4 == 3 && n % 4 == 3) {
            return -jacobi_symbol(n, a);
        }
        else {
            return jacobi_symbol(n, a);
        }
    }
};


