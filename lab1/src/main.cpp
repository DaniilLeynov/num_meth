#include "interpol.h"
#include "func.h"
#include "draw_plots.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <limits>

void print_nodes(const std::vector<double>& nodes) {
    for (double x : nodes) std::cout << x << " ";
    std::cout << std::endl;
}

void calculate_midpoints(std::vector<double>& midpoints, const std::vector<double>& nodes, int n) {
    for (int i = 0; i < n -1; i++)
        midpoints.push_back((nodes[i] + nodes[i + 1]) / 2.0);
}

void print_interpol_res(std::vector<double>& midpoints, std::vector<double>& nodes,
                        std::vector<double>& value) {
    for (double x : midpoints) {
        std::cout << "   x*        f(x*)        Ln(x*)       Error" << std::endl;
        double exact = func(x);
        double interpol = lagrange_interpol(nodes, value, x);
        double err = fabs(interpol - exact);
        std::cout << std::setw(8) << x << "  " << std::setw(10) << exact << "  " << std::setw(10) <<
                  interpol << "  " << std::setw(10) << err << std::endl;
    }
}

double get_max_err(std::vector<double>& midpoints, std::vector<double>& nodes, std::vector<double>& values) {
    double max_err = 0.0;
    for (double x : midpoints)
        max_err = std::max(max_err, fabs(lagrange_interpol(nodes, values, x) - func(x)));

    return max_err;
}

void export_data_to_file(const std::vector<double>& nodes_uniform,
                         const std::vector<double>& nodes_cheb,
                         const std::vector<double>& values_uniform,
                         const std::vector<double>& values_cheb,
                         const std::pair<int, int>& segment,
                         const int n) {

    double a = (double)segment.first;
    double b = (double)segment.second;

    std::ofstream data_file("data/interpolation_data.txt");
    if (!data_file.is_open()) {
        std::cout << "Error: Cannot create file!" << std::endl;
        return;
    }

    data_file << std::fixed << std::setprecision(6);
    data_file << "# x exact uniform chebyshev uniform_nodes chebyshev_nodes\n";

    const int points = 1000;
    double dx = (b - a) / (points - 1);

    for (int i = 0; i < points; i++) {
        double x = a + i * dx;
        double exact = func(x);
        double unif = lagrange_interpol(nodes_uniform, values_uniform, x);
        double cheb = lagrange_interpol(nodes_cheb, values_cheb, x);

        double uniform_node_value = 0.0;
        double cheb_node_value = 0.0;

        for (size_t j = 0; j < nodes_uniform.size(); j++) {
            if (std::abs(x - nodes_uniform[j]) < dx/2) {
                uniform_node_value = exact;
                break;
            }
        }

        for (size_t j = 0; j < nodes_cheb.size(); j++) {
            if (std::abs(x - nodes_cheb[j]) < dx/2) {
                cheb_node_value = exact;
                break;
            }
        }
        if (uniform_node_value == 0.0) uniform_node_value = NAN;
        if (cheb_node_value == 0.0) cheb_node_value = NAN;
        data_file << x << " " << exact << " " << unif << " " << cheb << " "
                  << uniform_node_value << " " << cheb_node_value << "\n";
    }

    data_file.close();
    std::cout << "Data saved to interpolation_data.txt" << std::endl;
}

int main(int argc, char* argv[]) {
    int n = (argc <= 1) ? 10 : atoi(argv[1]);
    if (n <= 0) {
        std::cout << "The number of nodes is less \
                than or equal to zero" << std::endl;
        return -1;
    }

    std::vector<double> nodes_uniform = uniform_nodes(n,segment);
    std::vector<double> nodes_cheb = chebyshev_nodes(n,segment);

    std::cout << "\n Nodes" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "\n Uniform nodes" << std::endl;
    print_nodes(nodes_uniform);
    std::cout << "\n Cheb nodes" << std::endl;
    print_nodes(nodes_cheb);

    std::vector<double> values_uniform(n), values_cheb(n);

    for (int i = 0; i < n; i++) {
        values_uniform[i] = func(nodes_uniform[i]);
        values_cheb[i] = func(nodes_cheb[i]);
    }

    std::vector<double> midpoints_uniform, midpoints_cheb;
    calculate_midpoints(midpoints_uniform, nodes_uniform, n);
    calculate_midpoints(midpoints_cheb, nodes_cheb, n);

    std::cout << "\nInterpolation results at midpoints: " << std::endl;
    std::cout << "\n Uniform grid" << std::endl;
    print_interpol_res(midpoints_uniform, nodes_uniform, values_uniform);

    std::cout << "\n Cheb grid" << std::endl;
    print_interpol_res(midpoints_cheb, nodes_cheb, values_cheb);


    double max_err_uniform = get_max_err(midpoints_uniform, nodes_uniform, values_uniform);
    double max_err_cheb = get_max_err(midpoints_cheb, nodes_cheb, values_cheb);

    std::cout << "\nMaximum error at midpoints:" << std::endl;
    std::cout << "Uniform grid:   " << max_err_uniform << std::endl;
    std::cout << "Chebyshev grid: " << max_err_cheb << std::endl;

    std::cout << "\n Draw plots" << std::endl;
    export_data_to_file(nodes_uniform, nodes_cheb, values_uniform, values_cheb, segment, n);
    draw_plots();
    return 0;
}

