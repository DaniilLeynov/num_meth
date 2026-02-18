#include "interpol.h"
#include <iostream>
#include <cfloat>
#include <iomanip>
#include <algorithm>
#include <cmath>

std::vector<double> uniform_nodes(int n, std::pair<int, int> segment) {
    if (n <= 1) return {0};
    std::vector<double> nodes(n);

    double a = (double)segment.first;
    double b = (double)segment.second;

    for (int i = 0; i < n; i++) {
        nodes[i] = a + i * (b - a) / (n - 1);
    }
    return nodes;
}

std::vector<double> chebyshev_nodes(int n, std::pair<int, int> segment) {
    std::vector<double> nodes(n);

    double a = (double)segment.first;
    double b = (double)segment.second;

    for (int i = 0; i < n; i++) {
        double cheb = cos((2.0 * i + 1.0) / (2.0 * n) * M_PI);
        nodes[i] = (a + b) / 2.0 + (b - a) / 2.0 * cheb;
    }
    sort(nodes.begin(), nodes.end());
    return nodes;
}

double lagrange_interpol(const std::vector<double>& xs,
                         const std::vector<double>& ys, double x) {
    int n = xs.size();
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        double term = ys[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                if (std::abs(xs[i] - xs[j]) < DBL_EPSILON) {
                    std::cout << "Devision by zero" << std::endl;
                    return DBL_MIN;
                }
                term *= (x - xs[j]) / (xs[i] - xs[j]);
            }
        }
        result += term;
    }
    return result;
}

