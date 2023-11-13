#pragma once
#include "SymbolCalculator.h"
#include "PrimalityTest.h"
#include "algorythms.h"
class SoloveiStrassenTest : public PrimalityTest
{
protected:
	int iterations_counter(const float& is_prime_min_probability) override;
	bool customize_test(const long long& test_value) override;
};

