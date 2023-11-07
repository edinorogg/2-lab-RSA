#include "endlessfraction.h"


std::vector<int> get_cf_expansion(int n, int d) { //непрерывная дробь
    std::vector<int> e;
    int q = n / d;
    int r = n % d;

    e.push_back(q);

    while (r != 0) {
        n = d;
        d = r;
        q = n / d;
        r = n % d;
        e.push_back(q);
    }

    return e;
}

std::vector<std::pair<int, int>> get_convergents(const std::vector<int>& e) {    //подходящие дроби

    std::vector<int> n;
    std::vector<int> d;
    std::vector<std::pair<int, int>> convergents;
    for (size_t i = 0; i < e.size(); ++i) {
        int ni, di;

        if (i == 0) {
            ni = e[i];
            di = 1;
        }
        else if (i == 1) {
            ni = e[i] * e[i - 1] + 1;
            di = e[i];
        }
        else { // i > 1
            ni = e[i] * n[i - 1] + n[i - 2];
            di = e[i] * d[i - 1] + d[i - 2];
        }

        n.push_back(ni);
        d.push_back(di);

        convergents.emplace_back(ni, di);
    }

    return convergents;
}

