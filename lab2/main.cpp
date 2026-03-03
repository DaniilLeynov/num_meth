#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <fstream>
#include <algorithm>

enum class Method {
    Forward,
    CentralFirst,
    SecondOrder2,
    SecondOrder4
};

static std::vector<double> generate_grid(double a, double b, double h) {
    std::vector<double> grid;
    for (double x = a; x <= b + 1e-12; x += h)
        grid.push_back(x);
    return grid;
}

static std::vector<double> numerical_derivative(
    const std::function<double(double)>& f,
    const std::vector<double>& x,
    double h,
    Method method
) {
    size_t n = x.size();
    std::vector<double> result(n, 0.0);

    switch (method) {

    case Method::Forward:
        for (size_t i = 0; i < n - 1; ++i)
            result[i] = (f(x[i+1]) - f(x[i])) / h;
        break;

    case Method::CentralFirst:
        for (size_t i = 1; i < n - 1; ++i)
            result[i] = (f(x[i+1]) - f(x[i-1])) / (2*h);
        break;

    case Method::SecondOrder2:
        for (size_t i = 1; i < n - 1; ++i)
            result[i] = (f(x[i+1]) - 2*f(x[i]) + f(x[i-1])) / (h*h);
        break;

    case Method::SecondOrder4:
        for (size_t i = 2; i < n - 2; ++i)
            result[i] = (
                            -f(x[i+2])
                            + 16*f(x[i+1])
                            - 30*f(x[i])
                            + 16*f(x[i-1])
                            - f(x[i-2])
                        ) / (12*h*h);
        break;
    }

    return result;
}

static double max_error(
    const std::vector<double>& numeric,
    const std::vector<double>& x,
    const std::function<double(double)>& exact,
    size_t start,
    size_t end
) {
    double max_err = 0.0;

    for (size_t i = start; i < end; ++i) {
        double err = std::abs(numeric[i] - exact(x[i]));
        max_err = std::max(max_err, err);
    }

    return max_err;
}

int main() {
    double a = -3.0;
    double b = 3.0;
    std::vector<double> h_values = {0.2, 0.1, 0.05, 0.025, 0.0125};

    auto f = [](double x) {
        return std::sinh(1.0 + x*x);
    };

    auto f1_exact = [](double x) {
        return 2*x*std::cosh(1.0 + x*x);
    };

    auto f2_exact = [](double x) {
        return 2*std::cosh(1.0 + x*x)
               + 4*x*x*std::sinh(1.0 + x*x);
    };

    std::ofstream file("errors.csv");
    file << "h,forward,central,second2,second4\n";

    for (double h : h_values) {

        auto grid = generate_grid(a, b, h);

        auto forward = numerical_derivative(f, grid, h, Method::Forward);
        auto central = numerical_derivative(f, grid, h, Method::CentralFirst);
        auto second2 = numerical_derivative(f, grid, h, Method::SecondOrder2);
        auto second4 = numerical_derivative(f, grid, h, Method::SecondOrder4);

        double err_forward =
            max_error(forward, grid, f1_exact, 0, grid.size()-1);

        double err_central =
            max_error(central, grid, f1_exact, 1, grid.size()-1);

        double err_second2 =
            max_error(second2, grid, f2_exact, 1, grid.size()-1);

        double err_second4 =
            max_error(second4, grid, f2_exact, 2, grid.size()-2);

        file << h << ","
             << err_forward << ","
             << err_central << ","
             << err_second2 << ","
             << err_second4 << "\n";

        std::cout << "h = " << h
                  << "  forward = " << err_forward
                  << "  central = " << err_central
                  << "  second2 = " << err_second2
                  << "  second4 = " << err_second4
                  << "\n";
    }

    file.close();
    return 0;
}

