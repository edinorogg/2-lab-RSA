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

    base = base % mod;  // ”бедимс€, что base находитс€ в диапазоне [0, mod - 1]

    while (exponent > 0) {
        // ≈сли текущий бит экспоненты равен 1, умножаем result на base и берем остаток по модулю
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        // ¬озводим base в квадрат и берем остаток по модулю
        base = (base * base) % mod;

        // Ёкспонента сдвигаетс€ вправо
        exponent >>= 1;
    }

    return result;
}