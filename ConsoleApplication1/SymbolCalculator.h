#pragma once
#include <cmath>
class SymbolCalculator
{
    public:
        long long legendre_symbol(long a, long p);
        long long jacobi_symbol(long a, long n);
    protected:
          bool check(long const& a, long const& p);
};

