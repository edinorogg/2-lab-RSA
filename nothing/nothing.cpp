#include <iostream>
#include <cstdlib>
#include <cmath>
#include <numeric>

int eucledian_algorythm(int a, int b) {

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
// Функция для вычисления символа Якоби
int jacobi(int a, int n) {
    if (n <= 0 || n % 2 == 0)
        return 0;

    int result = 1;
    int a_mod_n = a % n;
    while (a_mod_n != 0) {
        while (a_mod_n % 2 == 0) {
            a_mod_n /= 2;
            int n_mod_8 = n % 8;
            if (n_mod_8 == 3 || n_mod_8 == 5)
                result = -result;
        }
        // Обмен значениями a и n, если n нечётное и не делит a
        int temp = a_mod_n;
        a_mod_n = n;
        n = temp;
        if (a_mod_n % 4 == 3 && n % 4 == 3)
            result = -result;
        a_mod_n = a_mod_n % n;
    }
    if (n == 1)
        return result;
    return 0;
}

// Функция для выполнения одной итерации теста Соловея-Штрассена
bool singleIteration(int n, int iterations) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;

    for (int i = 0; i < iterations; ++i) {
        int a = 2 + rand() % (n - 3);
        int g = std::abs(eucledian_algorythm(a, n));
        if (g > 1)
            return false;

        int jacobi_symbol = jacobi(a, n);
        int temp = static_cast<int>(std::pow(a, (n - 1) / 2)) % n;
        if (temp != 1 && temp != n - 1)
            return false;

        if (temp != jacobi_symbol)
            return false;
    }

    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    int iterations;
    std::cout << "Введите число для проверки на простоту: ";
    std::cin >> n;
    std::cout << "Введите количество итераций: ";
    std::cin >> iterations;

    bool isPrime = singleIteration(n, iterations);

    if (isPrime)
        std::cout << n << " - вероятно простое число." << std::endl;
    else
        std::cout << n << " - составное число." << std::endl;

    return 0;
}
