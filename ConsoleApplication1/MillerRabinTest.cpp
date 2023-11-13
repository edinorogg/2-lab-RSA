#include "MillerRabinTest.h"
#include <cmath>
#include <exception>
int MillerRabinTest::iterations_counter(const float& is_prime_min_probability) {
    if (is_prime_min_probability < 0.5 || is_prime_min_probability >= 1.0) {
        throw(std::exception)"Ошибка: Минимальная вероятность должна быть в диапазоне[0.5, 1).";
    }
    double q = 1.0 - is_prime_min_probability; // Вероятность ошибки
    int k = std::ceil(std::log(q) / std::log(0.25)); // Вычисление k
    return k;
}
bool MillerRabinTest::customize_test(const long long& test_value) {
    if (test_value < 1) return false;
    if (test_value <= 3) return true;
    long long d = test_value - 1;
    int poweroftwo = 0;
    while (d % 2 == 0) {
        d /= 2;
        poweroftwo++;
    }
    long long a = 0;
    a = static_cast<long long>(randomiser(2, test_value - 2));
    long long x = mod_pow(a, d, test_value);
    if (x == 1 || x == test_value - 1) {
        return true;
    }

    for (int i = 0; i < poweroftwo - 1; i++)
    {
        x = mod_pow(x, 2, test_value);
        if (x == 1) {
            throw(std::exception)"Число не прошло тест";
        }
        else if (x == test_value - 1) {
            return true;
        }
    }
    throw(std::exception)"Число не прошло тест";
}