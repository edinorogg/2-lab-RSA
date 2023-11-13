#include <iostream>
#include<string>
#include <cmath>
#include <random>
#include <unordered_set>
#include "PrimalityTest.h"
#include "FermaTest.h"
#include "SoloveiStrassenTest.h"
#include "MillerRabinTest.h"
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
enum class Test {
    FermaTest,
    MillerRabinTest,
    SoloveiStrassenTest
};
Test choose_test() {
    std::string input;
    int c;
    cout << "Выберите каким тестом вы хотите воспользоваться для генерации ключа" << endl;
    cout << "1. Тест Миллера-Рабина" << endl;
    cout << "2. Тест Ферма" << endl;
    cout << "3. Тест Соловея-Штрассена" << endl;
    do {
        cin >> input;

        std::stringstream ss(input);

        if (ss >> c) {
            if (c > 3 || c < 1) {
                cout << "Введённое вами значение должно соответствовать номеру варианта." << std::endl;
                cin.clear();
            }
            else {
                break;
            }
        }
        else {
            cout << "Ошибка: Введенное значение не является числом. Попробуйте снова." << std::endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (c > 3 || c < 1);
    switch (c)
    {
    case 1:
        return Test::MillerRabinTest;
        break;
    case 2:
        return Test::FermaTest;
        break;
    case 3:
        return Test::SoloveiStrassenTest;
        break;
    default:
        throw(std::exception)"Что-то пошло не так при выборе теста";
    }
}
[[nodiscard]] double get_probability() {
    std::string input;
    double is_prime_min_probablity;
    while (true) {

        cout << "Пожалуйста, введите значение минимальной вероятности для числа [0.5.. 1) " << endl;
        cin >> input;
        std::stringstream ss(input);
        if (ss >> is_prime_min_probablity) {
            if (is_prime_min_probablity < 0.5 || is_prime_min_probablity >= 1) {
                std::cout << "Ошибка: Введенное значение  не должно быть больше 1 и меньше 0.5" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                return is_prime_min_probablity;
                break;
            }
        }
        else {
            std::cout << "Ошибка: Введенное значение не является числом. Попробуйте снова." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }


}

int main()
{
    setlocale(LC_ALL, "Russian");
    long long test_value;
    bool flag = false;
    do {
        cout << "Пожалуйста, введите число для проверки" << endl;
        cin >> test_value;
        if (test_value <= 0) {
            cout << "По определению простые числа положительные. Вы вводите отрицательное число или 0 " << endl;
        }
        if (test_value && 1 != 1) {
            cout << "Введённое вами число не простое, поскольку делится на 2. Пожалуйста, введите нечётное число" << endl;
        }
        if (test_value == 1 || test_value == 2) {
            cout << "Это число точно простое. Попробуйте другое число" << endl;
        }
        if ((test_value > 2) && (test_value && 1 == 1)) {
            flag = true;
        }
      

    } while (!flag);

    Test variant = choose_test();
    double is_prime_min_probability = get_probability();
    try {
        switch (variant)
        {
        case Test::FermaTest: {
            FermaTest fermaTest;
            fermaTest.runTest(is_prime_min_probability, test_value);
            break;
        }
        case Test::MillerRabinTest: {

            MillerRabinTest MillerRabTest;
            MillerRabTest.runTest(is_prime_min_probability, test_value);
            break;
        }
        case Test::SoloveiStrassenTest: {
            SoloveiStrassenTest SolovStrTest;
            SolovStrTest.runTest(is_prime_min_probability, test_value);
            break;
        }
        default:
            //Do nothing
            break;
        }
        cout << "Число вероятно простое " << test_value << endl;
    }

    catch (std::exception& e) {
        cout << e.what() << endl;
    }
}
    