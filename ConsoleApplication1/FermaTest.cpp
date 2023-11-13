#include "FermaTest.h"
#include <string>
#include <cmath>
#include <random>
#include <unordered_set>
int FermaTest::iterations_counter(const float& is_prime_min_probability) {
    if (is_prime_min_probability < 0.5 || is_prime_min_probability >= 1.0) {
        throw(std::exception)"Ошибка: Минимальная вероятность должна быть в диапазоне[0.5, 1).";
    }
    else {
        int k = static_cast<int>(std::ceil(std::log(1.0 / (1.0 - is_prime_min_probability)) / std::log(2.0)));
        return k;
    }

}

bool FermaTest::customize_test(const long long& test_value)
{

    if (test_value < 1) {
        return false;
    }
    else if (test_value <= 3) {
        return true;
    }
    long long a = randomiser(2, test_value - 1);
    //creating_a(a, uniqueNumbers, test_value);

    if (mod_pow(a, test_value - 1, test_value) == 1) {
        return true;
    }
    else {
        throw(std::exception)"Число не прошло тест";
        return false;
    }


}
