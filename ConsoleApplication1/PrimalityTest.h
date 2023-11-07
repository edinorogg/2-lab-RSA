#pragma once
class PrimalityTest
{
protected:
	long long randomiser();
	long long randomiser(long min, long max);
	virtual bool customize_test(const long long& test_value) = 0;
	virtual int iterations_counter(const float& is_prime_min_probability) = 0;
	bool cheking_if_even(const long long& value);
public:
	void runTest(float is_prime_min_probability, const long long &test_value);
};