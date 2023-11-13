#include "SoloveiStrassentest.h"
#include <exception>
#include <cmath>
#include <iostream>
int SoloveiStrassenTest::iterations_counter(const float& is_prime_min_probability) {
	
	        if (is_prime_min_probability < 0.5 || is_prime_min_probability >= 1.0) {
	            throw(std::exception)"Ошибка: Минимальная вероятность должна быть в диапазоне[0.5, 1).";
	        }
	        else {
	            int k = static_cast<int>(std::ceil(std::log(1.0 / (1.0 - is_prime_min_probability)) / std::log(2.0)));
	            return k;
	        }
	    }
bool SoloveiStrassenTest::customize_test(const long long& test_value) {
			long a = randomiser(2, test_value - 1);
			SymbolCalculator symbolcalculator;
	        if (eucledian_algorythm(a, test_value) > 1) {
	            throw(std::exception)"Число не прошло тест";
	        }
			int jacobisymbol = static_cast<int>(symbolcalculator.jacobi_symbol(a, test_value));
			        long long s = mod_pow(a, (test_value - 1) / 2, test_value);
					if (s == test_value - 1) {
						s = -1;
					}
			        if (jacobisymbol != s) {
			            throw(std::exception)"Число не прошло тест";
			        }
			        else {
			            return true;
			        }
	    }