#include "PrimalityTest.h"
#include <random>
    long long PrimalityTest::randomiser() {
        std::random_device random_device; //рандомайзер без параметров
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> dis(500, 10000);
        return dis(generator);
    }
    long long PrimalityTest::randomiser(long min, long max) { //рандомайзер с параметрами
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<long> dist(min, max);
        return dist(gen);
    }
    bool PrimalityTest::cheking_if_even(const long long & value) {
        if (value & 1) {
            return true;
        }
        else {
            return false;
        }
    }
    void PrimalityTest::runTest(float is_prime_min_probability, const long long& test_value) { //сюда ещё нужно будет вписать название теста в качестве принимаемого параметра./////
        bool test_failed = false;
        cheking_if_even(test_value);
        int iterations_amount = iterations_counter(is_prime_min_probability);
        int succesful_operations = 0;
        int i = 0;
        while (succesful_operations != iterations_amount) {
            i = 0;
            test_failed = false; //обнуляем переменные при выходе из цикла
            succesful_operations = 0;
            for (size_t i = 0; i < iterations_amount; i++)
            {
                    customize_test(test_value);
                    succesful_operations++;
            }
        }
    }
