#pragma once
#include "PrimalityTest.h"
#include "algorythms.h"
class FermaTest : public PrimalityTest
{
protected:
    int iterations_counter(const float& is_prime_min_probability) override;
    bool customize_test(const long long& test_value)  override;

};

