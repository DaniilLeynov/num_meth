#ifndef INTERPOL
#define INTERPOL

#include <vector>
#include <utility>

std::vector<double> uniform_nodes(int n, std::pair<int, int> segment);

std::vector<double> chebyshev_nodes(int n, std::pair<int, int> segment);

double lagrange_interpol(const std::vector<double>& xs,
                         const std::vector<double>& ys,
                         double x);

#endif
