#include <iostream>
#include<string>
#include <cmath>
#include <random>
#include <unordered_set>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random.hpp>
#include <time.h> 

using std::cout;
using std::cin;
using std::endl;
using boost::multiprecision::cpp_int;
using namespace boost::multiprecision;
using std::vector;

long eucledian_algorythm(long a, long b) {

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
cpp_int eucledian_algorythm(cpp_int a, cpp_int b) {

    while (b != 0) {
        cpp_int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long mod_pow(long base, long exponent, long  mod) {
    long result = 1;

    base = base % mod;  // Убедимся, что base находится в диапазоне [0, mod - 1]

    while (exponent > 0) {
        // Если текущий бит экспоненты равен 1, умножаем result на base и берем остаток по модулю
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        // Возводим base в квадрат и берем остаток по модулю
        base = (base * base) % mod;

        // Экспонента сдвигается вправо
        exponent >>= 1;
    }

    return result;
}
cpp_int pow_big_int(cpp_int base, cpp_int exponent) {

    cpp_int result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base;
        }
        base = base * base;
      exponent >>= 1;
    }
    return result;
}
class symbolcalculator {
public:
    bool check(cpp_int  const &a,cpp_int const &p) {
        if ((a < 0) || (a > p))
            throw std::invalid_argument("a должно быть положительным числом и меньше p.");
        else {
            return true;
        }
    }
    cpp_int legendre_symbol(cpp_int a, cpp_int p) {
        cout << "a is " << a << endl;
        cout << "p is " << p << endl;
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
            return legendre_symbol(a / 2, p) * pow_big_int(-1, (p * p - 1) / 8);
        }
        else {
            return legendre_symbol(p % a, a) * pow_big_int(-1, (a - 1) * (p - 1) / 4);
        }
    }
    cpp_int jacobi_symbol(cpp_int a, cpp_int n) {
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
            return jacobi_symbol(a / 2, n) * pow_big_int(-1, (n * n - 1) / 8);
        }
        else {
            if (a % 4 == 3 && n % 4 == 3) {
                return -jacobi_symbol(n, a);
            }
            else {
                return jacobi_symbol(n, a);
            }
        }
    }

};
class RSA_Attack {
protected:
    cpp_int sqrt(cpp_int n) { //нахождение целой части корня
        cpp_int x = n;
        cpp_int y = (x + n / x) / 2;
        while (y < x) {
            x = y;
            y = (x + n / x) / 2;
        }
        return x;
    }
    cpp_int mod_inverse(cpp_int a, cpp_int m) {
        cpp_int m0 = m;
        cpp_int x0 = 0, x1 = 1;

        while (a > 1) {
            cpp_int q = a / m;
            cpp_int t = m;
            m = a % m;
            a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }

        if (x1 < 0) {
            x1 += m0;
        }

        return x1;
    
    }
public:
    cpp_int make_ferma_attack(cpp_int const& e, cpp_int const& n) {
        cout << "e is " << e << endl;
        cout << "N is " << n << endl;
        cpp_int a = sqrt(n);
        cout << "a is " << a << endl;
        cpp_int temp = pow_big_int(a, 2) - n;
        cpp_int b = sqrt(temp);
        cout << " b is " << b << endl;
        while (pow_big_int(b, 2) != temp) {
            cout << "pow b,2 is " << pow_big_int(b, 2) << endl;
            a++;
            temp = pow_big_int(a, 2) - n;
            cout << " temp is " << temp << endl;
            b = sqrt(temp);
            cout << "b is " << b << endl;
        }
        cpp_int y = pow(a, 2) - n;
        b = sqrt(y);
        cpp_int p = a + b;
        cpp_int q = a - b;
        cpp_int EilerFunction = (p - 1) * (q - 1);
        cpp_int d = mod_inverse(e, EilerFunction);
        cout << "e is " << e << endl;
        cout << "p is " << p << endl;
        cout << "Eiler Function is " << EilerFunction << endl;
        cout << "d is " << d << endl;
        return 0;
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");
    clock_t start = clock();
    RSA_Attack test1;
    cpp_int N = 483;
    cpp_int e = 3;
  
    test1.make_ferma_attack(e, N);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "\nTime spent: " << seconds; 
}

