#ifndef FUNC
#define FUNC

#include <cmath>
#include <utility>

constexpr std::pair<int, int> segment = {0, 10};

inline double func(double x) {
    if (x == 0.0) return 0.0;

    return pow(x/10.0, sin(x));
}

#endif
