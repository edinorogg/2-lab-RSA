#include "algorythms.h"
long eucledian_algorythm(long a, long b) {

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long mod_pow(long long base, long long  exponent, long long mod) {
    long long result = 1;

    base = base % mod;  // ��������, ��� base ��������� � ��������� [0, mod - 1]

    while (exponent > 0) {
        // ���� ������� ��� ���������� ����� 1, �������� result �� base � ����� ������� �� ������
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        // �������� base � ������� � ����� ������� �� ������
        base = (base * base) % mod;

        // ���������� ���������� ������
        exponent >>= 1;
    }

    return result;
}